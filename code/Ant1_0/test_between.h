#ifndef TEST_BETWEEN_H
#define TEST_BETWEEN_H

#include "test_function.h"

template <typename T>
class test_between : public test_function <T>{
    string arg_name;
    T value1;
    T value2;
   public:
    test_between( T val1, T val2, string name): value1(val1),
        value2(val2),test_function <T>(name){}
    test_between (test_between<T>& t2): test_function <T> (t2.get_arg_name())
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

    test_function <T> * clone()
    {
        return new test_between (*this);
    }

    bool operator() (T tested)
    {
        return ((tested >= value1)&&(tested<=value2));
    }
    string toString(){
        ostringstream s (ostringstream::out);
        s << arg_name << " is more or equal than " <<
             value1 <<" and less or equal than " << value2 << " ";
        return s.str();
    }

};

#endif // TEST_BETWEEN_H
