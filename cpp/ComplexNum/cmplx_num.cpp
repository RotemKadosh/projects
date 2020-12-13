#include <iostream> //std ::cout, cin;
#include "cmplx_num.hpp"

namespace ilrd
{


inline Complex::Complex(const double real_,const double imaginary_):
                m_real(real_), m_imaginary(imaginary_){}

inline double Complex::GetReal() const
{
    return this->m_real;
}
inline double Complex::GetImaginary() const
{
    return this->m_imaginary;
}

inline void Complex::SetReal(const double value)
{
    this->m_real = value; 
}
inline void Complex::SetImaginary(const double value)
{
    this->m_imaginary = value; 
}
inline Complex& Complex::operator=(const Complex& other_)
{
    
}
inline Complex& Complex::operator+=(const Complex& other_)
{
    
}
inline Complex& Complex::operator-=(const Complex& other_)
{
    
}
inline Complex& Complex::operator*=(const Complex& other_)
{
    
}
inline Complex& Complex::operator/=(const Complex& other_)
{
    
}

inline std::ostream& operator<<(std::ostream& os_, const Complex& cmplx_)
{
    return os_ << cmplx_.GetReal() << "+"<< cmplx_.GetImaginary()<< "i\n";
}
inline std::istream& operator>>(std::istream& is, Complex& cmplx_)
{

}
inline bool operator==(const Complex& cmplx_, const Complex& cmplx_to_compare_)
{
    return();
}
inline bool operator!=(const Complex& cmplx_, const Complex& cmplx_to_compare_);
inline Complex operator+(const Complex& cmplx_, const Complex& cmplx_to_compare_);
inline Complex operator-(const Complex& cmplx_, const Complex& cmplx_to_compare_);
inline Complex operator*(const Complex& cmplx_, const Complex& cmplx_to_compare_);
inline Complex operator/(const Complex& cmplx_, const Complex& cmplx_to_compare_);


}







