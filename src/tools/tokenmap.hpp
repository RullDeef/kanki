#pragma once

#include <map>
#include <string>

template<typename T>
class TokenMap
{
public:
    std::string insert(const T& value);
    bool contains(const std::string& token) const;
    T get(const std::string& token);
    T remove(const std::string& token);

    std::string getToken(const T& value) const;

    void clear();

private:
    std::string generateNewToken();

    std::map<std::string, T> map;
};

#include "imp_tokenmap.hpp"
