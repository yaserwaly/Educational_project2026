#include "pch.h"
#include "UIHelpers.hpp"
// #include <iostream>  // مكرر: موجود أصلاً بـ pch.h
#include <limits>

namespace UIHelpers {

    void PrintHeader(const std::string& title) {
        std::cout << "========================================\n";
        std::cout << "\t\t" << title << "\n";
        std::cout << "========================================\n";
    }

    void PrintDivider() {
        std::cout << "----------------------------------------\n";
    }

    void Pause() {
        std::cout << "\nPress any key to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }

    int ReadInt(const std::string& prompt, int min, int max) {
        int value;
        while (true) {
            std::cout << prompt;
            std::cin >> value;

            if (std::cin.fail() || value < min || value > max) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
            }
            else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
        }
    }

    std::string ReadString(const std::string& prompt) {
        std::string input;
        std::cout << prompt;
        std::getline(std::cin, input);
        return input;
    }

    bool ConfirmYes(const std::string& question) {
        std::string answer;
        std::cout << question << " (y/n): ";
        std::getline(std::cin, answer);
        while (answer != "y" && answer != "Y" && answer != "n" && answer != "N") {
            std::cout << "Invalid input. Please enter 'y' or 'n': ";
            std::getline(std::cin, answer);
        }
        return (answer == "y" || answer == "Y");
    }

}
