#include "shoppingcart.h"
#include "pharmacyitem.h"
#include <iostream>
void ShoppingCart::addItem(const std::string& item) {
    if (inventory[item].stock > 0) {
        cart[item]++;
        inventory[item].stock--;
        std::cout << item << " added to cart.\n";
    }
    else {
        std::cout << "Sorry, " << item << " is out of stock.\n";
    }
}

void ShoppingCart::displayCart() const {
    std::cout << "\n--- Cart Contents ---\n";
    for (const auto& item : cart) {
        std::cout << item.first << " x" << item.second << "\n";
    }
    std::cout << "---------------------\n";
}

double ShoppingCart::calculateTotal() const {
    double total = 0.0;
    for (const auto& item : cart) {
        total += inventory[item.first].price * item.second;
    }
    return total;
}

void ShoppingCart::processPayment(double paidAmount) const {
    double total = calculateTotal();
    double change = paidAmount - total;
    std::cout << "Total: $" << total << "\n";
    std::cout << "Paid: $" << paidAmount << "\n";
    std::cout << "Change: $" << change << "\n";
}

void ShoppingCart::generateReceipt(double paidAmount) const {
    std::cout << "\n---------- Receipt ----------\n";
    std::cout << "Item\t\tPrice\tQty\tTotal\n";

    double total = 0.0;
    for (const auto& item : cart) {
        double itemTotal = inventory[item.first].price * item.second;
        total += itemTotal;
        std::cout << item.first << "\t$" << inventory[item.first].price << "\t" << item.second << "\t$" << itemTotal << "\n";
    }

    double change = paidAmount - total;
    std::cout << "\nTotal: $" << total << "\n";
    std::cout << "Paid: $" << paidAmount << "\n";
    std::cout << "Change: $" << change << "\n";
    std::cout << "-----------------------------\n";
}
