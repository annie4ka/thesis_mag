#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include "test_function.h"
#include "base_graph_node.h"
#include "edge.h"
#include <time.h>
#include <stdlib.h>
#include <set>


template <typename T1, typename T>
class graph_node : public base_graph_node{
    vector < edge<T> * > edges;
    double heuristic;
    test_function <T1> * test;
public:
    graph_node ( test_function <T1> * t, double h, node_type type = ordinary ):base_graph_node(type)
    {
        test = t->clone();
        heuristic = h;
    }

    string toString ()
    {
        return test->toString();
    }

    int get_degree ()
    {
        return edges.size();
    }

    bool tester (T1 a)
    {
        return (*test)(a);
    }

    double get_heuristic ()
    {
        return heuristic;
    }

    void set_heuristic(double h)
    {
        heuristic = h;
    }

    void Link()
    {
        plus_owner_count();
    }


    void UnLink()
    {
        minus_owner_count();
        if (get_owner_count()==0)
            delete this;
    }

    double get_i_edge_prob(int i)
    {
        if (i>=edges.size())
            return -1;
        return edges[i]->get_next_h();
    }

    void set_i_edge_prob(int i,double prob)
    {
        if (i>=edges.size())
            return;
        edges[i]->set_probability(prob);
    }

    double get_i_edge_next_h(int i)
    {
        if (i>=edges.size())
            return -1;
        return edges[i]->get_probability();
    }

    double get_i_edge_ph(int i)
    {
        if (i>=edges.size())
            return -1;
        return edges[i]->get_pheromone();
    }
    void set_i_edge_ph(int i,double ph)
    {
        if (i<edges.size())
             edges[i]->set_pheromone(ph);
    }

     static graph_node <T1,T> * make (test_function <T1> * t,double h, node_type type =ordinary)
      {
          return new graph_node(t,h,type);
      }

      void add_the_edge (edge <T> * e)
      {
          edges.push_back(e);
      }

      edge <T> * edge_i(int i)
      {
          return edges[i];
      }

      edge <T> * random_edge()
      {

          int i = rand()%edges.size();
          return edges[i];

      }

      ~graph_node()
      {

          edges.clear();
          delete test;
      }

};

#endif // GRAPH_NODE_H
