#ifndef ANT_EXCEPTION_H
#define ANT_EXCEPTION_H
#include <string>

using namespace std;


class AntException: public exception
{
    const char* message;
public:
    AntException(const char* msg):exception(),message(msg){}
    AntException():exception()
    {
       message = "Unknown runtime error in Ant-Miner...";
    }

    virtual const char* what() const throw()
    {
        return message;
    }
};

#endif // ANT_EXCEPTION_H
