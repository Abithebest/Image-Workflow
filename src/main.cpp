#include <iostream>
#include <filesystem>
#include <map>

#include "photo.hpp"
#include "folder.hpp"

namespace fs = std::filesystem;

struct Configuration {
    //folder, collection name, filters, webp, watermark
    fs::path folder = "";
    std::string collection = "";
    std::map<std::string, std::string> filters;
    bool webp = true;
    bool watermark = false;
};

int main() {
    const std::string MENU = "========= Image Workflow =========\n\n1. Run Workflow\n2. Connect Folder\n3. Configurations\n4. Exit\n\n> ";

    int command;
    bool continueCommands = true;
    Configuration config;

    fs::path defaultPath;
    #if defined(_WIN32)
        const char* profile = std::getenv("USERPROFILE");
        if(profile) {
            defaultPath = fs::path(profile);
        }
    #else
        const char* home = std::getenv("HOME");
        if(home) {
            defaultPath = fs::path(home);
        }
    #endif

    while(continueCommands) {
        std::cout << MENU;
        std::cin >> command;

        if (!command) {
            std::cout << "Invalid input...\n";

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;
        }

        switch(command) {
            case 1: { // Run Workflow
                auto [it, inserted] = FolderData.try_emplace(config.folder.filename(), config.folder);
                Folder& folder = it->second;

                std::vector<Photo*> photos = folder.getPhotos();

                for(Photo* photo : photos) {
                    std::cout << photo->getId() << "\n";
                    std::cout << "  Date: " << photo->getDate() << "\n";
                    std::cout << "  ISO: " << photo->getIso() << "\n";
                    std::cout << "  Aperture: " << photo->getAperture() << "\n";
                    std::cout << "  Focal: " << photo->getFocal() << "\n";
                    std::cout << "  Shutter: " << photo->getShutter() << "\n";
                }
                break;
            }

            case 2: { // Connect Folder
                fs::path folderPath;

                std::cout << "Folder Path to Connect (e.g. Desktop/Folder) > ";
                std::cin >> folderPath;

                config.folder = defaultPath / folderPath;
                std::cout << "Connected to " << config.folder << ".\n\n";
                break;
            }

            case 3: { // Configurations
                break;
            }

            case 4: // Exit
                continueCommands = false;
                std::cout << "Exited instance...\n";
                break;

            default:
                std::cout << "Not a command...\n";
                break;
        }
    }

    return 0;
}