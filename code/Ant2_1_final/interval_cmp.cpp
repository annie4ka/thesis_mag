#include "intervals.h"
bool operator== (ant_interval i1, ant_interval i2)
{
    return (
                ((i2.getB()==-1)&&(i1.getB()==-1)&&(i2.getA()==i1.getA()))||
                ((i2.getB()==-1)&&(i1.getB()!=-1)&&(i1.getA()<=i2.getA())&&(i2.getA()<=i1.getB()))||
                ((i2.getB()!=-1)&&(i1.getB()==-1)&&(i2.getA()<=i1.getA())&&(i1.getA()<=i2.getB()))||
                ((i2.getB()!=-1)&&(i1.getB()!=-1)&&(i2.getA()==i1.getA())&&(i2.getB()==i1.getB()))
            );
}

bool operator< (ant_interval i1, ant_interval i2)
{
    if(i2.getB()==-1)
    {
        if (i1.getB()==-1)
            throw AntException("Impossible to compare intervals");
        return (i1.getB()<i2.getA());
    }
    else
    {
        if (i1.getB()==-1)
        {
            if(i2.getB()==-1)
            {
                throw AntException("Impossible to compare intervals");
            }
            else
            {
                return (i1.getA() < i2.getA());
            }
        }
        else
        {
            return (i1.getB() <= i2.getA());
        }


    }
}
bool operator<= (ant_interval i1, ant_interval i2)
{
    return ((i1==i2)||(i1<i2));
}
bool operator>(ant_interval i1, ant_interval i2)
{
    return (! (i1<=i2));
}
bool operator>=(ant_interval i1, ant_interval i2)
{
    return ((i1==i2)||(i1>i2));
}
bool operator!= (ant_interval i1, ant_interval i2)
{
    return (!(i1==i2));
}
