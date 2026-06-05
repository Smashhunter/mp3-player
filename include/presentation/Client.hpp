#pragma once

#include <QObject>
#include <QUrl>
#include <QAbstractListModel>
#include <QVariantList>
#include "factories/AudioFactory.hpp"
#include "domain/AudioEngine.hpp"
#include "data-source/TrackRepository.hpp"
#include "domain/PlaybackQueue.hpp"

class Client: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int currentTrackIndex READ getCurrentTrackIndex NOTIFY currentTrackChanged)
    Q_PROPERTY(float progress READ getProgress NOTIFY trackProgressChanged)

public:
    Client(QObject* parent = nullptr);
    void init(AudioFactory *factory, TrackRepository *repository);
    int getCurrentTrackIndex() const;
    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void next();
    Q_INVOKABLE void previous();
    Q_INVOKABLE void toggleLooping();
    Q_INVOKABLE void seek(float position);
    Q_INVOKABLE void setVolume(float volume);
    Q_INVOKABLE void loadPlaylist(const QUrl& path);
    Q_INVOKABLE QVariantList getPlaylist() const;
    Q_INVOKABLE QUrl getCover() const;
    Q_INVOKABLE void playTrackAtIndex(int index);
    Q_INVOKABLE float getProgress();
    Q_INVOKABLE float getVolume();

signals:
    void currentTrackChanged();
    void trackProgressChanged();

private:
    AudioFactory* audioFactory;
    AudioEngine* audioEngine;
    TrackRepository* trackRepository;
    PlaybackQueue* playbackQueue;
    bool isRunning = true;
};
