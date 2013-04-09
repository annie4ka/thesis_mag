#ifndef TEST_EMPTY_H
#define TEST_EMPTY_H
#include "checker.h"
#include <sstream>

using namespace std;

class test_empty : public checker{

   public:

    test_empty(string name):checker(name){}
    test_empty (test_empty& t2): checker (t2.get_arg_name())
    {
    }

    ~test_empty(){
        return;
    }

    checker* clone (){
        return new test_empty(*this);
    }

    bool test (void* tested)
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
