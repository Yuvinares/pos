#include<iostream>
#include<string>
#include <map>
#include <set>
#include <vector>
using namespace std;
// Define the struct to represent each item with its category
struct Item {
    string category;
    double price;
    int stock;

    Item(string category, double price, int stock) : category(category), price(price), stock(stock) {}
};

// Create a map to store the pharmacy items (item_name: Item)
map<string, Item> inventory;

// Function to initialize the inventory map with items
void initializeInventory() {
    vector<pair<string, Item>> items = {
        {"Paracetamol", {"Medicine", 5.0, 10}},
        {"Aspirin", {"Medicine", 3.0, 5}},
        {"Band-Aid", {"First Aid", 2.0, 20}},
        {"Vitamin C", {"Vitamins", 7.5, 15}},
        {"Fish Oil", {"Supplements", 10.0, 12}},
        {"Paracetamol", {"Medicine", 5.0, 100}},
        {"theraflu", {"Medicine", 10.0, 30}},
        {"Multivitamins", {"Supplements", 75.0, 15}},
        {"sweating spray", {"First Aid", 100.0, 50}},
        {"Toothpastes", {"Supplements", 40.0, 55}},
        {"Fish oil & omega 3", {"Supplements", 120.0, 55}},
        {"Afrin Nasal Spray", {"Medicine", 160.0, 30}},
        {"Daytime Cold & Flu Syrup", {"Medicine", 30.0, 50}},
        {"Blink Contacts Eye Drops", {"Medicine", 50.0, 30}},
        {"Eye Wash", {"First Aid", 35.0, 35}},
        {"Hand Sanitizer", {"First Aid", 50.0, 40}},
        {"Hot/cold pack", {"Medicine", 20.0, 30}},
        {"Paracetamol", {"Medicine", 5.0, 100}},
        {"Wart remover Liquid", {"First Aid", 50.0, 56}},
        {"Petroleum Jelly", {"First Aid", 25.0, 120}},
        {"Tablet Cutter", {"Supplements", 10.0, 30}},
        {"Wound Wash", {"First Aid", 35.0, 45}},
        {"Fiber Tabs", {"Supplements", 10.0, 150}},
        {"Milk of Magnesia", {"Supplements", 40.0, 65}},
        {"Mineral Oil", {"Supplements", 110.0, 55}},
        {"Sarna Anti-Itch", {"First Aid", 60.0, 30}},
        {"Zinc Oxide Ointment", {"First Aid", 30.0, 80}},
        {"Vitamin B-12 (1,000mcg)", {"Supplements", 50.0, 100}},
        {"Vitamin C (500mg)", {"Supplements", 35.0, 95}},
        {"Vitamin B-6 (25mg)", {"Supplements", 50.0, 80}},
        {"One-a-day Women’s Vitamin", {"Supplements", 80.0, 100}},
    };

    for (const auto& item : items) {
        inventory[item.first] = item.second;
    }
}

// Create a map to store the cart (item_name: quantity)
map<string, int> cart;

// Function to add items to the cart
void addItemToCart(string item) {
    if (inventory[item].stock > 0) {
        cart[item]++;
        inventory[item].stock--;
        cout << item << " added to cart.\n";
    }
    else {
        cout << "Sorry, " << item << " is out of stock.\n";
    }
}

// Function to display the cart contents
void displayCart() {
    cout << "\n--- Cart Contents ---\n";
    for (const auto& item : cart) {
        cout << item.first << " x" << item.second << "\n";
    }
    cout << "---------------------\n";
}

// Function to calculate the total price
double calculateTotal() {
    double total = 0.0;
    for (const auto& item : cart) {
        total += inventory[item.first].price * item.second;
    }
    return total;
}

// Function to process payment
void processPayment(double paidAmount) {
    double total = calculateTotal();
    double change = paidAmount - total;
    cout << "Total: $" << total << "\n";
    cout << "Paid: $" << paidAmount << "\n";
    cout << "Change: $" << change << "\n";
}

// Function to generate receipt
void generateReceipt(double paidAmount) {
    cout << "\n---------- Receipt ----------\n";
    cout << "Item\t\tPrice\tQty\tTotal\n";

    double total = 0.0;
    for (const auto& item : cart) {
        double itemTotal = inventory[item.first].price * item.second;
        total += itemTotal;
        cout << item.first << "\t$" << inventory[item.first].price << "\t" << item.second << "\t$" << itemTotal << "\n";
    }

    double change = paidAmount - total;
    cout << "\nTotal: $" << total << "\n";
    cout << "Paid: $" << paidAmount << "\n";
    cout << "Change: $" << change << "\n";
    cout << "-----------------------------\n";
}

int main() {
    // Initialize the inventory with items
    initializeInventory();

    // Create a set to store unique categories
    set<string> categories;
    for (const auto& item : inventory) {
        categories.insert(item.second.category);
    }

    string selectedCategory;
    while (true) {
        cout << "Welcome to the Pharmacy Point of Sale!\n";
        cout << "\nAvailable categories:\n";
        int categoryIndex = 1;
        for (const auto& category : categories) {
            cout << categoryIndex << ". " << category << "\n";
            categoryIndex++;
        }

        int selectedCategoryIndex;
        cout << "\nEnter the category number you want to browse (or enter 0 to exit): ";
        cin >> selectedCategoryIndex;

        if (selectedCategoryIndex == 0) {
            // Exit the program
            cout << "\nThank you for shopping with us!\n";
            break;
        }

        // Find the selected category
        int categoryIndexCounter = 1;
        for (const auto& category : categories) {
            if (categoryIndexCounter == selectedCategoryIndex) {
                selectedCategory = category;
                break;
            }
            categoryIndexCounter++;
        }

        cout << "\nAvailable items in " << selectedCategory << ":\n";
        int itemIndex = 1;
        for (const auto& item : inventory) {
            if (item.second.category == selectedCategory) {
                cout << itemIndex << ". " << item.first << " ($" << item.second.price << ") - Stock: " << item.second.stock << "\n";
                itemIndex++;
            }
        }

        int selectedItemIndex;
        cout << "Enter the item number you want to add to the cart (or enter 0 to go back to category selection): ";
        cin >> selectedItemIndex;

        if (selectedItemIndex == 0) {
            // Go back to category selection
            continue;
        }

        // Find the selected item
        string selectedItem;
        itemIndex = 1;
        for (const auto& item : inventory) {
            if (item.second.category == selectedCategory) {
                if (itemIndex == selectedItemIndex) {
                    selectedItem = item.first;
                    break;
                }
                itemIndex++;
            }
        }

        // Add the selected item to the cart
        addItemToCart(selectedItem);
    }

    displayCart();

    double paidAmount;
    cout << "Enter the amount paid: $";
    cin >> paidAmount;

    processPayment(paidAmount);

    generateReceipt(paidAmount);

    return 0;
}
