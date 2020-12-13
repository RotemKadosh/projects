#include "sstring.hpp"
#include <cstring> // strlen, memcpy, size_t
#include <iostream>
#include <assert.h>


ilrd :: String :: String(const char *string) // : m_cstr(NULL)
{
    assert(NULL != string);
    const size_t length = strlen(string) + NULL_BYTE;
    m_cstr = new char[length];
    memcpy(m_cstr, string, length);
}

ilrd::String::String(const String& other_)
{
  
    const char *other_char_ptr = other_.CStr();
    const size_t length = strlen(other_char_ptr) + NULL_BYTE;
    m_cstr = new char[length];
    memcpy(m_cstr, other_char_ptr, length);
}

ilrd::String& ilrd::String::operator=(const String& other_)
{
    const char *other_char_ptr = other_.CStr();
    size_t length = strlen(other_char_ptr) + NULL_BYTE;
    char *tmpStr = new char[length];
    memcpy(tmpStr, other_char_ptr, length);
    delete[](m_cstr);
    m_cstr = tmpStr;    
    return *this;
}

ilrd::String:: ~String()
{
    delete[](m_cstr);
    m_cstr = NULL;
}

size_t ilrd::String::Length() const
{
    return strlen(m_cstr);
}

const char *ilrd :: String ::CStr() const
{
    return m_cstr;
}

bool ilrd::operator==(const String& str, const String& str_to_compare)
{
    return (0 == strcmp(str.CStr(), str_to_compare.CStr()));
}

bool ilrd::operator>(const String& str, const String& str_to_compare)
{
    return (0 < strcmp(str.CStr(), str_to_compare.CStr()));
}

bool ilrd::operator<(const String& str, const String& str_to_compare)
{
    return (0 > strcmp(str.CStr(), str_to_compare.CStr()));
}

std::ostream& ilrd::operator<<(std::ostream& os_, const String& str_)
{
    return os_ << str_.CStr();
}

std::istream& ilrd::operator>>(std::istream& is, String& str)
{
    const int max_line_size = 300;
    char string[max_line_size] = {0};
    is >> string;
    str = string;
    return is;
}