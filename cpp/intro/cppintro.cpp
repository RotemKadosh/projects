#include <iostream>
#include "../../ds/stack/stack.h"
int x = 7;
int c = 10;
struct X
{
  explicit X();
  explicit X(int a_, int b_ = 8); //regular, non default constructor
  ~X(); //destuctor
  X(const X& other_); //copy constructor
  //X& operator=(const X& other_); //assignment operator
  int m_a;
  const int m_b;
};


struct Y
{
  explicit Y();
  Y& operator=(const Y& other_); //assignment operator
  X m_x;
  int m_i;
};

inline int rotemmememe()
{
  std :: cout << "kkk";
  return 1;
}

Y::Y(): m_x(2), m_i(rotemmememe())
{
  std::cout << "this" << this << " Y default Ctor.m_a: " << m_x.m_a << " m_b: " << m_x.m_b << std::endl;
}
X::X(): m_a(3), m_b(4)
{
  std::cout << "this" << this << "X default Ctor.m_a: " << m_a << " m_b: " << m_b << std::endl;
}
X::X(int a_, int b_): m_a(a_), m_b(b_)
{
  std::cout << "this: " << this << " X int int Ctor. m_a: " << m_a << " m_b: " << m_b << std::endl;
}

X::X(const X& other_): m_a(other_.m_a), m_b(other_.m_b) //copy constructor
{
  std::cout << "this "<< this << " X copy Ctor. m_a: " << m_a << " m_b: " << m_b << std::endl;
}
/*
X& X::operator=(const X& other_)
{
  m_a = other_.m_a;
  //m_b = other_.m_b;
  std::cout << "this: " << this << " X assignment op. m_a: " << m_a << " does not change m_b: " << m_b << std::endl;
  return *this;
}
*/
X::~X()
{
  std::cout << "this: " << this << " X Dtor. m_a: " << m_a << " m_b: " << m_b << std::endl;
}

Y& Y::operator=(const Y& othre)
{
  m_x.m_a = othre.m_x.m_a;
  m_i = othre.m_i;
  return *this;
}


int main()
 {

 
 

 
  int px = 0;


  
  return 0;
}