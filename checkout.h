#pragma once

#include <queue>

class Inventory;

struct CartNode {
    int productId;
    int quantity;
    CartNode* next;

    CartNode(int id, int amount);
};

class Cart {
private:
    CartNode* head;

public:
    Cart();
    ~Cart();

    Cart(const Cart&) = delete;
    Cart& operator=(const Cart&) = delete;

    void add(int id, int quantity);
    bool empty() const;
    void display(const Inventory& inventory) const;
    void transferToQueue(std::queue<CartNode*>& checkoutQueue);
    bool checkout(Inventory& inventory, std::queue<CartNode*>& checkoutQueue);
    void clear();
};