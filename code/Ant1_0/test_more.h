#ifndef TEST_MORE_H
#define TEST_MORE_H
#include "test_function.h"
#include <sstream>

template <typename T>
class test_more : public test_function <T>{
    T value;
   public:
    test_more( T val, string name): value(val),test_function <T> (name){}
    test_more (const test_more <T>& t2)
    {
        test_function <T> (t2.get_arg_name());
        value =  t2.get_value();
    }

    ~test_more(){
        return;
    }


    test_function <T> * clone ()
    {
        return new test_more(*this);
    }

    T get_value (){
        return value;
    }

    bool operator() (T tested)
    {
        return tested > value;
    }
    void toString(){
        ostringstream s (ostringstream::out);
        s << this->get_arg_name() << " is more than " << value <<" ";
        return s.str();
    }

};
#endif // TEST_MORE_H
