#ifndef EDGE_H
#define EDGE_H
#include "ant_exception.h"
class edge
{
    double pheromone;
    double trans_probability;
    int edge_num;
public :edge(double ph=0,double prob=0):
        pheromone(0),trans_probability(0),edge_num(0)
    {
        if ((prob>1)||(prob<0))
            throw AntException("Unapropriate probability value");
        if (ph < 0)
            throw AntException("Unapropriate pheromone value");
        pheromone = ph;
        trans_probability = prob;
    };
//public:
    static edge* make_edge(double ph=0,double prob=0)
    {
        return new edge(ph,prob);
    }


    double getPheromone()
    {
        return pheromone;
    }

    double getTransProb()
    {
        return trans_probability;
    }

    void set_pheromone(double ph)
    {
        pheromone = ph;
    }

    void set_probability(double prob)
    {
        if ((prob>1)||(prob<0))
            throw AntException("Unapropriate probability value");
        trans_probability = prob;
    }



    void Link()
    {
        ++edge_num;
        if (edge_num>2)
            throw AntException("One edge points to more than 2 nodes");
    }
    void UnLink()
    {
        if (edge_num==0)
            throw AntException ("Error in edge connections");
        --edge_num;
        if (edge_num == 0)
            delete (this);
    }

    ~edge()
    {
        if (edge_num>0)
            throw AntException("Attempt to delete edge connected to others existent objects");
       return;
    }


};

#endif // EDGE_H
