#ifndef TEST_EQUAL_H
#define TEST_EQUAL_H
#include "checker.h"
#include <sstream>

using namespace std;

template <typename T>
class test_equal : public checker
{
    std::string arg_name;
    T value;
public:
    test_equal( T val, string name):checker(name),value(val)
    {
    }
    test_equal (test_equal<T>& t2):checker(t2.get_arg_name())
    {
        value = t2.get_value();
    }

    ~test_equal(){
        return;
    }

    T get_value(){
        return value;
    }
    checker * clone(){
        return new test_equal(*this);
    }

    bool test (void* tested)
    {
        T* v2 =(T*)tested;
        T v3 = *v2;
        return v3==value;
    }
    string toString(){
        ostringstream s(ostringstream::out);
        s << this->get_arg_name() << " equals to " << value <<" ";
        return s.str();
    }

};
#endif // TEST_EQUAL_H
