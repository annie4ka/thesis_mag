#ifndef SIMPLE_NODE_H
#define SIMPLE_NODE_H

#include "ant_exception.h"
#include "checker.h"
#include "ant_miner.h"
#include "super_edge.h"
#include "intervals.h"
#include "move_gen.h"
#include <list>
#include <set>
class edge;
class super_edge;
class ant_miner;
class ant;
class simpleNode
{

    friend class ant;
    friend void super_edge::count_probability();
    friend void ant_miner::count_probability();
    int correct; //общее число точек
    int all;     //число точек, удовлетвор€ющих правилу
    double heuristic;//эвристика дл€ узла
    checker * tester;//правило

    double layer_probability;//коэффициент нормировки веро€тности дл€ данного узла
    move_gen mover;


    int owners;//количество владельцев узла

    checker* get_tester()
    {
        return tester;
    }

    void add_forward_edge(simpleNode* node, edge* data);

    void add_back_edge(simpleNode* node, edge* data);


    void count_layer_prob();
	
	

    void count_probability();
	

public:void count_probability2();
    list<class super_edge*> to_next_layer;//св€зи с узлами следующего уровн€
    list<class super_edge*> to_previous_layer;
    static void connect (simpleNode* first, simpleNode* second, double pheromone);

    string toString()
    {
        return tester->toString();
    }
    double getLayerProb()//?
    {
        return layer_probability;
    }
void recount_heuristic(int i, vector<vector<void*> > x, vector<vector<void*> > y);

   /* void Link()
    {
        ++owners;
    }
    void Unlink()
    {
        --owners;
        if (owners==0)
            delete (*this);
   }*/

    simpleNode(checker* test, int al=0,int cor=0);


    int getCorrect()
    {
        return correct;
    }

    int getAll()
    {
        return all;
    }

    double getHeuristic()
    {
        return heuristic;
    }

 /*   double recount(int in, int al)
    {
        correct = correct + in;
        all = all + al;

        if (correct>all)
        {
            correct=0;
            all=0;
            throw antEx("Contradictory arguments for simple graph node...");
        }
        if (all<0)
        {
            correct = 0;
            all = 0;
            throw antEx("Imposible argument all = 0 in simple graph node... ");
        }

        if (all==0)
        {
            atta=0;
        }
        else
        {
            atta=correct/(all*1.0);
        }
    }
*/

    ~simpleNode()
    {
        /*
        list<super_edge*>::iterator it;
        for(it=to_next_layer.begin();it!=to_next_layer.end();++it)
        {
            (*it)->remove(*this);
            remove(it);
        }
        for (it=to_previous_layer.begin();it!=to_next_layer.end();++it)
        {
            (*it)->remove((*this));
            remove(it);
        }*/
    }

    void evaporate (double po);
    void count_convergence(vector<int>* min_e,vector<int>* other_e, vector<int>* max_e, int layer,double ph_max, double ph_min);

};


#endif // SIMPLE_NODE_H
