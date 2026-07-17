#include <iostream>
#include <filesystem>

int main() {
    const std::string MENU = "========= Image Workflow =========\n\n1. Connect Folder\n2. Configurations\n3. Exit\n\n> ";

    int command;
    bool continueCommands = true;

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
            case 1: { // Connect Folder
                //
            }

            case 2: { // Configurations
                //
            }

            case 3: // Exit
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