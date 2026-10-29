#pragma once
#include <vector>
#include "Product.h"

namespace FileIO {
    std::vector<Product> loadData(const std::string& filename);
    void saveData(const std::string& filename, const std::vector<Product>& products);
}