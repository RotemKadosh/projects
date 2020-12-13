#ifndef ILRD_94_STRING_HPP
#define ILRD_94_STRING_HPP
#include <iosfwd> // size_t


namespace ilrd
{

class String
{
public:
    String(const char *str_);       // non explicit on purpose
    String(const String& other_); 
    ~String(); 
    String& operator=(const String& other_);
    
    size_t Length() const;          // length of string
    const char* CStr() const;       // get raw string  

private:
    static const size_t NULL_BYTE = 1; 
    char *m_cstr;
};

std::ostream& operator<<(std::ostream& os_, const String& str_);
std::istream& operator>>(std::istream& is, String& str);
bool operator==(const String& str_, const String& str_to_compare_);
bool operator>(const String& str_, const String& str_to_compare_);
bool operator<(const String& str_, const String& str_to_compare_);

} //namespace ilrd

#endif  // ILRD_94_STRING_HPP