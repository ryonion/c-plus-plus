#ifndef FRACTION_H
#define FRACTION_H


#include <iostream>
#include <cstdlib>

using namespace std;

class fraction
{
    public:
        fraction(); //Constructor
        fraction(int n, int d); //Constructor with 2 parameters
        ~fraction(); //Destructor
        fraction(const fraction &other);
        fraction& operator=(const fraction &other);
        fraction& operator+=(const fraction &other); // a += b
        fraction& operator-=(const fraction &other); // a -= b
        fraction& operator*=(const fraction &other); // a *= b
        fraction& operator/=(const fraction &other); // a /= b

        fraction& operator=(int other);
        fraction& operator+=(int other); // a += b
        fraction& operator-=(int other); // a -= b
        fraction& operator*=(int other); // a *= b
        fraction& operator/=(int other); // a /= b

        void setVal(int n, int d); //Mutator
        void getVal(int &n, int &d) ;//Accessor
        void display(ostream &out = cout ) const;

        friend
        fraction operator+(const fraction &x, const fraction &y);

        friend
        fraction operator-(const fraction &x, const fraction &y);

        friend
        fraction operator*(const fraction &x, const fraction &y);

        friend
        fraction operator/(const fraction &x, const fraction &y);
        \
        friend
        ostream& operator<<(ostream &out, const fraction &f);

        friend
        istream& operator>>(istream &in, fraction &f);

        friend
        bool operator==(const fraction &x, const fraction &y);

        friend
        bool operator!=(const fraction &x, const fraction &y);

        friend
        bool operator>=(const fraction &x, const fraction &y);

        friend
        bool operator<=(const fraction &x, const fraction &y);

        friend
        bool operator<(const fraction &x, const fraction &y);

        friend
        bool operator>(const fraction &x, const fraction &y);

    protected:
        int getNumerator() const;
        int getDenominator() const;
        void setNumerator(int n);
        void setDenominator(int d);
        void reduce();

    private:
        int num, denom;

        int gcd(int p, int q);
        void copy(const fraction &other);

};



#endif // FRACTION_H
