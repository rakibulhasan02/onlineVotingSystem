// NumberManagementSystem.cpp

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class NumberManager {
private:
    vector<int> numbers;

public:
    void addNumber(int num) {
        numbers.push_back(num);
        cout << "Number " << num << " added successfully.\n";
    }

    void deleteNumber(int num) {
        auto it = find(numbers.begin(), numbers.end(), num);
        if (it != numbers.end()) {
            numbers.erase(it);
            cout << "Number " << num << " deleted successfully.\n";
        } else {
            cout << "Number not found.\n";
        }
    }

    void searchNumber(int num) {
        auto it = find(numbers.begin(), numbers.end(), num);
        if (it != numbers.end()) {
            cout << "Number " << num << " found at position " << (it - numbers.begin()) << ".\n";
        } else {
            cout << "Number not found.\n";
        }
    }

    void displayNumbers() {
        if (numbers.empty()) {
            cout << "No numbers in the system.\n";
            return;
        }
        cout << "Numbers in the system: ";
        for (int num : numbers) {
            cout << num << " ";
        }
        cout << "\n";
    }

    void sortNumbers() {
        sort(numbers.begin(), numbers.end());
        cout << "Numbers sorted in ascending order.\n";
    }
};

int main() {
    NumberManager manager;
    int choice, number;

    do {
        cout << "\n=== Number Management System ===\n";
        cout << "1. Add Number\n";
        cout << "2. Delete Number\n";
        cout << "3. Search Number\n";
        cout << "4. Display All Numbers\n";
        cout << "5. Sort Numbers\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter number to add: ";
                cin >> number;
                manager.addNumber(number);
                break;
            case 2:
                cout << "Enter number to delete: ";
                cin >> number;
                manager.deleteNumber(number);
                break;
            case 3:
                cout << "Enter number to search: ";
                cin >> number;
                manager.searchNumber(number);
                break;
            case 4:
                manager.displayNumbers();
                break;
            case 5:
                manager.sortNumbers();
                break;
            case 6:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}
