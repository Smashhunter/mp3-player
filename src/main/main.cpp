#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStandardPaths>
#include "presentation/Client.hpp"
#include "factories/SfmlAudioEngineFactory.hpp"
#include "data-source/TrackRepository.hpp"

#include <string>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    SfmlAudioEngineFactory sfFactory;
    // std::string defaultMusicPath = (QStandardPaths::writableLocation(QStandardPaths::MusicLocation)).toStdString();
    TrackRepository trackRep("");
    Client client;
    client.init(&sfFactory,&trackRep);


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("client"), &client);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("mp3player", "Main");
 
    return app.exec();
}
