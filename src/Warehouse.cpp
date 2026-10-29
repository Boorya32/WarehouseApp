#include "Warehouse.h"
#include "FileIO.h"
#include <algorithm>
#include <iostream>
#include <cctype>

std::string toLower(std::string str) {
    for (char& c : str) c = std::tolower(c);
    return str;
}

void Warehouse::loadFromFile(const std::string& filename) {
    products = FileIO::loadData(filename);
    if (!products.empty()) {
        nextId = products.back().id + 1;
    }
}

void Warehouse::saveToFile(const std::string& filename) {
    FileIO::saveData(filename, products);
}

bool Warehouse::addProduct(const std::string& name, const std::string& category, double price, int quantity) {
    if (name.empty() || category.empty() || price < 0 || quantity < 0) return false;
    products.emplace_back(nextId++, name, category, price, quantity);
    return true;
}

bool Warehouse::editProduct(int id, const std::string& name, const std::string& category, double price, int quantity) {
    for (auto& p : products) {
        if (p.id == id) {
            if (name.empty() || category.empty() || price < 0 || quantity < 0) return false;
            p.name = name; p.category = category; p.price = price; p.quantity = quantity;
            return true;
        }
    }
    return false;
}

bool Warehouse::deleteProduct(int id) {
    auto it = std::find_if(products.begin(), products.end(), [id](const Product& p){ return p.id == id; });
    if (it != products.end()) {
        products.erase(it);
        return true;
    }
    return false;
}

std::vector<Product> Warehouse::searchByName(const std::string& query) {
    std::vector<Product> res;
    std::string q = toLower(query);
    for (const auto& p : products) {
        if (toLower(p.name).find(q) != std::string::npos) res.push_back(p);
    }
    return res;
}

std::vector<Product> Warehouse::filterByCategory(const std::string& category) {
    std::vector<Product> res;
    for (const auto& p : products) {
        if (toLower(p.category) == toLower(category)) res.push_back(p);
    }
    return res;
}

std::vector<Product> Warehouse::filterByPriceRange(double min, double max) {
    std::vector<Product> res;
    for (const auto& p : products) {
        if (p.price >= min && p.price <= max) res.push_back(p);
    }
    return res;
}

void Warehouse::sortByPrice(bool ascending) {
    std::sort(products.begin(), products.end(), [ascending](const Product& a, const Product& b) {
        return ascending ? a.price < b.price : a.price > b.price;
    });
}

void Warehouse::sortByQuantity() {
    std::sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
        return a.quantity < b.quantity;
    });
}

void Warehouse::sortByName() {
    std::sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
        return toLower(a.name) < toLower(b.name);
    });
}

double Warehouse::getTotalValue() {
    double sum = 0;
    for (const auto& p : products) sum += p.price * p.quantity;
    return sum;
}

std::vector<Product> Warehouse::getLowStock(int threshold) {
    std::vector<Product> res;
    for (const auto& p : products) {
        if (p.quantity <= threshold) res.push_back(p);
    }
    return res;
}

std::vector<Product> Warehouse::getTopExpensive(int count) {
    std::vector<Product> sortedProd = products;
    std::sort(sortedProd.begin(), sortedProd.end(), [](const Product& a, const Product& b) {
        return a.price > b.price;
    });
    if (sortedProd.size() > count) sortedProd.resize(count);
    return sortedProd;
}

void Warehouse::printProducts(const std::vector<Product>& list) {
    if (list.empty()) { std::cout << "List is empty.\n"; return; }
    std::cout << "ID | Name | Category | Price | Quantity\n";
    std::cout << "-------------------------------------------------\n";
    for (const auto& p : list) {
        std::cout << p.id << " | " << p.name << " | " << p.category 
                  << " | " << p.price << " | " << p.quantity << "\n";
    }
}