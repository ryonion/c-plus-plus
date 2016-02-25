#include <iostream>
#include "parser.h"
#include <iomanip>

using namespace std;

int main()
{
    string exp;
    cout << "Enter an expression: ";
    getline(cin,exp);
    cout << endl;
    parser p(exp);
    cout << setw(p.getStr().size()+6) << setfill('*')<<" ";
    cout << endl << endl;
    cout << "RPN: " << p.getStr();


    cout << endl << endl;
    return 0;
}

