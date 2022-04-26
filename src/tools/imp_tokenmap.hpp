#pragma once

#include <chrono>
#include <sstream>
#include <algorithm>
#include "logger.hpp"
#include "tokenmap.hpp"

template<typename T>
std::string TokenMap<T>::insert(const T& value)
{
    auto token = generateNewToken();

    map.emplace(std::pair<std::string, T>(token, value));

    return token;
}

template<typename T>
T TokenMap<T>::remove(const std::string& token)
{
    T value = get(token);
    map.erase(token);

    return value;
}

template<typename T>
std::string TokenMap<T>::getToken(const T& value) const
{
    auto it = std::find_if(map.begin(), map.end(), [&value]
        (const std::pair<std::string, T>& pair) {
            return pair.second == value;
        });
    
    if (it == map.end())
    {
        ERROR_METHOD("token not found");
        throw std::runtime_error("bad token");
    }
    
    return it->first;
}

template<typename T>
bool TokenMap<T>::contains(const std::string& token) const
{
    return map.count(token) == 1;
}

template<typename T>
T TokenMap<T>::get(const std::string& token)
{
    if (!contains(token))
    {
        ERROR_METHOD("no such token: " + token);
        throw std::runtime_error("bad token");
    }

    return map.at(token);
}

template<typename T>
void TokenMap<T>::clear()
{
    map.clear();
}

template<typename T>
std::string TokenMap<T>::generateNewToken()
{
    auto tp = std::chrono::system_clock::now();
    auto ticks = tp.time_since_epoch().count();

    std::ostringstream token;
    token << "token#" << ticks;

    return token.str();
}
