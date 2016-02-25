#include "mixednumber.h"
#include <sstream>

mixedNumber::mixedNumber()
{
    setValue(0,0,1);
}

mixedNumber::mixedNumber(int w, int n, int d)
{
    setValue(w,n,d);
}

//int finddigit(int x)
//{
//    int digits=0;
//    while(x>0)
//    {
//        x/=10;
//        digits++;
//    }

//    return digits;
//}
mixedNumber::~mixedNumber()
{
    nukem();
}

mixedNumber::mixedNumber(const mixedNumber &other)
{
    copy(other);
}

mixedNumber& mixedNumber::operator=(const mixedNumber &other)
{
    if(this != &other)
        copy(other);
    return *this;
}

void mixedNumber::setValue(int w, int n, int d)
{
    bool negative_whole = (w < 0), negative_num = (n < 0);

    setNumerator(abs(w)*d + abs(n) );
    setDenominator(d);
    reduce();   
    if(!negative_num)   //positive numerator
        setNumerator(getNumerator()*(negative_whole ? -1 : 1));
    else                //numerator negative
        setNumerator(getNumerator()*(negative_whole ? 1 : -1));
}

void mixedNumber::copy(const mixedNumber &other)
{
    int n = other.getNumerator();
    setNumerator(n);
    setDenominator(other.getDenominator());
}

ostream& operator<<(ostream &out, const mixedNumber &number)
{


    int whole = number.getNumerator() / number.getDenominator(),
        num = number.getNumerator() % number.getDenominator();

    if(whole == 0)
    {
        if(number.getNumerator() != 0)
            out << number.getNumerator() << "/" << number.getDenominator();
        else
            out << "0";
    }
    else
    {
        if(num == 0)        // integer
            out << whole;
        else
            out<<whole<<" "<<abs(num)<<"/"<<number.getDenominator();
    }

//    if(num == 0)
//    {
//        cout << whole;
//    }
//    else if(whole == 0)             //num is not 0
//    {
//       out << num << "/" << number.getDenominator();
//    }
//    else if(num)
//    {
//       out<<whole<<" "<<abs(num)<<"/"<<number.getDenominator();
//    }

    return out;
}

istream& operator>>(istream &in, mixedNumber &number)
{
    int whole, num = 0, denom = 1, pos_spc;
    char junk;
    string num_temp;
    if(in>>whole)
    {
        junk = in.get();
        if(junk == '/')
        {
           num = whole;
           whole = 0;
           in>>denom;

        }
        else if(junk=='.')
        {
            num_temp = in.peek();
            pos_spc = num_temp.find_first_not_of('123456789');
            if (pos_spc >= string::npos)
                num_temp.erase(pos_spc);

            in>>num;
            number.setNumerator(num);
            denom=pow(10, num_temp.length());
            number.setDenominator(denom);
        }
        else if(junk == ' ' && !isdigit(in.peek()) && ( in.peek() != '-')) // integer
        {
            num = 0,
            denom = 1;
        }

        else
        {
            if(junk == ' ' && (isdigit(in.peek()) || (in.peek() == '-')) )// mixnumber with whole numebr
                in>>num>>junk>>denom;
        }

            number.setValue(whole,num,denom);
    }
    return in;
}

mixedNumber operator+(const mixedNumber &x, const mixedNumber &y)
{
    int newNum = x.getNumerator() *y.getDenominator() + x.getDenominator() *y.getNumerator(),
        newDenom = x.getDenominator() * y.getDenominator();
    return mixedNumber(0,newNum, newDenom);
}

mixedNumber operator-(const mixedNumber &x, const mixedNumber &y)
{
    int newNum = x.getNumerator() *y.getDenominator() - x.getDenominator() *y.getNumerator(),
        newDenom = x.getDenominator() * y.getDenominator();

//     cout << "****"<< x.getNumerator() *y.getDenominator();
    return mixedNumber(0,newNum, newDenom);
}

mixedNumber operator*(const mixedNumber &x, const mixedNumber &y)
{
    int newNum = x.getNumerator() * y.getNumerator(),
        newDenom = x.getDenominator() * y.getDenominator();
    return mixedNumber(0,newNum, newDenom);
}

mixedNumber operator/(const mixedNumber &x, const mixedNumber &y)
{
    int newNum = x.getNumerator() *y.getDenominator() ,
        newDenom = x.getDenominator() * y.getNumerator();
    return mixedNumber(0,newNum, newDenom);
}

mixedNumber operator^(const mixedNumber &x, const mixedNumber &y)
{
     long double exp=(long double)y.getNumerator()/y.getDenominator();
     int newNum = pow(x.getNumerator(),exp);
     int newDenom = pow(x.getDenominator(),exp);
//     cout<<"num="<<x.getNumerator()<<"exp="<<exp<<endl;
//     cout<<"newNum="<<newNum<<"newDenom="<<newDenom<<endl;
     return mixedNumber(0,newNum, newDenom);
}

//bool operator==(const mixedNumber &x, const int &y)
//{
//    if(x.num == 0)
//        return (x.whole == y);
//    else
//        return false;
//}
void mixedNumber::nukem()
{
    setVal(0,1);
}
int mixedNumber::getNum() const
{
    return getNumerator();
}
int mixedNumber::getDenom() const
{
    return getDenominator();
}
