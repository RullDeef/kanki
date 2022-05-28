#include <iostream>
#include "menu.hpp"

cli::Menu::Menu()
{
}

cli::Menu::Menu(const std::string &title)
    : title(title + "\n")
{
}

void cli::Menu::addOption(const std::string &label, Action action)
{
    int id = optionMap.size() + 1;
    optionMap[id] = Option{label, action};
}

void cli::Menu::run(bool infinite)
{
    while (true)
    {
        std::cout << title;
        for (auto [id, option] : optionMap)
            std::cout << id << ". " << option.first << std::endl;
        if (infinite)
            std::cout << "0. Выход\n";
        std::cout << "> ";

        int id;
        std::cin >> id;
        std::cin.get();

        if (id == 0)
            break;
        else if (optionMap.count(id) == 0)
            std::cout << "Неверная опция. Повторите попытку\n";
        else
        {
            optionMap[id].second();
            if (!infinite)
                break;
        }
    }
}
