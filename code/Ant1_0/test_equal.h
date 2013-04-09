#ifndef TEST_EQUAL_H
#define TEST_EQUAL_H
#include "test_function.h"
#include <sstream>

template <typename T>
class test_equal : public test_function <T>{
    std::string arg_name;
    T value;
   public:

    test_equal( T val, string name):value(val),test_function <T>(name){}
    test_equal (test_equal<T>& t2):test_function <T>(t2.get_arg_name()){

        value = t2.get_value();
    }

    ~test_equal(){
        return;
    }

    T get_value(){
        return value;
    }
    test_function<T> * clone(){
        return new test_equal(*this);
    }

    bool operator() (T tested)
    {
        return tested==value;
    }
    string toString(){
        ostringstream s(ostringstream::out);
        s << this->get_arg_name() << " equals to " << value <<" ";
        return s.str();
    }

};

#endif // TEST_EQUAL_H
