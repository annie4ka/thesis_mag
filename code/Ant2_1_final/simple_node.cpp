#include "edge.h"
#include "simple_node.h"
#include "move_gen.h"
#include "super_edge.h"
#include <iostream>


simpleNode::simpleNode(checker* test, int al,int cor):
    correct(cor),all(al),tester(test),owners(0),mover()
{
    if (correct>all)
    {
        correct=0;
        all=0;
        throw AntException("Contradictory arguments for simple graph node...");
    }
    if (all<0)
    {
        correct = 0;
        all = 0;
        throw AntException("Imposible argument all = 0 in simple graph node... ");
    }
    if (all==0)
    {
        heuristic=0;
    }
    else
    {
        heuristic=correct/(all*1.0);
    }
}


	void simpleNode::recount_heuristic (int i,vector<vector<void*>>x,vector<vector<void*>>y)
	{
		if ((i>=0)&&(i<x.size()))
		{
		correct = 0;
		all = 0;
		for(int j = 0;j<x[i].size();++j)
		{
			if(tester->test(x[i][j]))
			{
				++correct;
				++all;
			}
		}
			for(int j = 0;j<y[i].size();++j)
		{
			if(tester->test(y[i][j]))
			{
				++all;
			}
		}

			 if (correct>all)
    {
        correct=0;
        all=0;
        throw AntException("Contradictory arguments for simple graph node...");
    }
    if (all<0)
    {
        correct = 0;
        all = 0;
        throw AntException("Imposible argument all = 0 in simple graph node... ");
    }
    if (all==0)
    {
        heuristic=0;
    }
    else
    {
        heuristic=correct/(all*1.0);
    }
		
		}
		else
		{
			correct =1 ;
			all =1;
			heuristic = 1;
		}
		for (list<super_edge*>::iterator it = to_next_layer.begin();it!=to_next_layer.end();++it)
		{
			(*it)->getNext()->recount_heuristic(i+1,x,y);
		}

	}
inline void  simpleNode::add_forward_edge(simpleNode* node, edge* data)
{
    to_next_layer.push_back(new super_edge(data,node));
}
inline void  simpleNode::add_back_edge(simpleNode* node, edge* data)
{
    to_previous_layer.push_back(new super_edge(data,node));
}

void simpleNode::count_layer_prob()
{
    list<super_edge*>::iterator it;
    double sum = 0;
    for( it=to_next_layer.begin();it!=to_next_layer.end();++it)
    {
        sum+=(*it)->get_prob_mul();
    }
    layer_probability = sum;
	//cout<<"layer: "<<tester->toString()<<" :"<<layer_probability<<endl;
//
}
void simpleNode::evaporate(double po)
{

    list<super_edge*>::iterator it;

    for( it=to_next_layer.begin();it!=to_next_layer.end();++it)
    {
       
        (*it)->set_probability((*it)->get_probability()*po);
        ((*it)->getNext())->evaporate(po);

    }
}
void simpleNode::count_convergence(vector<int> *min_e, vector<int> *other_e, vector<int> *max_e, int layer, double ph_max, double ph_min)
{
    list<super_edge*>::iterator it;
    for(it=to_next_layer.begin();it!=to_next_layer.end();++it)
    {
        if ((*it)->get_pheromone() == ph_max)
        {
            ++(*max_e)[layer];
        }
        else
            if ((*it)->get_pheromone() == ph_min)
            {
                ++(*min_e)[layer];
            }
            else
                ++(*other_e)[layer];
        (*it)->getNext()->count_convergence(min_e,other_e,max_e,layer+1,ph_max,ph_min);
    }

}

void simpleNode::count_probability()
{
    count_layer_prob();
    list<super_edge*>::iterator it;
    for(it=to_next_layer.begin();it!=to_next_layer.end();++it)
    {
		if (layer_probability==0)
            (*it)->set_probability(0);
        else
            (*it)->set_probability(((*it)->get_prob_mul())/layer_probability);
	//	cout<<"from: "<<tester->toString()<<" to:"<<(*it)->getNext()->toString()<<" :"<<(*it)->get_probability()<<endl;
       	(*it)->count_probability();


    }
    mover.change(to_next_layer);
}



void simpleNode::count_probability2()
{
      list<super_edge*>::iterator it;
    for(it=to_next_layer.begin();it!=to_next_layer.end();++it)
    {
		(*it)->set_probability(1.0/to_next_layer.size());
        (*it)->count_probability2();


    }
    mover.change(to_next_layer);
}


void simpleNode::connect (simpleNode* first, simpleNode* second, double pheromone)
{
    edge* data = edge::make_edge(pheromone);
    first->add_forward_edge(second,data);
    second->add_back_edge (first,data);
}

