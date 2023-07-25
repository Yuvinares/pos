#ifndef PHARMACYITEM_H
#define PHARMACYITEM_H

#include <string>

struct PharmacyItem {
    std::string category;
    double price;
    int stock;

    PharmacyItem(std::string category, double price, int stock);
};

#endif // PHARMACYITEM_H
