#include "parser.h"

parser::parser()
{
    translation = "";
}
parser::parser(const string& exp)
{
    translate(exp);
}
parser::~parser()
{
    translation = "";
    while(!op.empty())
        op.pop();
    while(!num.empty())
        num.pop();
}
parser::parser(const parser &other)
{
        copy(other);
}
parser& parser::operator=(const parser &other)
{
    if(this != &other)
        copy(other);
    return *this;
}

void parser::translate(const string &exp)
{
    stringstream ss;
    string temp = exp, whole = "";
    translation = "";
    bool mod_sign = false;

    while(!temp.empty())
    {
        if(temp[0] == '(')
        {
            op.push('(');
            temp.erase(0,1);
        }
        else if (isdigit(temp[0]))      // hit a number
        {
//            cout <<"[first dg: " <<temp[0] << "]\n";
            while(isdigit(temp[0]))   //get a whole number
            {
                whole += temp[0];
                temp.erase(0,1);
            }
            if(mod_sign)
            {
                whole = "-" + whole;
                mod_sign = false;
            }
            if(isspace(temp[0]))    //it can be mixed or whole
            {
                temp.erase(0,1);
                if(isdigit(temp[0]))    // mixed number
                {
                    whole += " ";
                    while(isdigit(temp[0]))   //get the nominator
                    {
                        whole += temp[0];
                        temp.erase(0,1);
                    }
                    temp.erase(0,1); // delete '/'
                    whole += "/";
                    while(isdigit(temp[0]))   //get the denum
                    {
                        whole += temp[0];
                        temp.erase(0,1);
                    }
                }// finish a mixed number.
            }
            else if(temp[0] == '/')   //fraction;
            {
                temp.erase(0,1); // delete '/'
                whole += "/";
                while(isdigit(temp[0]))   //get the denum
                {
                    whole += temp[0];
                    temp.erase(0,1);
                }
            }//  finish a fraction.
            else if(temp[0] == '.')   // decimal
            {
                temp.erase(0,1);
                whole += ".";
                while(isdigit(temp[0]))   //get the decimal part
                {
                    whole += temp[0];
                    temp.erase(0,1);
                }
            }
            whole = "(" + whole + ")";
            translation += whole + " ";
            whole = "";
        }
        else if (temp[0] == '+' || temp[0] == '-')
        {
            if(temp[0] == '-' && isdigit(temp[1]))
                mod_sign = true;
            else if(!op.empty())
            {
                while(op.top() == '*' || op.top() == '/')
                {

                    translation += op.top();
                    if(temp.size()>1)
                        translation += " ";
                    op.pop();
                    if(op.empty())
                        break;
                }
                op.push(temp[0]);
            }
            else
                op.push(temp[0]);
            temp.erase(0,1);
        }
        else if (temp[0] == '*' || temp[0] == '/')
        {
            op.push(temp[0]);
            temp.erase(0,1);
        }
        else if (temp[0] == ')')
        {
            while(op.top() != '(')
            {
                translation += op.top();
                if(temp.size()>1)
                    translation += " ";
                op.pop();
            }
            op.pop();
            temp.erase(0,1);
        }
        else if(!temp.empty())
            temp.erase(0,1);
    }

    while(!op.empty())
    {
        translation += op.top();
        op.pop();
        if(!op.empty())
            translation += " ";
    }
}
string parser::getStr()
{
    return translation;
}
//mixedNumber parser::calculate()
//{
//    bool first_num = true, mod_sign = false;
//    mixedNumber mix1,mix2;
//    stringstream ss;
//    int w=0,n=0,d=1 , dec_c=0 , dec;
//    char junk;
//    string temp = translation, whole = "";
//    while(!temp.empty())
//    {
//        cout << "["<< temp<< "]";
//        if(isdigit(temp[0]))
//        {

//            while(isdigit(temp[0]))   //get a whole number
//            {
//                whole += temp[0];
//                temp.erase(0,1);

//            }
//            if(isspace(temp[0]))    //it can be mixed or whole
//            {
//                temp.erase(0,1);

//                if(isdigit(temp[0]))    // mixed number
//                {
//                    whole += " ";
//                    while(isdigit(temp[0]))   //get the nominator
//                    {
//                        whole += temp[0];
//                        temp.erase(0,1);
//                    }
//                    temp.erase(0,1); // delete '/'
//                    whole += "/";
//                    while(isdigit(temp[0]))   //get the denum
//                    {
//                        whole += temp[0];
//                        temp.erase(0,1);
//                    }
//                    ss.str(whole);
//                    ss >> w >> n >> junk >> d;
//                }
//                else
//                {
//                    ss.str(whole);
//                    ss >> w;
//                }
//                num.push(mixedNumber(w,n,d));
////                cout << "["<<num.top() << "]";
//            }// finish a mixed number.
//            else if(temp[0] == '/')   //fraction;
//            {
//                temp.erase(0,1); // delete '/'
//                whole += "/";
//                while(isdigit(temp[0]))   //get the denum
//                {
//                    whole += temp[0];
//                    temp.erase(0,1);
//                }
//                ss.str(whole);
//                ss >> n >> junk >> d;
//                num.push(mixedNumber(0,n,d));
//            }//  finish a fraction.
//            else if(temp[0] == '.')   // decimal
//            {
//                temp.erase(0,1);
//                whole += ".";
//                while(isdigit(temp[0]))   //get the decimal part
//                {
//                    whole += temp[0];
//                    temp.erase(0,1);
//                    dec_c++;
//                }
//                ss.str(whole);
//                ss >> w >> junk >> n;
//                d = pow(10, dec_c);
//                num.push(mixedNumber(w,n,d));
//            }
//            if(mod_sign)
//            {
//                num.top()=num.top()*mixedNumber(-1,0,1);
//                mod_sign = false;
//            }
//            w = 0;n = 0;d=1;
//            whole = "";
//            first_num = false;
//        }
//        else if(temp[0] == '+' ||temp[0] == '-'||temp[0] == '*'||temp[0] == '/' )
//        {
//            if(temp[0] == '-' && first_num)
//                mod_sign = true;
//            else
//            {
//                mix2 = num.top();
//                num.pop();
//                mix1 = num.top();
//                num.pop();
//                switch(temp[0])
//                {
//                case '+':
//                    num.push(mix1 + mix2);break;
//                case '-':
//                    num.push(mix1 - mix2);break;
//                case '*':
//                    num.push(mix1 * mix2);break;
//                case '/':
//                    num.push(mix1 / mix2);break;
//                default:
//                    cout << "error!";
//                }
//            }
//            temp.erase(0,1);
//        }
//        if(!temp.empty() && !isdigit(temp[0]))
//            temp.erase(0,1);
//        ss.clear();
//        ss.str(" ");
//    }
//    cout << num.top();
//}

void parser::copy(const parser &other)
{
    parser temp(other.translation);
    translation = temp.translation;
    while(!op.empty())
        op.pop();
    while(!num.empty())
        num.pop();
    while(!temp.op.empty())
    {
        op.push(temp.op.top());
        temp.op.pop();
    }
    while(!temp.num.empty())
    {
        num.push(temp.num.top());
        temp.num.pop();
    }
}
