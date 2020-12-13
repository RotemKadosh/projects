#ifndef ILRD_94_COMPLEX_IMPL_HPP
#define ILRD_94_COMPLEX_IMPL_HPP

#include <iostream> //std ::cout, cin;
#include <cstring> // memset
#include <cstdlib> // atof;
#include "cmplx_num.hpp"

namespace ilrd
{

    const int buff_size = 1024; // change to max double length

    Complex::Complex(const double real_,const double imaginary_)
    : m_real(real_)
    ,m_imaginary(imaginary_)
    {}

    inline double Complex::GetReal() const
    {
        return this->m_real;
    }

    inline double Complex::GetImaginary() const
    {
        return this->m_imaginary;
    }

    inline void Complex::SetReal(double value)
    {
        this->m_real = value; 
    }

    inline void Complex::SetImaginary(double value)
    {
        this->m_imaginary = value; 
    }

    inline Complex& Complex::operator+=(const Complex& other_)
    {
        Complex tmp(*this + other_);
        *this = tmp;
        return *this;
    }

    inline Complex& Complex::operator-=(const Complex& other_)
    {
        Complex tmp(*this - other_);
        *this = tmp;
        return *this;
    }

    inline Complex& Complex::operator*=(const Complex& other_)
    {
        Complex tmp(*this * other_);
        *this = tmp;
        return *this;
    }

    inline Complex& Complex::operator/=(const Complex& other_)
    {
        Complex tmp( *this  / other_);
        *this = tmp;
        return *this;
    }


    inline std::ostream& operator<<(std::ostream& os_, const Complex& cmplx_)
    {
        return os_ << cmplx_.GetReal() << " + i*("<< cmplx_.GetImaginary()<< ")\n";
    }

    inline std::istream& operator>>(std::istream& is, Complex& cmplx_)
    {
        char buffer[buff_size] = {0};
        is >> buffer;
        cmplx_.SetReal(atof(buffer));
        memset(buffer, 0, buff_size);
        is >> buffer;
        cmplx_.SetImaginary(atof(buffer));
        memset(buffer, 0, buff_size);
        return is;
    }

    inline bool operator==(const Complex& cmplx_, const Complex& cmplx_to_compare_)
    {
        return(cmplx_.GetReal() == cmplx_to_compare_.GetReal() &&
                cmplx_.GetImaginary() == cmplx_to_compare_.GetImaginary() );
    }

    inline bool operator!=(const Complex& cmplx_, const Complex& cmplx_to_compare_)
    {
        return(cmplx_.GetReal() != cmplx_to_compare_.GetReal() ||
                cmplx_.GetImaginary() != cmplx_to_compare_.GetImaginary() );
    }

    inline Complex operator+(const Complex& cmplx_, const Complex& other_)
    {
        return Complex(cmplx_.GetReal() + other_.GetReal(),
                        cmplx_.GetImaginary() + other_.GetImaginary());
    }

    inline Complex operator-(const Complex& cmplx_, const Complex& other_)
    {
            return Complex(cmplx_.GetReal() - other_.GetReal(),
                        cmplx_.GetImaginary() - other_.GetImaginary());
    }

    inline Complex operator*(const Complex& cmplx_, const Complex& other_)
    {
        return Complex(((cmplx_.GetReal()*other_.GetReal()) - 
                        (cmplx_.GetImaginary()* other_.GetImaginary())),
                        ((cmplx_.GetReal()*other_.GetImaginary()) + 
                        (other_.GetReal()*cmplx_.GetImaginary())));
    }

    inline Complex operator/(const Complex& cmplx_, const Complex& other_)
    {
        double a = cmplx_.GetReal();
        double b = cmplx_.GetImaginary();
        double c = other_.GetReal();
        double d = other_.GetImaginary();
        double mult = (1 / ((c * c) + (d * d)));
        return Complex(mult*((a * c) + (d * b)), mult * ((b * c) - (a * d)));
    }

}
#endif //ILRD_94_COMPLEX_IMPL_HPP;






