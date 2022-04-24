#pragma once

#include <string>
#include <locale>
#include <codecvt>

class Convert
{
public:
    static std::string toString(const std::string& str)
    {
        return str;
    }

    static std::string toString(const std::wstring& str)
    {
        return convertor.to_bytes(str);
    }

    static std::wstring toWString(const std::string& str)
    {
        return convertor.from_bytes(str);
    }

    static std::wstring toWString(const std::wstring& str)
    {
        return str;
    }

private:
    static std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convertor;
};
