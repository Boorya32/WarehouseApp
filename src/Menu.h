#pragma once
#include "Warehouse.h"

class Menu {
private:
    Warehouse warehouse;
    std::string filename;

    int readInt(const std::string& prompt);
    double readDouble(const std::string& prompt);
    std::string readString(const std::string& prompt);

public:
    Menu();
    void run();
};