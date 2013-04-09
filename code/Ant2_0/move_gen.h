#ifndef MOVE_GEN_H
#define MOVE_GEN_H
#include <map>
#include "super_edge.h"
#include "intervals.h"
#include "interval_cmp.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class move_gen
{
    map<ant_interval,super_edge*> base;
    double random_d()
    {

                return ((double)rand())/RAND_MAX;
    }
public:
    move_gen (list<super_edge*> way)
    {
        srand(time(0));
        double sum = 0;
        for (list<super_edge*>::iterator it = way.begin(); it != way.end(); ++it)
        {
            base.insert(pair <ant_interval,super_edge*> (ant_interval(sum,sum + (*it)->get_probability()),(*it)));
            sum += (*it)->get_probability();
        }
    }

    move_gen ()
    {
        srand(time(0));
    }
    void change (list<super_edge*> way)
    {
        double sum = 0;
        for (list<super_edge*>::iterator it = way.begin(); it != way.end(); ++it)
        {
            base.insert(pair <ant_interval,super_edge*> (ant_interval(sum,sum+(*it)->get_probability()),(*it)));
            sum += (*it)->get_probability();
        }
    }

    super_edge* generate()
    {
       if (base.empty())
            return null;
       double r = random_d();
       return base[ant_interval(r)];
    }
};

#endif // MOVE_GEN_H
