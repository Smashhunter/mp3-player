#include "data-source/TrackRepository.hpp"

#include <iostream>
#include <filesystem>
#include <algorithm>
#include <cctype>
#include <vector>

TrackRepository::TrackRepository(const std::string &dataFolder)
    : dataFolderPath(dataFolder)
{
}

void TrackRepository::setDataFolderPath(const std::string &path)
{
    dataFolderPath = std::move(path);
}
Playlist TrackRepository::loadTracks() const
{
    Playlist playlist;
    if(dataFolderPath=="") return playlist;
    // SFML commonly supports these audio formats; include mp3 as well if available in your build
    const std::vector<std::string> sfmlExtensions = {".wav", ".ogg", ".flac", ".aiff", ".aif", ".mp3"};

    for (const auto &entry : std::filesystem::directory_iterator(dataFolderPath))
    {
        if (!entry.is_regular_file())
            continue;

        std::string ext = entry.path().extension().string();
        std::string extLower;
        extLower.reserve(ext.size());
        std::transform(ext.begin(), ext.end(), std::back_inserter(extLower), [](unsigned char c){ return std::tolower(c); });

        if (std::find(sfmlExtensions.begin(), sfmlExtensions.end(), extLower) != sfmlExtensions.end())
        {
            std::string filePath = entry.path().string();
            std::string fileName = entry.path().filename().string();
            playlist.addTrack(Track(fileName, filePath));
        }
    }

    
    return playlist;
}

std::string TrackRepository::loadCover()
{
    if (dataFolderPath.empty())
    {
        std::cerr << "Data folder path is empty. Cannot load cover." << std::endl;
        return "";
    }
    // Common image formats for album covers
    const std::vector<std::string> imageExtensions = {".jpg", ".jpeg", ".png", ".bmp", ".gif"};

    for (const auto &entry : std::filesystem::directory_iterator(dataFolderPath))
    {
        if (!entry.is_regular_file())
            continue;

        std::string ext = entry.path().extension().string();
        std::string extLower;
        extLower.reserve(ext.size());
        std::transform(ext.begin(), ext.end(), std::back_inserter(extLower), [](unsigned char c){ return std::tolower(c); });

        if (std::find(imageExtensions.begin(), imageExtensions.end(), extLower) != imageExtensions.end())
        {   
            
            coverFilePath = entry.path().string(); // Store the found cover file path
            std::cout << "Found cover image: " << coverFilePath << std::endl;
            return coverFilePath; // Return the first found cover image path
        }
    }

    return ""; // No cover found
}

std::string TrackRepository::getCoverFilePath() const
{
    return coverFilePath;
}
