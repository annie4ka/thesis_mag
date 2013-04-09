#ifndef TEST_BETWEEN_H
#define TEST_BETWEEN_H

#include <sstream>
#include "checker.h"

using namespace std;

template <typename T>
class test_between : public checker{
    string arg_name;
    T value1;
    T value2;
   public:
    test_between( T val1, T val2, string name):checker(name), value1(val1),
        value2(val2){}
    test_between (test_between<T>& t2): checker (t2.get_arg_name())
    {

        value1 = t2.get_first_value();
        value2 = t2.get_second_value();
    }

    ~test_between(){
        return;
    }

    T get_first_value ()
    {
        return value1;
    }

    T get_second_value ()
    {
        return value2;
    }

    checker * clone()
    {
        return new test_between (*this);
    }

    bool  test(void* tested)
    {
        T* v1 = (T*)tested;
        T v2 = (*v1);
        return ((v2 >= value1)&&(v2<=value2));
    }

    string toString(){
        ostringstream s (ostringstream::out);
        s << arg_name << " is more or equal than " <<
             value1 <<" and less or equal than " << value2 << " ";
        return s.str();
    }

};
#endif // TEST_BETWEEN_H
