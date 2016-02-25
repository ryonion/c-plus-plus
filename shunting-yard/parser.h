#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstdlib>
#include <string>
#include <stack>
#include <sstream>
#include "fraction.h"
#include "mixednumber.h"

using namespace std;

class parser
{
    public:
        parser();
        ~parser();
        parser(const parser &other);
        parser& operator=(const parser &other);
        parser(const string &exp);

        string getStr();
        mixedNumber calculate();

    private:
        void copy(const parser &other);
        void translate(const string &exp);

        string translation;
        stack <char> op;
        stack <mixedNumber> num;
};
#endif // PARSER_H
