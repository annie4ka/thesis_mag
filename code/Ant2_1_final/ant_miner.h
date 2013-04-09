#ifndef ANT_MINER_H
#define ANT_MINER_H
#include "ant_types.h"
#include "ant.h"
#include "ant.h"
#include <iostream>
#include <fstream>

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
	//fstream& log_file;
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
    double coverage;
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


	 base_type get_base(bool anomaly, int num, vector<vector<void*> > x, vector <vector<void*> > y, vector< list<checker*> > layers)
    {
		fstream not_in;
		not_in.open("not_in_normal.txt",ios::out);
        vector<void*>::iterator it;
        list <checker*>::iterator c_it;
        list< pair<checker*, pair<int,int> > > ::iterator b_it;
        base_type base (num);
        for (int i=0; i<num;++i)
        {
            for (c_it = layers[i].begin();c_it!=layers[i].end();++c_it)
                base[i].push_back(pair<checker*,pair<int,int> >((*c_it),pair<int,int>(0,0)));
        }
		cout<<"base_count"<<endl;
		int count;
        for (int i=0;i<num;++i)
        {

            for (unsigned int j = 0; j<x[i].size();++j)
            {
				
				count = 0;
                for (b_it=base[i].begin();b_it!=base[i].end(); ++b_it)
                {
                    if((*b_it).first->test((x[i][j])))
                    {
                        (*b_it).second.first = (*b_it).second.first + 1;
                        (*b_it).second.second = (*b_it).second.second + 1;
						++count;
                    }
                }
				if (count==1)
				{
					for (int i=0; i<num;++i)
						not_in<<(*(int*)(x[i][j]))<<" ";
					not_in<<endl;
				}
            }
        }
		not_in.close();
		cout<<"x_OK"<<endl;
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
		cout<<"y_OK"<<endl;
        pre_node_type::iterator d_it;
        for (int i=0;i<num;++i)
        {


           d_it=remove_if( base[i].begin(),base[i].end(),/*(bool (*)(pair<checker*, pair <int,int> >))*/ant_miner::not_used);
           base[i].erase(d_it,base[i].end());
		 //  cout<<"SL:"<<base[i].size()<<endl;
        }
		cout<<"remove_OK"<<endl;
        return base;

    }

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
		cout<<"base_count"<<endl;
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
		cout<<"x_OK"<<endl;
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
		cout<<"y_OK"<<endl;
        pre_node_type::iterator d_it;
        for (int i=0;i<num;++i)
        {


           d_it=remove_if( base[i].begin(),base[i].end(),/*(bool (*)(pair<checker*, pair <int,int> >))*/ant_miner::not_used);
           base[i].erase(d_it,base[i].end());
		 //  cout<<"SL:"<<base[i].size()<<endl;
        }
		cout<<"remove_OK"<<endl;
        return base;

    }

	bool is_covered_enough()
	{
		double w = x_num-x[0].size();
	

		w=w/x_num;
		
		return (w>coverage);
	}

	double get_covered()
	{
		double w = x_num-x[0].size();
	

		w=w/x_num;
		return w;
	}

	void recount_heuristic();
	
void count_probability();
void count_probability2();


   void _ant_miner(int num,  base_type base,struct method_coefs K);
    ant_miner(int num, vector<vector<void*> > xx, vector<vector<void*> > yy, vector <list<checker*> > layers, struct method_coefs K):x(num),y(num)
    {
       
	
		cout<<"ant_miner_creation "<<num<<endl;
        vector <void*>::iterator it_x, it_y;
        for (int i=0;i<num;++i)
        {
            
			for (it_x = xx[i].begin(); it_x!=xx[i].end();++it_x)
            {
                x[i].push_back((*it_x));
            }
            for (it_y = yy[i].begin(); it_y!=yy[i].end();++it_y)
            {
                y[i].push_back((*it_y));
            }

        }
        
	//	cout<<"avg="<<avg<<endl;
        x_num = x[0].size();
        y_num = y[0].size();
       // _ant_miner(num,get_base(true,num,x,y,layers),K);
		_ant_miner(num,get_base(num,x,y,layers),K);
    }
    ant* iteration();
    void evaporation();
    bool is_converged();
	double extract(ant * best);


};

#endif // ANT_MINER_H
