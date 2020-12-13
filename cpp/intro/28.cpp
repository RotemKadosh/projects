#include <iostream>

class X
{
public:
    X() : m_id(++s_cntrXXXXXXXXXXX) {};
    int GetId() {std::cout << m_id<< std::endl; return m_id;}

    private:
    int m_id;
    static int s_cntrXXXXXXXXXXX;
};

int X::s_cntrXXXXXXXXXXX = 4;

int main()
{
    X x1;
    X x2;
    x1.GetId();
    x2.GetId();
}
