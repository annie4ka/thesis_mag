#ifndef SUPER_EDGE_H
#define SUPER_EDGE_H
#include "edge.h"
class simpleNode;
class move_gen;
class ant;
class super_edge
{
    edge* data;
    simpleNode* next;
friend class simpleNode;
friend class move_gen;
friend class ant;
void count_probability();
void count_probability2();
edge* get_data()
{
    return data;
}
simpleNode* getNext()
{
    return next;
}

public:

    super_edge(edge* dat, simpleNode* node)
    {
        dat->Link();
        data = dat;
        next = node;
    }

    //void remove(simpleNode* nod)=0;
    double  get_prob_mul();




    void set_probability(double prob)
    {
        data->set_probability(prob);
    }
    double get_probability()
    {
        return data->getTransProb();
    }

    void set_pheromone(double ph)
    {
        data->set_pheromone(ph);
    }

    double get_pheromone()
    {
        return data->getPheromone();
    }


    ~super_edge()
    {
        data->UnLink();
    }

};

#endif // FORWARD_EDGE_H
