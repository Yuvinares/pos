#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <map>
#include <string>

class ShoppingCart {
public:
    void addItem(const std::string& item);
    void displayCart() const;
    double calculateTotal() const;
    void processPayment(double paidAmount) const;
    void generateReceipt(double paidAmount) const;

private:
    std::map<std::string, int> cart;
};

#endif // SHOPPINGCART_H

