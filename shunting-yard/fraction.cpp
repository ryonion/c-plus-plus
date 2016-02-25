#include "fraction.h"


fraction::fraction()//Constructor
{
    num = 0;
    denom = 1;
}

fraction::fraction(int n, int d) //Constructor with 2 parameters
{
    num = n;
    denom = d;
    reduce();
}

fraction::~fraction() //Destructor
{
    num = 0;
    denom = 1;
}

fraction::fraction(const fraction &other)
{
    copy(other);
}
/*
  The following enables me to do
  x = y = z;
*/
fraction& fraction::operator=(const fraction &other)
{
    if(this != &other)
    {
        copy(other);
    }
    return *this;
}

fraction& fraction::operator+=(const fraction &other)
{
    num = other.denom*num + denom*other.num;
    denom *= other.denom;
    reduce();
    return *this;
}// a += b

fraction& fraction::operator-=(const fraction &other)
{
    num = other.denom*num - denom*other.num;
    denom *= other.denom;
    reduce();
    return *this;
} // a -= b

fraction& fraction::operator*=(const fraction &other)
{
   num *= other.num;
   denom *= other.denom;
   return *this;
} // a *= b

fraction& fraction::operator/=(const fraction &other)
{
    num *= other.denom;
    denom *= other.num;
    return *this;
} // a /= b

fraction& fraction::operator+=(int other)
{
    num += other*denom;
    reduce();
    return *this;

} // a += b

fraction& fraction::operator-=(int other)
{
    num -= other*denom;
    reduce();
    return *this;

} // a -= b

fraction& fraction::operator*=(int other)
{
    num *= other;
    reduce();
    return *this;

} // a *= b

fraction& fraction::operator/=(int other)
{
    denom *= other;
    reduce();
    return *this;
} // a /= b

void fraction::setVal(int n, int d) //Mutator
{
   num = n;
   denom = d;
   reduce();
}

void fraction::getVal(int &n, int &d)//Accessor
{
    n = num;
    d = denom;
}

void fraction::display(ostream &out) const
{
    out<<num<<"/"<<denom;
}

int fraction::gcd(int p, int q)
{
    int r;
    while((r = p%q))
    {
        p = q;
        q = r;
    }
    return q;
}

void fraction::copy(const fraction &other)
{
    num = other.num;
    denom = other.denom;
}

void fraction::reduce()
{
    int div = gcd(num, denom);
    num /= div;
    denom /= div;
}

void fraction::setNumerator(int n)
{
    num = n;
}

void fraction::setDenominator(int d)
{
    denom = d;
}


int fraction::getNumerator() const
{
    return num;
}

int fraction::getDenominator() const
{
    return denom;
}

fraction operator+(const fraction &x, const fraction &y)
{
    int newNum = x.num *y.denom + x.denom *y.num,
        newDenom = x.denom * y.denom;
    return fraction(newNum, newDenom);
}

fraction operator-(const fraction &x, const fraction &y)
{
    int newNum = x.num *y.denom - x.denom *y.num,
        newDenom = x.denom * y.denom;
    return fraction(newNum, newDenom);
}

fraction operator*(const fraction &x, const fraction &y)
{
    int newNum = x.num * y.num,
        newDenom = x.denom * y.denom;
    return fraction(newNum, newDenom);
}

fraction operator/(const fraction &x, const fraction &y)
{
    int newNum = x.num *y.denom ,
        newDenom = x.denom * y.num;
    return fraction(newNum, newDenom);
}
\
ostream& operator<<(ostream &out, const fraction &f)
{
    if(f.num == 0)
        out<<0;
    else if(f.denom == 0)
        out<<" undefined answer ";
    else if(f.denom==1)
        out<<f.num;
    else
        out<<f.num<<"/"<<f.denom;
    return out;
}


istream& operator>>(istream &in, fraction &f)
{
    char junk;
    in>>f.num>>junk>>f.denom;
    f.reduce();
    return in;
}


bool operator==(const fraction &x, const fraction &y)
{
    return x.num*y.denom == x.denom*y.num;
}


bool operator!=(const fraction &x, const fraction &y)
{
    return !(x == y);
}


bool operator>=(const fraction &x, const fraction &y)
{
    return x.num*y.denom >= x.denom*y.num;
}


bool operator<=(const fraction &x, const fraction &y)
{
    return x.num*y.denom <= x.denom*y.num;
}


bool operator<(const fraction &x, const fraction &y)
{
    return x.num*y.denom < x.denom*y.num;
}


bool operator>(const fraction &x, const fraction &y)
{
    return x.num*y.denom > x.denom*y.num;
}

