#ifndef PHOTO_HPP
#define PHOTO_HPP

#include <iostream>
#include <filesystem>
#include <map>

namespace fs = std::filesystem;

enum class PhotoType {
    JPEG = 0,
    PNG,
    WEBP
};
struct PhotoExif {
    std::string date;
    int iso;
    int aperture;
    int focal_length;
    std::string shutter_speed;
};
struct PhotoFilter {
    std::string name;
    std::string value;
};

class Photo {
    private:
        std::string _id;
        PhotoType _type;
        PhotoExif _exif;
        std::map<std::string, PhotoFilter> _filters;

    public:
        Photo(std::string file_name, fs::path& file_extension);
        std::string& getId();
        PhotoType& getType();
        std::string& getDate();
        int& getIso();
        int& getAperture();
        int& getFocal();
        std::string& getShutter();
        std::map<std::string, PhotoFilter>& getFilters();
        void getJson();
        void addFilter(const std::string& filter_name, const std::string& filter_value);
};

extern std::map<std::string, Photo> PhotoData;

bool isPhoto(const fs::path& photo_extension);

#endif