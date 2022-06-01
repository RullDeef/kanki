#pragma once

#include "uuid.h"
#include <iostream>
#include <optional>

using UUID = uuids::uuid;

template <typename Char>
std::basic_ostream<Char> &operator<<(std::basic_ostream<Char> &stream, const UUID &id)
{
    return stream << uuids::to_string<Char>(id);
}

template <typename Char>
std::basic_istream<Char> &operator>>(std::basic_istream<Char> &stream, UUID &id)
{
    std::basic_string<Char> string;
    stream >> string;
    id = *UUID::from_string(string);
    return stream;
}
