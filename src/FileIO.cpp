#include "FileIO.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

namespace FileIO {
    std::vector<Product> loadData(const std::string& filename) {
        std::vector<Product> products;
        std::ifstream file(filename);
        
        if (!file.is_open()) {
            std::filesystem::create_directories("data");
            std::ofstream createFile(filename);
            return products;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            Product p;
            char delimiter;
            if (ss >> p.id >> delimiter && std::getline(ss, p.name, ',') &&
                std::getline(ss, p.category, ',') && ss >> p.price >> delimiter >> p.quantity) {
                products.push_back(p);
            }
        }
        file.close();
        return products;
    }

    void saveData(const std::string& filename, const std::vector<Product>& products) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка сохранения!\n";
            return;
        }
        for (const auto& p : products) {
            file << p.id << "," << p.name << "," << p.category << "," 
                 << p.price << "," << p.quantity << "\n";
        }
        file.close();
    }
}