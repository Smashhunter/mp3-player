#pragma once

#include <string>
#include "domain/AudioEngine.hpp"
#include "domain/Playlist.hpp"

class TrackRepository
{
private:
    std::string dataFolderPath;
    std::string coverFilePath; // Store the cover file path
    AudioEngine* engine;

public:
    TrackRepository(const std::string& dataFolder);
    void setDataFolderPath(const std::string& path);
    Playlist loadTracks() const;
    std::string loadCover();
    std::string getCoverFilePath() const;
    void setAudioEngine(AudioEngine* engine);
};
