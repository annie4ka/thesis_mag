#ifndef TEST_FUNCTION_H
#define TEST_FUNCTION_H
#include <string>
using namespace std;

template <typename T>
class test_function{
    string arg_name;
public:
    test_function(string name): arg_name(name){}
    virtual test_function <T> * clone () = 0;
    string get_arg_name ()
    {
        return arg_name;
    }

      virtual string toString ()=0;
      virtual bool operator ()(T tested)=0;
};

#endif // TEST_FUNCTION_H
