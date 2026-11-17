#pragma once

#include <string>

struct Product {
    int id;
    std::string name;
    std::string category;
    std::string brand;
    double price;
    int stockQuantity;
};

class Inventory {
private:
    Product* items;
    int count;
    int capacity;

    void resize();

public:
    Inventory();
    ~Inventory();

    Inventory(const Inventory&) = delete;
    Inventory& operator=(const Inventory&) = delete;

    int size() const;
    Product& at(int index);
    const Product& at(int index) const;

    int findIndexById(int id) const;
    bool add(const Product& product);
    void display() const;

    static void printHeader();
    static void printProduct(const Product& product);

    void sortByPriceDescending();
    void binarySearchId(int target) const;
};