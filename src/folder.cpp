#include <iostream>
#include <filesystem>
#include <vector>
#include <map>

#include "folder.hpp"
#include "photo.hpp"

namespace fs = std::filesystem;

Folder::Folder(fs::path directory) {
    if(!fs::exists(directory) || !fs::is_directory(directory)) return;

    _name = directory.filename().string();
    for(const auto& file : fs::directory_iterator(directory)) {
        if(!file.is_regular_file())
            continue;

        const auto& path = file.path();

        if(getPhotoType(path) != PhotoType::UNKNOWN)
            _photos.push_back(path);
    }
}

std::string& Folder::getName() {
    return _name;
}
std::vector<Photo*> Folder::getPhotos() {
    std::vector<Photo*> finalized_photos;
    for(const fs::path& path : _photos) {
        auto [photo, inserted] = PhotoData.try_emplace(path.filename(), path);
        finalized_photos.push_back(&photo->second);
    }

    return finalized_photos;
}

std::map<std::string, Folder> FolderData;