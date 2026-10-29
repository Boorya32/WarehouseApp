#pragma once
#include <string>

class Product {
public:
    int id;
    std::string name;
    std::string category;
    double price;
    int quantity;

    Product() : id(0), price(0.0), quantity(0) {}
    Product(int id, std::string name, std::string category, double price, int quantity)
        : id(id), name(std::move(name)), category(std::move(category)), price(price), quantity(quantity) {}
};