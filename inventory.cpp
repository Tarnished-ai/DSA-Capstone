#include "inventory.h"

#include <algorithm>
#include <iomanip>
#include <iostream>

void Inventory::resize() {
    capacity *= 2;
    Product* bigger = new Product[capacity];
    for (int i = 0; i < count; ++i) {
        bigger[i] = items[i];
    }
    delete[] items;
    items = bigger;
}

Inventory::Inventory() : items(new Product[5]), count(0), capacity(5) {}

Inventory::~Inventory() {
    delete[] items;
}

int Inventory::size() const {
    return count;
}

Product& Inventory::at(int index) {
    return items[index];
}

const Product& Inventory::at(int index) const {
    return items[index];
}

int Inventory::findIndexById(int id) const {
    for (int i = 0; i < count; ++i) {
        if (items[i].id == id) return i;
    }
    return -1;
}

bool Inventory::add(const Product& product) {
    if (findIndexById(product.id) != -1) return false;
    if (count == capacity) resize();
    items[count++] = product;
    return true;
}

void Inventory::display() const {
    if (count == 0) {
        std::cout << "\nInventory is empty.\n";
        return;
    }
    printHeader();
    for (int i = 0; i < count; ++i) {
        printProduct(items[i]);
    }
}

void Inventory::printHeader() {
    std::cout << "\n" << std::left << std::setw(6) << "ID"
              << std::setw(25) << "Product" << std::setw(18) << "Category"
              << std::setw(14) << "Brand" << std::right << std::setw(12) << "Price"
              << std::setw(10) << "Stock" << "\n";
    std::cout << std::string(85, '-') << "\n";
}

void Inventory::printProduct(const Product& product) {
    std::cout << std::left << std::setw(6) << product.id
              << std::setw(25) << product.name.substr(0, 24)
              << std::setw(18) << product.category.substr(0, 17)
              << std::setw(14) << product.brand.substr(0, 13)
              << std::right << std::setw(12) << std::fixed << std::setprecision(2)
              << product.price << std::setw(10) << product.stockQuantity << "\n";
}

void Inventory::sortByPriceDescending() {
    for (int i = 1; i < count; ++i) {
        Product key = items[i];
        int j = i - 1;
        while (j >= 0 && items[j].price < key.price) {
            items[j + 1] = items[j];
            --j;
        }
        items[j + 1] = key;
    }
}

// Binary search uses an ID-sorted copy, so the inventory display order stays unchanged.
void Inventory::binarySearchId(int target) const {
    Product* copy = new Product[count];
    for (int i = 0; i < count; ++i) {
        copy[i] = items[i];
    }

    std::sort(copy, copy + count, [](const Product& a, const Product& b) {
        return a.id < b.id;
    });

    int low = 0;
    int high = count - 1;
    bool found = false;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (copy[mid].id == target) {
            std::cout << "\nProduct found:\n";
            printHeader();
            printProduct(copy[mid]);
            found = true;
            break;
        }
        if (copy[mid].id < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (!found) {
        std::cout << "\nNo product found with ID " << target << ".\n";
    }
    delete[] copy;
}