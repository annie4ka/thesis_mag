#ifndef CHECKER_H
#define CHECKER_H

#include <string>
using namespace std;

class checker{
    string arg_name;
public:

    checker(string name=""): arg_name(name){}
    virtual checker * clone () = 0;
    string get_arg_name ()
    {
        return arg_name;
    }

     virtual string toString ()=0;
     virtual bool test(void* tested) = 0;
	 virtual void del(void * tested) = 0;
};


#endif // CHECKER_H
