#include <iostream>
#include <filesystem>
#include <algorithm>
#include <map>

#include "photo.hpp"

namespace fs = std::filesystem;

std::map<std::string, Photo> PhotoData;
Photo::Photo(std::string file_name, fs::path& file_extension) {
    _id = file_name;
}

std::string& Photo::getId() {
    return _id;
}
PhotoType& Photo::getType() {
    return _type;
}
std::string& Photo::getDate() {
    return _exif.date;
}
int& Photo::getIso() {
    return _exif.iso;
}
int& Photo::getAperture() {
    return _exif.aperture;
}
int& Photo::getFocal() {
    return _exif.focal_length;
}
std::string& Photo::getShutter() {
    return _exif.shutter_speed;
}
std::map<std::string, PhotoFilter>& Photo::getFilters() {
    return _filters;
}

void Photo::getJson() {
    //
}
void Photo::addFilter(const std::string& filter_name, const std::string& filter_value) {
    //
}

bool isPhoto(const fs::path& photo_extension) {
    std::string extension = photo_extension.extension();
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    return (
        extension == ".jpg" ||
        extension == ".jpeg" ||
        extension == ".png" ||
        extension == ".webp"
    );
}