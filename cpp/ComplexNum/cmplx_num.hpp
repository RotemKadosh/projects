
#ifndef ILRD_94_COMPLEX_HPP
#define ILRD_94_COMPLEX_HPP

#include <iosfwd> // std:: ostream, std:: isrteam


namespace ilrd
{

class Complex
{
public:
    inline Complex(const double real_, const double imaginary_ = 0);    

    inline Complex& operator+=(const Complex& other_);
    inline Complex& operator-=(const Complex& other_);
    inline Complex& operator*=(const Complex& other_);
    inline Complex& operator/=(const Complex& other_);
    
    inline const double GetReal() const;          
    const double GetImaginary() const;         

    inline void SetReal(const double val);
    inline void SetImaginary(const double val);

private:
    double m_real;
    double m_imaginary;
};

inline std::ostream& operator<<(std::ostream& os_, const Complex& cmplx_);
inline std::istream& operator>>(std::istream& is, Complex& cmplx_);
inline bool operator==(const Complex& cmplx_, const Complex& cmplx_to_compare_);
inline bool operator!=(const Complex& cmplx_, const Complex& cmplx_to_compare_);
inline Complex operator+(const Complex& cmplx_, const Complex& cmplx_to_compare_);
inline Complex operator-(const Complex& cmplx_, const Complex& cmplx_to_compare_);
inline Complex operator*(const Complex& cmplx_, const Complex& cmplx_to_compare_);
inline Complex operator/(const Complex& cmplx_, const Complex& cmplx_to_compare_);
} //namespace ilrd

#endif  // ILRD_94_COMPLEX_HPP