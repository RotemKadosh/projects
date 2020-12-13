#include <iostream>

class X
{
public:
    X();
    X(int a_);
    X(int a_, int b_);
    operator int() const;
    void print() const;

    private:
    int m_a;
    double m_b;
};

X::X():m_a(0) , m_b(0){}
X::X(int a_):m_a(a_){}
X::X(int a_, int b_):m_a(a_ + b_){}


X::operator int() const
{
    return m_a;
}

void X::print() const
{
    std::cout << "X::print " << m_a << std::endl;
}

void Fifi(X& x_)
{
    std::cout << "Fifi " << x_ << std::endl;
    x_.print();
}

int main()
{
    X x1(7);
    Fifi(x1);//1
    Fifi(X(7));//2

    X x2;
    Fifi(9);
    //Fifi(3,4);
    double a = x1 * 3.5;
    std::cout << a  <<'\n';

    return 0;
}