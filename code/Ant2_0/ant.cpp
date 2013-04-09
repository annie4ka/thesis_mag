#include "ant.h"
#include "simple_node.h"
#include "super_edge.h"
#include <string>
#include <iostream>
using namespace std;

ant::ant(int num, double ph, simpleNode *start, simpleNode* finish):layer_num(num),quality(-1),ph_max(ph),updated(false)
{
    simpleNode* current = start;
    super_edge* next;
    while (current!=finish)
    {
        next = current->mover.generate();
        current = next->getNext();
        path.push_back(next->get_data());
        if (current!=finish)
        {
            rule.push_back(next->getNext()->get_tester());
        }
    }


}

string ant::to_string_rule()
{
    string temp = rule[0]->toString();
    for (int i=0;i<layer_num;++i)
    {
        temp+=" and ";
        temp+=rule[i]->toString();
    }
    return temp;
}

double ant::get_probability()
{
    double prob = 1;
    for (int i=0; i<layer_num;++i)
    {
        prob *= path[i]->getTransProb();
    }
    return prob;
}

double ant::get_quality(vector<vector<void*> >x, vector<vector<void*> > y)
{
    cout<<"qual="<<quality;
    if (quality!=-1)
        return quality;
    cout<<"!!!";
    if (layer_num<=0)
        return 0;
    int cov_x = 0;
    int cov_y = 0;
    int all_points = x[0].size()+y[0].size();
    cout<<"All "<<all_points<<endl;
    vector < vector<void*>::iterator > point(layer_num);
    for (int i = 0; i<layer_num;++i)
    {
        point[i] = x[i].begin();
    }
    {
        int i = 0;
        bool answer;
        while (i<x[0].size())
        {
            answer = true;
            for (int j=0; j<layer_num;++j)
            {
                answer = answer && rule[j]->test(*(point[j]));
                ++point[j];
            }
            if (answer)
            {
                ++cov_x;
            }
            ++i;

        }
    }

    for (int i = 0; i<layer_num;++i)
    {
        point[i] = y[i].begin();
    }
    {
        int i = 0;
        bool answer;
        while (i<y[0].size())
        {
            answer = true;
            for (int j=0; j<layer_num;++j)
            {
                answer = answer && rule[j]->test(*(point[j]));
                ++point[j];
            }
            if (answer)
            {
                ++cov_y;
            }
            ++i;

        }
    }
    cout<<"cov_x="<<cov_x<<" cov_y="<<cov_y<<endl;
    quality = (cov_x*1.0)/(cov_x+cov_y)+(cov_x+cov_y)/(all_points*1.0);
    cout<<"quality="<<quality<<endl;
    return quality;
}

bool ant::test(vector<void *> x)
{
    bool answer = true;
    for (int i=0;i<layer_num;++i)
    {
        answer = answer && rule[i]->test(x[i]);
    }
    return answer;
}

bool ant::rule_is_finished()
{
    bool answer = true;
    for (int i=0;i<=layer_num;++i)
        answer = answer && ((path[i]->getPheromone()) == ph_max);
    return answer;
}
