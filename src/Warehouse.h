#pragma once
#include <vector>
#include "Product.h"

class Warehouse {
private:
    std::vector<Product> products;
    int nextId = 1;

public:
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);

    bool addProduct(const std::string& name, const std::string& category, double price, int quantity);
    bool editProduct(int id, const std::string& name, const std::string& category, double price, int quantity);
    bool deleteProduct(int id);

    std::vector<Product> searchByName(const std::string& query);
    std::vector<Product> filterByCategory(const std::string& category);
    std::vector<Product> filterByPriceRange(double min, double max);

    void sortByPrice(bool ascending);
    void sortByQuantity();
    void sortByName();

    double getTotalValue();
    std::vector<Product> getLowStock(int threshold);
    std::vector<Product> getTopExpensive(int count);
    
    void printProducts(const std::vector<Product>& list);
};