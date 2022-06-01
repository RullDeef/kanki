#pragma once

#include <map>
#include <string>
#include <functional>

namespace cli
{
    class Menu
    {
    public:
        using Action = std::function<void()>;
        using Option = std::pair<std::string, Action>;

        Menu();
        Menu(const std::string &title);

        void addOption(const std::string &label, Action action);

        void exit();
        void run(bool infinite = false);

    private:
        std::string title;
        std::map<int, Option> optionMap;

        bool running = false;
    };
} // namespace cli
