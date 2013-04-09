#include "simple_node.h"
#include "ant_miner.h"
#include "ant.h"
#include <math.h>
void ant_miner::count_probability()
{
    start->count_probability();
}

void ant_miner::count_probability2()
{
    start->count_probability2();
}


double ant_miner::extract(ant* best)
{
	static int ex_num = 0;
	++ex_num;
	char* c= new char[200];
	itoa(ex_num,c,10);
	fstream fx,fy;
	string name_x = "x";
	name_x.append(c);
	name_x.append(".log");
	string name_y = "y";
	name_y.append(c);
	name_y.append(".log");
	fx.open(name_x,ios::out);
	fy.open(name_y,ios::out);
	int i = 0;
	int prev_size = x[0].size();
	while (i<x[0].size())
	{
		vector<void*> w (layer_num);
		for (int j=0; j<layer_num;++j)
			w[j] = x[j][i];
		if(best->test(w))
		{
			//best->del(w);
			fx<<(*(double*)(w[0]))<<" "<<(*(int*)(w[1]))<<" "<<(*(int*)(w[2]))<<" "<<(*(int*)(w[3]))<<" "<<(*(int*)(w[4]))<<endl;
			for (int j = 0;j<layer_num;++j)
			{
				x[j].erase(x[j].begin()+i);
			}
		}
		else 
			++i;
	}

	i = 0;
	while (i<y[0].size())
	{
		vector<void*> w (layer_num);
		for (int j=0; j<layer_num;++j)
			w[j] = y[j][i];
		if(best->test(w))
		{
			fx<<(*(double*)(w[0]))<<" "<<(*(int*)(w[1]))<<" "<<(*(int*)(w[2]))<<" "<<(*(int*)(w[3]))<<" "<<(*(int*)(w[4]))<<endl;
			for (int j = 0;j<layer_num;++j)
			{
				y[j].erase(y[j].begin()+i);
			}
		}
		else 
			++i;
	}
	recount_heuristic();
	count_probability();
	fx.close();
	fy.close();
	return(((prev_size -x[0].size())*1.0)/(prev_size*1.0));
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
	//	cout<<"min:"<<(*min_e)[i]<<" max:"<<(*max_e)[i]<<" other:"<<(*other_e)[i]<<endl;
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


void ant_miner::_ant_miner(int num,  base_type base,struct method_coefs K )
    {
		fstream log_file;
		log_file.open("log.txt",ios::out);
		
	layer_num = num;
	ph_min = K.ph_min;
	ph_max = K.ph_max;
	eva_coef = K.evap_c;
	alpha = K.alpha;
	beta = K.beta;
	ants_number = K.ants_number;
	coverage = K.covarage;
    cout<<"Graph generation:"<<endl;
    start = new simpleNode(new test_empty("start"),1,1);
    finish = new simpleNode (new test_empty("finish"),1,1);
    vector <list<simpleNode*> > nodes (layer_num);
    pre_node_type::iterator it;
	avg = 0;
    for (int i=0;i<layer_num;++i)
    {
		  for (it = base[i].begin();it!=base[i].end();++it )
          {
            cout<<(*it).first->toString()<<" "<<(*it).second.second<<" "<<(*it).second.first<<endl;
            nodes[i].push_back(new simpleNode((*it).first,(*it).second.second,(*it).second.first));
        }
		avg += nodes[i].size();
    }
	avg = avg*1.0/num;
    make_connections(nodes,finish);


	cout<<"connections done"<<endl;
    count_probability();
	cout<<"probability done"<<endl;
//	ant* best=iteration();
  //  cout<<"done!!"<<endl;
//	while (best->get_probability()<0.8)
//	{
	//  cout<<"is"<<is_converged()<<endl;
	  //best->rule_is_finished();
	/*  best = iteration();
	}*/
	//best->rule_is_finished();
	//cout<<"is"<<is_converged()<<endl<<"rule:"<<best->to_string_rule()<<endl<<"prob:"<<best->get_probability()<<endl;
	//extract(best);
	//cout<<is_covered_enough();
	//recount_heuristic();
	
	//best=iteration();
 //   cout<<"done!!"<<endl;
/*	while (best->get_probability()<0.8)
	{
		//cout<<best->get_probability()<<endl;
	//  cout<<"is"<<is_converged()<<endl;
	  best->rule_is_finished();
	  best = iteration();
	}*/
	//best->rule_is_finished();
	//cout<<"is"<<is_converged()<<endl<<"rule:"<<best->to_string_rule()<<endl<<"prob:"<<best->get_probability()<<endl;
	//extract(best);
	//cout<<is_covered_enough();

 log_file.close();
}



void ant_miner::recount_heuristic()
	{
		start->recount_heuristic(-1,x,y);
	}

void ant_miner::evaporation()
{
    start->evaporate(this->eva_coef);
}

ant* ant_miner::iteration()
{
	fstream log_file;
		log_file.open("log.txt",ios::out);
		

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
    best_quality = method_agents[best_num]->get_quality(x,y);
    for (int i=1; i<ants_number;++i)
    {
        if (method_agents[i]->get_quality(x,y)>best_quality)
        {
            best_num = i;
            best_quality = method_agents[i]->get_quality(x,y);
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
	cout<<"considered best ant with"<<endl;
	cout<<"rule: "<<best_ant->to_string_rule()<<endl;
	cout<<"with probability: "<<best_ant->get_probability()<<" and quality: "<<best_ant->get_quality()<<endl;
	cout<<endl;
 // //ph_max = (best_ant->get_quality(x,y))/(1.0-eva_coef);
    //ph_min = (ph_max*(1-pow(best_ant->get_probability(),1.0/layer_num)))/((avg-1)*pow(best_ant->get_probability(),1.0/layer_num));
 
	count_probability();
	//cout<<"b_q"<<best_ant->get_quality(x,y)<<endl;
	//cout<<best_ant->to_string_rule()<<endl;
//	cout<<"avg"<<avg<<endl<<"prob"<<best_ant->get_probability()<<endl;
   // cout<<"ph_min="<<ph_min<<" ph_max="<<ph_max<<endl;
	log_file.close();
	return best_ant;
}

