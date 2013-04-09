#ifndef INTERVALS_H
#define INTERVALS_H
#include "ant_exception.h"
#include <iostream>
using namespace std;
class ant_interval
{
    double a;
    double b;
    //simpleNode* next;
  //  friend class ant_miner;
public:
    ant_interval (double aa,double bb)
    {
        if (bb!=-1)
        {
            if((bb<aa)||(aa<0)||(bb<0)||(aa>1)||(bb>1))
            {
                cout<<aa<<" "<<bb<<endl;
                throw AntException("Wrong intervals for move generator1");
            }
        }
        else
        {
            if((aa>1)||(aa<0))
                throw AntException("Wrong number for move generator2");
        }
        a=aa;
        b=bb;
    }

    ant_interval (double aa):a(aa),b(-1){}
    double getA()
    {
        return a;
    }
    double getB()
    {
        return b;
    }


/*    bool operator == (interval i2)
    {
        return (
                    ((i2.getB()==-1)&&(this->b==-1)&&(i2.getA()==this->a))||
                    ((i2.getB()==-1)&&(this->b!=-1)&&(this->a<=i2.getA())&&(i2.getA()<=this->b))||
                    ((i2.getB()!=-1)&&(this->b==-1)&&(i2.getA()<=this->a)&&(this->a<=i2.getB()))||
                    ((i2.getB()!=-1)&&(this->b!=-1)&&(i2.getA()==this->a)&&(i2.getB()==this->b))
                );
    }

    bool operator< (interval i2)
    {
        if(i2.getB()==-1)
        {
            if (this->b==-1)
                throw AntException("Impossible to compare intervals");
            return (this->b<i2.getA());
        }
        else
        {
            if (this->b==-1)
            {
                if(i2.getB()==-1)
                {
                    throw AntException("Impossible to compare intervals");
                }
                else
                {
                    return (this->a < i2.getA());
                }
            }
            else
            {
                return (this->b <= i2.getA());
            }


        }
    }
    bool operator<= (interval i2)
    {
        return (((*this)==i2)||((*this)<i2));
    }
    bool operator>(interval i2)
    {
        return (! ((*this)<=i2));
    }
    bool operator>=(interval i2)
    {
        return (((*this)==i2)||((*this)>i2));
    }
    bool operator!= (interval i2)
    {
        return (!((*this)==i2));
    }*/
};


#endif // INTERVALS_H
