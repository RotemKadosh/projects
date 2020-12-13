#include "sstring.hpp"
#include <cstring> // strlen, memcpy, size_t
#include <iostream>
#include <assert.h>

namespace ilrd
{

    const int g_buff_size =1024;
    char *String::StrDuplicate(const char *str)
    {
    assert(NULL != str);

    const size_t str_len = strlen(str) + NULL_BYTE;
    char *new_str = new char[str_len];
    memcpy(new_str, str, str_len);

    return new_str; 
    }

    String :: String(const char *string) 
                : m_cstr(StrDuplicate(string))
    {}

    String::String(const String& other_)
                    : m_cstr(StrDuplicate(other_.CStr()))
    {}

    String& String::operator=(const String& other_)
    {
        char *other_char_ptr = StrDuplicate(other_.CStr());
        delete[](m_cstr);
        m_cstr = other_char_ptr;    
        return *this;
    }

    String:: ~String()
    {
        delete[](m_cstr);
        m_cstr = NULL;
    }

    size_t String::Length() const
    {
        return strlen(m_cstr);
    }

    const char *String ::CStr() const
    {
        return m_cstr;
    }

    bool operator==(const String& str, const String& str_to_compare)
    {
        return (0 == strcmp(str.CStr(), str_to_compare.CStr()));
    }

    bool operator>(const String& str, const String& str_to_compare)
    {
        return (0 < strcmp(str.CStr(), str_to_compare.CStr()));
    }

    bool operator<(const String& str, const String& str_to_compare)
    {
        return (0 > strcmp(str.CStr(), str_to_compare.CStr()));
    }

    std::ostream& operator<<(std::ostream& os_, const String& str_)
    {
        return os_ << str_.CStr();
    }

    std::istream& operator>>(std::istream& is, String& str)
    {
        char string[ g_buff_size] = {0};
        is >> string;
        str = string;
        return is;
    }
}