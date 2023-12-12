#include "GroceryItem.h"
#include <string>
#include <iostream>
#include <fstream>
#include <set>

using namespace std;

// Create a set of GroceryItems to store item names and quantities

set <GroceryItem> items;

//Reads the input file, checks for each grocery item in the file
//Adds the number of each item and backs up data in output file
void readFile() {
	//string item;
	string itemName;
	int itemQuantity = 0;
	string existingName;
	int existingQuantity = 0;

	ifstream inputFile("inventory.txt");

	// Check to see if file is open
	if (!inputFile.is_open()) {
		cout << "Could not open file inventory.txt." << endl;
	}

	// Read each grocery item until the end of the file
	while (!inputFile.eof()) {
		//Create a GroceryItem pointer to item
		inputFile >> itemName;

		GroceryItem* item = new GroceryItem(itemName, itemQuantity);

		//Check to see if item is in the items set
		auto existingItem = items.find(*item);

		if (existingItem != items.end()) {
			existingName = existingItem->getName();
			existingQuantity = existingItem->getQuantity();
			items.erase(existingItem);
			item = new GroceryItem(existingName, existingQuantity);
		}
		// If the item is found, increment item quantity and insert in the set
		item->addItem();
		items.insert(*item);
		delete(item);
	}

	inputFile.close();

	ofstream outputFile;

	// Open file for writing
	outputFile.open("frequency.dat");

	if (!outputFile.is_open()) {
		cout << "Could not open file frequency.dat." << endl;
	}
	for (GroceryItem item : items) {
		outputFile << item.getName() << " " << item.getQuantity() << endl;
	}
		outputFile.close();
}

//Displays Menu with choices for the user 
void displayMenu() {
	cout << "****** Grocery Item Search Menu ******" << endl;
	cout << endl;
	cout << "1 - Search for an item" << endl;
	cout << "2 - Display all frequencies" << endl;
	cout << "3 - Print histogram to console" << endl;
	cout << "4 = Exit Program" << endl;
	cout << endl;
	cout << "Enter your choice: ";
}


int main() {
	string itemName;
	int userInput;

	displayMenu();

	while (true) {
		try
		{
			cin >> userInput;
			if (cin.fail()) {
				throw runtime_error("Input must be an integer.");
			}

			if ((userInput < 0) || (userInput > 5)) {
				throw invalid_argument("Invalid input. Please enter a number between 1 and 4.");
			}
			
		}
		catch (runtime_error& end) {
			cout << end.what() << endl;
			cout << endl;
			displayMenu();
			cout << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}		

		catch (invalid_argument& e) {
			cout << e.what() << endl;
			cout << endl;
			displayMenu();
			cout << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		switch (userInput) {
		case 1: {
			string itemName;
			readFile();
			bool itemFound = false;
			cout << "Enter item: ";
			cin >> itemName;
			for (const auto& item : items) {
				if (item.getName() == itemName) {
					// Item found so return its quantity
					cout << item.getQuantity();
					itemFound = true;
					break;
				}

			}
			if (!itemFound) {
				cout << "Item not found. Please try another menu choice (1 - 4)" << endl;
				displayMenu();
			}
			break;
		}

		case 2:
			readFile();
			for (GroceryItem item : items) {
				cout << item.getName() << " " << item.getQuantity() << endl;
			}

			break;

		case 3:
			readFile();
			for (GroceryItem item : items) {
				cout << item.getName();
				for (int i = 0; i < item.getQuantity(); ++i) {
					cout << "*";
				}
				cout << endl;
			}
			break;

		case 4:
			cout << "Exiting program" << endl;
			exit(0);
		}
	}
}