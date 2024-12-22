// Jeremy Delk
// Instructor Linda Noss
// 12-21-2024

// Dependency includes
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>

// Class to open, save, and keep track of data
class ItemTracker {
private:
    std::map<std::string, int> itemFrequency;

public:
    // Constructor to load data from the input file
    ItemTracker(const std::string& filename) {
        std::ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return;
        }
        std::string item;
        while (inputFile >> item) {
            itemFrequency[item]++;
        }
        inputFile.close();
        SaveFrequencyToFile("frequency.dat");
    }

    // Save the frequency data to a backup file, just in case
    void SaveFrequencyToFile(const std::string& filename) {
        std::ofstream outputFile(filename);
        if (!outputFile.is_open()) {
            std::cerr << "Error: Unable to write to file " << filename << std::endl;
            return;
        }
        for (const auto& entry : itemFrequency) {
            outputFile << entry.first << " " << entry.second << std::endl;
        }
        outputFile.close();
    }

    // Display the frequency of a specific item
    void DisplayItemFrequency(const std::string& item) const {
        auto it = itemFrequency.find(item);
        if (it != itemFrequency.end()) {
            std::cout << "The item \"" << item << "\" appears " << it->second << " times." << std::endl;
        }
        else {
            std::cout << "The item \"" << item << "\" was not found." << std::endl;
        }
    }

    // Display all of the items and their frequencies
    void DisplayAllFrequencies() const {
        std::cout << "Item Frequencies:" << std::endl;
        for (const auto& entry : itemFrequency) {
            std::cout << std::setw(15) << std::left << entry.first << entry.second << std::endl;
        }
    }

    // Display a histogram of item frequencies
    void DisplayHistogram() const {
        std::cout << "Item Histogram:" << std::endl;
        for (const auto& entry : itemFrequency) {
            std::cout << std::setw(15) << std::left << entry.first << std::string(entry.second, '*') << std::endl;
        }
    }
};

// Function to display the main menu and handle user input
void DisplayMenu() {
    std::cout << "\nMenu Options:\n";
    std::cout << "1. Display frequency of a specific item\n";
    std::cout << "2. Display all item frequencies\n";
    std::cout << "3. Display item histogram\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}

// Main function to run the program
int main() {
    ItemTracker tracker("CS210_Project_Three_Input_File.txt"); // Opens the item histogram file

    int theChoice; // Input
    std::string theItem; // User defined choice

    // Program loop
    do {
        DisplayMenu();
        std::cin >> theChoice;
        std::cin.ignore();

        switch (theChoice) {
        case 1:
            std::cout << "Enter the item name: ";
            std::getline(std::cin, theItem);
            tracker.DisplayItemFrequency(theItem);
            break;

        case 2:
            tracker.DisplayAllFrequencies();
            break;

        case 3:
            tracker.DisplayHistogram();
            break;

        case 4:
            std::cout << "Exiting program. Goodbye!" << std::endl;
            break;

        default: // Handling invalid user input
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    } while (theChoice != 4);

    return 0;
}