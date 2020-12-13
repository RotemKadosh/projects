#include <iostream> //std ::cout, cin;
#include "cmplx_num.hpp"

inline ilrd::Complex::Complex(const double real_,const double imaginary_):
                m_real(real_), m_imaginary(imaginary_){}

//ilrd::Complex::Complex(const Complex& other_):
   // m_real(other_.GetReal()), m_imaginary(other_.Getimaginary()){}   


inline const double ilrd::Complex::GetReal() const
{
    return this->m_real;
}
inline const double ilrd::Complex::GetImaginary() const
{
    return this->m_imaginary;
}

inline void ilrd::Complex::SetReal(const double value)
{
    this->m_real = value; 
}
inline void ilrd::Complex::SetImaginary(const double value)
{
    this->m_imaginary = value; 
}
inline ilrd::Complex& ilrd::Complex::operator=(const Complex& other_)
{
    
}
inline ilrd::Complex& ilrd::Complex::operator+=(const Complex& other_)
{
    
}
inline ilrd::Complex& ilrd::Complex::operator-=(const Complex& other_)
{
    
}
inline ilrd::Complex& ilrd::Complex::operator*=(const Complex& other_)
{
    
}
inline ilrd::Complex& ilrd::Complex::operator/=(const Complex& other_)
{
    
}

inline std::ostream& ilrd::operator<<(std::ostream& os_, const ilrd::Complex& cmplx_)
{
    return os_ << cmplx_.GetReal() << "+"<< cmplx_.GetImaginary()<< "i\n";
}
inline std::istream& ilrd::operator>>(std::istream& is, Complex& cmplx_)
{

}
inline bool ilrd::operator==(const Complex& cmplx_, const Complex& cmplx_to_compare_)
{
    return();
}
inline bool ilrd::operator!=(const Complex& cmplx_, const Complex& cmplx_to_compare_);
inline Complex ilrd::operator+(const Complex& cmplx_, const Complex& cmplx_to_compare_);
inline Complex ilrd::operator-(const Complex& cmplx_, const Complex& cmplx_to_compare_);
inline Complex ilrd::operator*(const Complex& cmplx_, const Complex& cmplx_to_compare_);
inline Complex ilrd::operator/(const Complex& cmplx_, const Complex& cmplx_to_compare_);










