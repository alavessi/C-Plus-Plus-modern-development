#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <exception>

int gcd(int a, int b)
{
    if (b==0)
        return a;
    return gcd(b,a%b);
}

class Rational
{
public:
    Rational()
    {
        numerator=0;
        denominator=1;
    }

    Rational(long new_numerator, long new_denominator)
    {
        if (new_denominator==0)
            throw std::invalid_argument("Invalid argument");
        if (new_numerator==0)
        {
            numerator=0;
            denominator=1;
        }
        else
        {
            int GCD = gcd(abs(new_numerator), abs(new_denominator));
            numerator = ((new_numerator * new_denominator > 0) ? 1 : -1) * abs(new_numerator) / GCD;
            denominator = abs(new_denominator) / GCD;
        }
    }

    int Numerator() const
    {
        return numerator;
    }

    int Denominator() const
    {
        return denominator;
    }

    friend Rational operator+(const Rational& a, const Rational& b)
    {
        return Rational(a.Numerator() * b.Denominator() + a.Denominator() * b.Numerator(), a.Denominator() * b.Denominator());
    }

    friend Rational operator-(const Rational& a, const Rational& b)
    {
        return Rational (a.Numerator() * b.Denominator() - a.Denominator() * b.Numerator(), a.Denominator() * b.Denominator());
    }

    friend Rational operator*(const Rational& a, const Rational& b)
    {
        return Rational (a.Numerator() * b.Numerator(), a.denominator * b.denominator);
    }

    friend Rational operator/(const Rational& a, const Rational& b)
    {
        if (b.Numerator()==0)
            throw std::domain_error("Division by zero");
        return Rational (a.Numerator() * b.Denominator(), a.Denominator() *  b.Numerator());
    }

    friend bool operator==(const Rational& a, const Rational& b)
    {
        return a.Numerator() * b.Denominator() == a.Denominator() * b.Numerator();
    }

    friend bool operator<(const Rational& a, const Rational& b)
    {
        return a.Numerator() * b.Denominator() < a.Denominator() * b.Numerator();
    }

    friend std::istream& operator>>(std::istream& stream, Rational& fraction)
    {
        int numerator,denominator;
        if (stream)
        {
            stream>>numerator;
            if (stream.peek()=='/')
            {
                stream.ignore(1);
                if (stream.peek()!=-1 && stream.peek()>='0' && stream.peek()<='9' && stream.eof()!=1)
                    stream>>denominator;
                else
                    return stream;
            }
            else
                return stream;
        }
        else
            return stream;
        if (denominator==0)
            throw std::invalid_argument("Invalid argument");
        fraction.numerator=numerator;
        fraction.denominator=denominator;
        return stream;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Rational& fraction)
    {
        stream<<fraction.Numerator()<<"/"<<fraction.Denominator();
        return stream;
    }

private:
    long numerator,denominator;
};

int main()
{
    Rational a,b;
    char c;
    try
    {
        std::cin>>a>>c>>b;
    }
    catch (std::exception& ex)
    {
        std::cout<<ex.what();
        return 0;
    }
    if (c=='+')
        std::cout<<a+b;
    if (c=='-')
        std::cout<<a-b;
    if (c=='*')
        std::cout<<a*b;
    if (c=='/')
    {
        try
        {
            std::cout<<a/b;
        }
        catch (std::exception& ex)
        {
            std::cout<<ex.what();
            return 0;
        }
    }
    return 0;
}
