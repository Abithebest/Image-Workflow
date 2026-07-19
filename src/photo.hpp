#ifndef PHOTO_HPP
#define PHOTO_HPP

#include <iostream>
#include <filesystem>
#include <map>

namespace fs = std::filesystem;

enum class PhotoType {
    UNKNOWN = -1,
    JPEG = 0,
    PNG,
    WEBP
};
struct PhotoExif {
    std::string date;
    int iso;
    float aperture;
    float focal_length;
    std::string shutter_speed;
};
struct PhotoFilter {
    std::string name;
    std::string value;
};

class Photo {
    private:
        std::string _id;
        fs::path _path;
        std::string _name;
        PhotoType _type;
        PhotoExif _exif;
        std::map<std::string, PhotoFilter> _filters;
        void _loadExif(const fs::path& photo_directory);

    public:
        Photo(const fs::path& photo_directory);
        std::string& getId();
        fs::path& getPath();
        std::string& getName();
        PhotoType& getType();
        std::string& getDate();
        int& getIso();
        float& getAperture();
        float& getFocal();
        std::string& getShutter();
        std::map<std::string, PhotoFilter>& getFilters();
        void getJson();
        void addFilter(const std::string& filter_name, const std::string& filter_value);
        void toWebp(bool watermark);
};

extern std::map<std::string, Photo> PhotoData;

PhotoType getPhotoType(const fs::path& photo_directory);

#endif