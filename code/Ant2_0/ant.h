#ifndef ANT_H
#define ANT_H
#include "checker.h"
#include "ant_types.h"
#include "edge.h"
class ant_miner;
class simpleNode;
class ant
{

    int layer_num;
    double ph_max;
    double prob;
    bool updated;
    vector<checker*> rule;
    vector <edge*> path;
    double quality;

public:
    bool test(vector<void*> x);
    ant(int num,double ph_max, simpleNode* start,simpleNode* finish);//?
    void update_rule()
    {
        if (!updated)
        {
        for (int i=0;i<=layer_num;++i)
        {
            path[i]->set_pheromone(path[i]->getPheromone()+quality);
        }
        updated = true;
        }
    }


    bool rule_is_finished();
    string to_string_rule();
    double get_quality()
    {
        return quality;
    }
    double get_probability();

    double get_quality(vector<vector<void*> > x, vector<vector<void*> > y);
  //  ~ant();//?

};


#endif // ANT_H

