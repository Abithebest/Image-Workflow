#ifndef FOLDER_HPP
#define FOLDER_HPP

#include <iostream>
#include <filesystem>
#include <vector>
#include <map>

#include "photo.hpp"

namespace fs = std::filesystem;

class Folder {
    private:
        std::string _name;
        std::vector<fs::path> _photos;
    
    public:
        Folder(fs::path directory);
        std::string& getName();
        std::vector<Photo*> getPhotos();
};

extern std::map<std::string, Folder> FolderData;

#endif