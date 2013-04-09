#ifndef EDGE_H
#define EDGE_H
#include <base_edge.h>
#include <base_graph_node.h>

template < typename T>
class edge : public base_edge{
    T * next;
    double pheromone_value;
    double trans_probability;
public:
    edge (double trans_p, double ph_value, T* next_node):base_edge(),trans_probability(trans_p),pheromone_value(ph_value)
    {
        next_node->Link();
        next=next_node;
    }
    void set_pheromone(double ph_value)
    {
        pheromone_value = ph_value;
    }

    double get_pheromone()
    {
        return pheromone_value;
    }

    void set_probability (double probability)
    {
        trans_probability = probability;
    }


    double get_probability ()
    {
        return trans_probability;
    }

    double get_next_h()
    {
        return next->get_heuristic();
    }


    node_type get_next_type()
    {
        return next->get_type();
    }

    T* get_next()
    {
        return next;
    }

    ~edge()
    {
        //next->UnLink();
    }






};

#endif // EDGE_H
