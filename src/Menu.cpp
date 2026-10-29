#include "Menu.h"
#include <iostream>
#include <limits>
#include <windows.h>

Menu::Menu() : filename("data/products.txt") {
SetConsoleCP(1251);
SetConsoleOutputCP(1251);
    
    warehouse.loadFromFile(filename);
}

int Menu::readInt(const std::string& prompt) {
    int val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return val;
        }
        std::cout << "Ошибка ввода! Введите целое число.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double Menu::readDouble(const std::string& prompt) {
    double val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return val;
        }
        std::cout << "Ошибка ввода! Введите число.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string Menu::readString(const std::string& prompt) {
    std::cout << prompt;
    std::string val;
    std::getline(std::cin, val);
    return val;
}

void Menu::run() {
    int choice;
    do {
        std::cout << "\n=== СКЛАД ===\n";
        std::cout << "1. Показать все товары\n2. Добавить товар\n3. Редактировать товар\n";
        std::cout << "4. Удалить товар\n5. Поиск и фильтрация\n6. Сортировка\n";
        std::cout << "7. Аналитика\n8. Сохранить и выйти\n0. Выход без сохранения\n";
        choice = readInt("Ваш выбор: ");

        switch (choice) {
            case 1: warehouse.printProducts(warehouse.searchByName("")); break;
            case 2: {
                std::string name = readString("Название: ");
                std::string cat = readString("Категория: ");
                double price = readDouble("Цена: ");
                int qty = readInt("Количество: ");
                if (warehouse.addProduct(name, cat, price, qty)) std::cout << "Добавлено!\n";
                else std::cout << "Ошибка в данных!\n";
                break;
            }
            case 3: {
                int id = readInt("ID для редактирования: ");
                std::string name = readString("Новое название: ");
                std::string cat = readString("Новая категория: ");
                double price = readDouble("Новая цена: ");
                int qty = readInt("Новое количество: ");
                if (warehouse.editProduct(id, name, cat, price, qty)) std::cout << "Изменено!\n";
                else std::cout << "Товар не найден или ошибка в данных!\n";
                break;
            }
            case 4: {
                int id = readInt("ID для удаления: ");
                if (warehouse.deleteProduct(id)) std::cout << "Удалено!\n";
                else std::cout << "Не найдено!\n";
                break;
            }
            case 5: {
                std::cout << "1. По названию 2. По категории 3. По цене\n";
                int sub = readInt("Выбор: ");
                if (sub == 1) warehouse.printProducts(warehouse.searchByName(readString("Введите часть названия: ")));
                else if (sub == 2) warehouse.printProducts(warehouse.filterByCategory(readString("Категория: ")));
                else if (sub == 3) {
                    double min = readDouble("От: "), max = readDouble("До: ");
                    warehouse.printProducts(warehouse.filterByPriceRange(min, max));
                }
                break;
            }
            case 6: {
                std::cout << "1. По цене (возр) 2. По цене (убыв) 3. По кол-ву 4. По алфавиту\n";
                int sub = readInt("Выбор: ");
                if (sub == 1) warehouse.sortByPrice(true);
                else if (sub == 2) warehouse.sortByPrice(false);
                else if (sub == 3) warehouse.sortByQuantity();
                else if (sub == 4) warehouse.sortByName();
                std::cout << "Отсортировано!\n";
                break;
            }
            case 7: {
                std::cout << "1. Общая стоимость 2. Мало на складе (<=5) 3. Топ-3 дорогих\n";
                int sub = readInt("Выбор: ");
                if (sub == 1) std::cout << "Общая стоимость: " << warehouse.getTotalValue() << "\n";
                else if (sub == 2) warehouse.printProducts(warehouse.getLowStock(5));
                else if (sub == 3) warehouse.printProducts(warehouse.getTopExpensive(3));
                break;
            }
            case 8: 
                warehouse.saveToFile(filename); 
                std::cout << "Сохранено! Выход...\n"; 
                return;
        }
    } while (choice != 0);
}