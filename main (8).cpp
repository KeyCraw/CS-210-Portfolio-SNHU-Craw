#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

// GroceryTracker class handles loading and processing grocery item frequencies
class GroceryTracker {
private:
    map<string, int> itemFrequencies;

public:
    // Constructor: Load data from file and count frequencies
    GroceryTracker() {
        loadDataFromFile("CS210_Project_Three_Input_File.txt");
        saveFrequenciesToFile("frequency.dat"); // Save automatically on startup
    }

    // Load items from file and count frequency
    void loadDataFromFile(const string& filename) {
        ifstream inputFile(filename);
        string item;

        if (!inputFile) {
            cerr << "Error: Could not open input file: " << filename << endl;
            exit(1);
        }

        while (inputFile >> item) {
            itemFrequencies[item]++;
        }

        inputFile.close();
    }

    // Save frequencies to backup file
    void saveFrequenciesToFile(const string& filename) {
        ofstream outFile(filename);

        for (const auto& pair : itemFrequencies) {
            outFile << pair.first << " " << pair.second << endl;
        }

        outFile.close();
    }

    // Get the frequency of a specific item
    int getItemFrequency(const string& itemName) {
        if (itemFrequencies.count(itemName)) {
            return itemFrequencies[itemName];
        }
        return 0; // Not found
    }

    // Print all items with their frequencies
    void printAllFrequencies() {
        cout << "\nItem Frequencies:\n------------------" << endl;
        for (const auto& pair : itemFrequencies) {
            cout << setw(15) << left << pair.first << " " << pair.second << endl;
        }
    }

    // Print a histogram with asterisks
    void printHistogram() {
        cout << "\nItem Frequency Histogram:\n--------------------------" << endl;
        for (const auto& pair : itemFrequencies) {
            cout << setw(15) << left << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }
};

// Display the menu
void displayMenu() {
    cout << "\n=========== Corner Grocer Menu ===========\n";
    cout << "1. Search for item frequency\n";
    cout << "2. Display all item frequencies\n";
    cout << "3. Display histogram of item frequencies\n";
    cout << "4. Exit\n";
    cout << "Enter your choice (1-4): ";
}

int main() {
    GroceryTracker tracker;
    int choice;
    string item;

    do {
        displayMenu();
        cin >> choice;

        // Input validation
        while (cin.fail() || choice < 1 || choice > 4) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number between 1 and 4: ";
            cin >> choice;
        }

        switch (choice) {
        case 1:
            cout << "\nEnter item name to search: ";
            cin >> item;
            cout << "Frequency of \"" << item << "\": " << tracker.getItemFrequency(item) << endl;
            break;
        case 2:
            tracker.printAllFrequencies();
            break;
        case 3:
            tracker.printHistogram();
            break;
        case 4:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            // Should never reach here due to validation
            break;
        }

    } while (choice != 4);

    return 0;
}
