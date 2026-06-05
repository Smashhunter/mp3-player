#include "presentation/Client.hpp"

#include <QDebug>
#include <QAbstractListModel>
Client::Client(QObject* parent) : QObject(parent)
{
    
}

void Client::init(AudioFactory *factory, TrackRepository *repository)
{
    audioFactory = factory;
    trackRepository = repository;
    audioEngine = factory->createAudioEngine();
    playbackQueue = new PlaybackQueue(audioEngine);
    playbackQueue->setPlaylist(trackRepository->loadTracks());
    repository->loadCover();
    audioEngine->addListener(playbackQueue);
}

int Client::getCurrentTrackIndex() const
{
    return playbackQueue->getCurrentTrackIndex();
}
Q_INVOKABLE void Client::play()
{
    playbackQueue->playCurrentTrack();
}

Q_INVOKABLE void Client::pause()
{
    playbackQueue->pause();
}

Q_INVOKABLE void Client::next()
{
    playbackQueue->playNextTrack();
    emit currentTrackChanged();
    emit trackProgressChanged();
}

Q_INVOKABLE void Client::previous()
{
    playbackQueue->playPreviousTrack();
    emit currentTrackChanged();
    emit trackProgressChanged();
}

Q_INVOKABLE void Client::toggleLooping()
{
    playbackQueue->toggleLooping();
}

Q_INVOKABLE void Client::seek(float position)
{
    playbackQueue->seek(position);
    emit trackProgressChanged();
}

Q_INVOKABLE void Client::setVolume(float volume)
{
    playbackQueue->setVolume(volume);
}

Q_INVOKABLE void Client::loadPlaylist(const QUrl &path)
{
    qDebug() << "Loading playlist from:" << path.toLocalFile();
    trackRepository->setDataFolderPath(path.toLocalFile().toStdString());
    playbackQueue->setPlaylist(trackRepository->loadTracks());
    trackRepository->loadCover();
    playbackQueue->playCurrentTrack();
    emit currentTrackChanged();
}

Q_INVOKABLE QVariantList Client::getPlaylist() const
{
    QVariantList trackList;
    const auto& tracks = playbackQueue->getPlaylist().getTracks();
    for (const auto& track : tracks) {
        QVariantMap trackInfo;
        trackInfo["name"] = QString::fromStdString(track.getName());
        trackInfo["filePath"] = QString::fromStdString(track.getFilePath());
        trackList.append(trackInfo);
    }
    return trackList;
}
Q_INVOKABLE QUrl Client::getCover() const
{
    QString coverPath = QString::fromStdString(trackRepository->getCoverFilePath());
    if (coverPath.isEmpty()) {
        qDebug() << "No cover found in the current directory.";
        return QUrl(); // Return an empty QUrl if no cover is found
    }
    return QUrl::fromLocalFile(coverPath);
}

Q_INVOKABLE void Client::playTrackAtIndex(int index)
{
    while (playbackQueue->getCurrentTrackIndex() != index)
    {
        playbackQueue->playNextTrack();
    }
    emit currentTrackChanged();
}

Q_INVOKABLE float Client::getProgress()
{
    return playbackQueue->getTrackProgress();
}

Q_INVOKABLE float Client::getVolume()
{
    return playbackQueue->getVolume();
}
