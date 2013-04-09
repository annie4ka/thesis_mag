#include "simple_node.h"
#include "ant_miner.h"
#include "ant.h"
#include <math.h>
void ant_miner::count_probability()
{
    start->count_probability();
}

bool ant_miner::is_converged()
{
    bool answer;
    vector <int> *max_e = new vector <int>;
    vector <int> *min_e = new vector <int>;
    vector <int> *other_e = new vector <int>;
    for (int i=0;i<=layer_num;++i)
    {
        (*max_e).push_back(0);
        (*min_e).push_back(0);
        (*other_e).push_back(0);
    }
    start->count_convergence(min_e,other_e,max_e,0,ph_max,ph_min);
    answer = true;
    for (int i=0; ((i<=layer_num)&&answer);++i)
    {
        answer = answer && ((*min_e)[i]==0)
                &&((*max_e)[i]==1)&&((*other_e)[i]==0);
    }
    delete max_e;
    delete min_e;
    delete other_e;
    return answer;
}

void ant_miner::make_connections(vector<list<simpleNode*> > nodes,simpleNode* finish)
{
    list<simpleNode*>::iterator n_it_1, n_it_2;
    for (n_it_2 = nodes[0].begin();n_it_2!=nodes[0].end();++n_it_2)
    {
        simpleNode::connect(start,(*n_it_2),ph_max);
    }

    for (int i=0;i<(layer_num-1);++i)
    {
        for (n_it_1 = nodes[i].begin();n_it_1!=nodes[i].end();++n_it_1)
        {
            for (n_it_2 = nodes[i+1].begin();n_it_2!=nodes[i+1].end();++n_it_2)
            {
                simpleNode::connect((*n_it_1),(*n_it_2),ph_min);
            }
        }
    }
    for (n_it_1 = nodes[layer_num-1].begin();n_it_1!=nodes[layer_num-1].end();++n_it_1)
    {
        simpleNode::connect((*n_it_1),finish,ph_min);
    }
}


ant_miner::ant_miner(int num,  base_type base,struct method_coefs K ):
    layer_num(num),ph_min(K.ph_min),ph_max(K.ph_max),eva_coef(K.evap_c), alpha(K.alpha),beta(K.beta),
    ants_number(K.ants_number),covarage(K.covarage)
{
    cout<<eva_coef<<endl;
    start = new simpleNode(new test_empty("start"),1,1);
    finish = new simpleNode (new test_empty("finish"),1,1);
    vector <list<simpleNode*> > nodes (layer_num);
    pre_node_type::iterator it;

    for (int i=0;i<layer_num;++i)
    {
        for (it = base[i].begin();it!=base[i].end();++it )
          {
            cout<<(*it).first->toString()<<" "<<(*it).second.second<<" "<<(*it).second.first<<endl;
            nodes[i].push_back(new simpleNode((*it).first,(*it).second.second,(*it).second.first));
        }
    }

    make_connections(nodes,finish);



    count_probability();
    cout<<"done!!"<<endl;
  iteration();
}

void ant_miner::evaporation()
{
    start->evaporate(this->eva_coef);
}

ant* ant_miner::iteration()
{

    ant* best_ant;
    int best_num;
    double best_quality;
    {
        vector <ant*> method_agents;
    for (int i=0; i<ants_number;++i)
    {
        method_agents.push_back(new ant(layer_num,ph_max,start,finish));
    }


    best_num = 0;
    best_quality = method_agents[best_num]->get_quality();
    for (int i=1; i<ants_number;++i)
    {
        if (method_agents[i]->get_quality()>best_quality)
        {
            best_num = i;
            best_quality = method_agents[i]->get_quality();
        }
    }


    for (int i=0;i<ants_number;++i)
    {
        if (i==best_num)
        {
            best_ant = method_agents[best_num];
            method_agents[best_num]=null;
        }
        else
            delete method_agents [i];

    }
    }
    evaporation();
    best_ant->update_rule();
    cout<<"q"<<best_ant->get_quality()<<endl;
    ph_max = best_ant->get_quality()/(1-eva_coef);
    ph_min = (ph_max*(1-pow(best_ant->get_probability(),1.0/layer_num)))/((avg-1)*(best_ant->get_probability()));
    cout<<"ph_min="<<ph_min<<" ph_max="<<ph_max<<endl;


}

