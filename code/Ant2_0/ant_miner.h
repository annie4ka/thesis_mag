#ifndef ANT_MINER_H
#define ANT_MINER_H
#include "ant_types.h"
#include "ant.h"
#include <iostream>

using namespace std;
struct method_coefs
{
    double alpha;
    double beta;
    double ph_min;
    double ph_max;
    double evap_c;
    int ants_number;
    double covarage;
    method_coefs()
    {
        ph_min=0;
        ph_max=0;
        evap_c=0;
        alpha=0;
        beta=0;
        ants_number = 0;
        covarage = 0;
    }
};
class simpleNode;
class ant_miner
{
public:
    int layer_num;
    double ph_min;
    double ph_max;
    double eva_coef;
    double alpha;
    double beta;
    int ants_number;
    double avg;
    int x_num;
    int y_num;
    double covarage;
    friend class ant;

    simpleNode* start;
    simpleNode* finish;
    vector<vector<void*> > x;
    vector<vector<void*> > y;

    static bool not_used(const pair<checker*,pair<int,int> > base_part )
    {
        return (base_part.second.second==0);
    }
    void make_connections(vector<list<simpleNode*> > nodes,simpleNode* finish);


    base_type get_base(int num, vector<vector<void*> > x, vector <vector<void*> > y, vector< list<checker*> > layers)
    {
        vector<void*>::iterator it;
        list <checker*>::iterator c_it;
        list< pair<checker*, pair<int,int> > > ::iterator b_it;
        base_type base (num);
        for (int i=0; i<num;++i)
        {
            for (c_it = layers[i].begin();c_it!=layers[i].end();++c_it)
                base[i].push_back(pair<checker*,pair<int,int> >((*c_it),pair<int,int>(0,0)));
        }

        for (int i=0;i<num;++i)
        {

            for (it = x[i].begin();it!=x[i].end();++it)
            {
                for (b_it=base[i].begin();b_it!=base[i].end(); ++b_it)
                {
                    if((*b_it).first->test((*it)))
                    {
                        (*b_it).second.first = (*b_it).second.first + 1;
                        (*b_it).second.second = (*b_it).second.second + 1;
                    }
                }
            }
        }
        for (int i=0;i<num;++i)
        {
            for (it = y[i].begin();it!=y[i].end();++it)
            {
                for (b_it=base[i].begin();b_it!=base[i].end(); ++b_it)
                {
                    if((*b_it).first->test((*it)))
                    {
                        (*b_it).second.second = (*b_it).second.second + 1;
                    }
                }
            }
        }
        pre_node_type::iterator d_it;
        for (int i=0;i<num;++i)
        {


           d_it=remove_if( base[i].begin(),base[i].end(),/*(bool (*)(pair<checker*, pair <int,int> >))*/ant_miner::not_used);
           base[i].erase(d_it,base[i].end());
        }

        return base;

    }






void count_probability();


    ant_miner(int num,  base_type base,struct method_coefs K );
    ant_miner(int num, vector<vector<void*> > xx, vector<vector<void*> > yy, vector <list<checker*> > layers, struct method_coefs K):x(num),y(num)
    {
        avg = 0;


        vector <void*>::iterator it_x, it_y;
        for (int i=0;i<num;++i)
        {
            avg += layers[i].size()-1;
            for (it_x = xx[i].begin(); it_x!=xx[i].end();++it_x)
            {
                x[i].push_back((*it_x));
            }
            for (it_y = yy[i].begin(); it_y!=yy[i].end();++it_y)
            {
                y[i].push_back((*it_y));
            }

        }
        avg = avg*1.0/num;
        x_num = x[0].size();
        y_num = y[0].size();
        ant_miner(num,get_base(num,x,y,layers),K);

    }
    ant* iteration();
    void evaporation();
    bool is_converged();


};

#endif // ANT_MINER_H
