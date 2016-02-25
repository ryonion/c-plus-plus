#ifndef MIXEDNUMBER_H
#define MIXEDNUMBER_H
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstdlib>
#include "fraction.h"

using namespace std;

class mixedNumber : public fraction
{
    public:
        mixedNumber();
        mixedNumber(int w, int n = 0, int d = 1);
        ~mixedNumber();
        mixedNumber(const mixedNumber &other);
        mixedNumber& operator=(const mixedNumber &other);

        void setValue(int w, int n = 0, int d = 1);
        int getNum() const;
        int getDenom() const;
        int finddigit(int &x);
        void nukem();

        friend
        ostream& operator<<(ostream &out, const mixedNumber &number);

        friend
        istream& operator>>(istream &in, mixedNumber &number);

        friend
        mixedNumber operator+(const mixedNumber &x, const mixedNumber &y);

        friend
        mixedNumber operator-(const mixedNumber &x, const mixedNumber &y);

        friend
        mixedNumber operator*(const mixedNumber &x, const mixedNumber &y);

        friend
        mixedNumber operator/(const mixedNumber &x, const mixedNumber &y);

        friend
        mixedNumber operator^(const mixedNumber &x, const mixedNumber &y);

        friend
        bool operator==(const mixedNumber &x, const int &y);


    private:
        void copy(const mixedNumber &other);
};

#endif // MIXEDNUMBER_H
