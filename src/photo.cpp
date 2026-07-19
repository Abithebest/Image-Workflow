#include <iostream>
#include <filesystem>
#include <algorithm>
#include <map>

#include <exiv2/exiv2.hpp>
#include "photo.hpp"

namespace fs = std::filesystem;

std::map<std::string, Photo> PhotoData;
Photo::Photo(const fs::path& photo_directory) {
    _id = photo_directory.filename().string();
    _path = photo_directory;
    _name = photo_directory.stem().string();
    _type = getPhotoType(photo_directory);
    _loadExif(photo_directory);
}

void Photo::_loadExif(const fs::path& photo_directory) {
    try {
        auto photo_data = Exiv2::ImageFactory::open(photo_directory.string());
        if (!photo_data) {
            std::cerr << "Could not open image\n";
            return;
        }

        photo_data->readMetadata();
        Exiv2::ExifData& photo_exif = photo_data->exifData();

        auto getExif = [&](const char* key) -> std::optional<Exiv2::ExifData::const_iterator>
        {
            auto exif_data = photo_exif.findKey(Exiv2::ExifKey(key));

            if(exif_data == photo_exif.end())
                return std::nullopt;

            return exif_data;
        };

        if(auto photo_date = getExif("Exif.Photo.DateTimeOriginal"))
            _exif.date = (*photo_date)->value().toString();
        if(auto photo_aperture = getExif("Exif.Photo.FNumber"))
            _exif.aperture = (*photo_aperture)->value().toFloat();
        if(auto photo_shutter_speed = getExif("Exif.Photo.ExposureTime"))
            _exif.shutter_speed = (*photo_shutter_speed)->value().toString();
        if(auto photo_iso = getExif("Exif.Photo.ISOSpeedRatings"))
            _exif.iso = (*photo_iso)->value().toInt64();
        if(auto photo_focal_length = getExif("Exif.Photo.FocalLength"))
            _exif.focal_length = (*photo_focal_length)->value().toFloat();
   } catch(const Exiv2::Error& e) {
        std::cerr << "EXIF error: " << e.what() << '\n';
   }
}

std::string& Photo::getId() {
    return _id;
}
fs::path& Photo::getPath() {
    return _path;
}
std::string& Photo::getName() {
    return _name;
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
float& Photo::getAperture() {
    return _exif.aperture;
}
float& Photo::getFocal() {
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
void Photo::toWebp(bool watermark) {
    //
}

PhotoType getPhotoType(const fs::path& photo_directory) {
    std::string photo_extension = photo_directory.extension().string();
    std::transform(photo_extension.begin(), photo_extension.end(), photo_extension.begin(),
        [](unsigned char c) { return std::tolower(c); });

    if(photo_extension == ".jpg" || photo_extension == ".jpeg") {
        return PhotoType::JPEG;
    } else if(photo_extension == ".png") {
        return PhotoType::PNG;
    } else if(photo_extension == ".webp") {
        return PhotoType::WEBP;
    }

    return PhotoType::UNKNOWN;
}