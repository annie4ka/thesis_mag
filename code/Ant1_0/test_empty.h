#ifndef TEST_EMPTY_H
#define TEST_EMPTY_H
#include "test_function.h"
#include <sstream>

template <typename T>
class test_empty : public test_function <T>{

   public:

    test_empty(string name):test_function<T>(name){}
    test_empty (test_empty <T>& t2): test_function <T> (t2.get_arg_name())
    {
    }

    ~test_empty(){
        return;
    }

    test_function <T> * clone (){
        return new test_empty(*this);
    }

    bool operator() (T tested)
    {
        return true;
    }
    string toString(){
        ostringstream s (ostringstream::out);
        s << this->get_arg_name()<< " could be of any value ";
        return s.str();
    }

};

#endif // TEST_EMPTY_H
