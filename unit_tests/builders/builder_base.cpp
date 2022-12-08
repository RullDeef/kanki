#include <random>
#include "builder_base.hpp"

static std::mt19937 generator;

UUID gen_random_uuid()
{
    return uuids::uuid_random_generator(generator)();
}

std::wstring gen_random_string(size_t len)
{
    static const wchar_t chars[] = L" ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::wstring tmp_s;
    tmp_s.reserve(len);

    for (size_t i = 0; i < len; ++i)
        tmp_s += chars[generator() % (sizeof(chars) / sizeof(chars[0]) - 1)];

    return tmp_s;
}
