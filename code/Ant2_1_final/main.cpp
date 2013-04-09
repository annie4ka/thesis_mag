

#include "process_different.h"


void process_ping_find_anomaly()
{
	fstream normal_lin, normal_win, abnormal;
	normal_lin.open("ping_lin.log",ios::in);
	normal_win.open("ping_n.log",ios::in);
	abnormal.open("ping_a.log",ios::in);
	fstream outer;
	outer.open("rule_tunnel_anomaly.txt",ios::out);

	int num = 5;
	int _num =20;

	vector <vector<void*> > normal(num);
    vector <vector <void*> > normal_with_attack(num);
	int *x;
	int normal_lin_count = 0;
	int normal_win_count = 0;
	int attack_count = 0;
	while ((!normal_lin.eof())&&(normal_lin_count<200))
	{
		for (int i=0; i<20; ++i)
		{
			x = new int;
			normal_lin>>(*x);
			if(i<num)
			{

			normal[i].push_back((void*)x);
			if(normal_lin_count<100)
			{
				normal_with_attack[i].push_back((void*)x);
			}
			}
		}
		++normal_lin_count;
	}

	while ((!normal_win.eof())&&(normal_win_count<200))
	{
		for (int i=0; i<20; ++i)
		{
			x = new int;
			normal_win>>(*x);
			if(i<num)
			{
			normal[i].push_back((void*)x);
			if (normal_win_count<100)
			{
				normal_with_attack[i].push_back((void*)x);
			}
			}
		}
		++normal_win_count;
	}
	while ((!abnormal.eof())&&(attack_count<200))
	{
		for (int i=0; i<20; ++i)
		{
			x =new int;
			abnormal>>(*x);
			if(i<num)
			{
			normal_with_attack[i].push_back((void*)x);
			}
		}
		++attack_count;
	}

	cout<<"normal_lin_count="<<normal_lin_count<<"    normal_win_count"<<normal_win_count<<"  attack_count="<<attack_count<<endl;
	cout<<"layers"<<endl;
    vector<list<checker*> > layers(num);
	char* arg_name = new char [11];
	strcpy(arg_name,"byte_");
	strcpy(arg_name+6,"_.txt");
	for (int i=0; i<num;++i)
	{
		itoa(i,arg_name+5,10);
		layers[i]=layer_equal_points(normal_with_attack[i],arg_name,50);
	}
	cout<<"q"<<endl;
    method_coefs K;
    K.alpha = 2;
    K.beta = 1;
    K.evap_c = 0.85;
    K.ph_min = 1;
    K.ph_max = 3;
    K.ants_number = 100;
    K.covarage = 1;
    ant_miner my_ant(num,normal_with_attack,normal,layers,K);
    ant* best;

	int iteration_number = 0;
	int equls = 0;
	ant* prev; 
	while (!my_ant.is_covered_enough())
	{
		
		cout<<"iteration number: "<<iteration_number<<endl;
		
		best = my_ant.iteration();
		++iteration_number;
		while (equls<5)
		{
			prev = best;
			best = my_ant.iteration();
			if (ant::equal(best,prev))
				++equls;
			++iteration_number;
		}

		outer<<"after "<<iteration_number<<" iterations extracted "<<endl;
		outer<<"rule: "<<best->to_string_rule()<<endl;
		
		cout<<"after "<<iteration_number<<" iterations extracted "<<endl;
		cout<<"rule: "<<best->to_string_rule()<<endl;
		
		cout<<"extracted!";
		double cover = my_ant.extract(best);
		outer<<"with coverage: "<<my_ant.get_covered()*100<<"%"<<endl;
		outer<<"with specific coverage: "<<cover*100<<"%"<<endl;
		
		cout<<"with coverage: "<<my_ant.get_covered()*100<<"%"<<endl;
		
		outer<<endl;
		iteration_number = 0;
		equls = 0;
	}
	cout<<"Done!";
	
	cin.get();
}


int main (int argc, char** argv)
{
	//process_ping_find_anomaly();
	//KDD_anomaly();
	fstream in1, in2,out1,out2;
	in1.open("D:\\learn_port_22.log",ios::in);
	in2.open("D:\\learn_port_80.log",ios::in);
	out1.open("D:\\out_22.log",ios::out);
	out2.open("D:\\out_80.log", ios::out);

	double time;
	int f_pack, t_pack, f_dat, t_dat, mark;
	while (!in1.eof()){
	in1>>(time)>>(f_pack)>>(t_pack)>>(f_dat)>>(t_dat)>>mark;
	out1<<f_pack<<" "<<t_pack<<" "<<f_dat<<endl;
	}
	while(!in2.eof()){
	in2>>(time)>>(f_pack)>>(t_pack)>>(f_dat)>>(t_dat)>>mark;
	out2<<f_pack<<" "<<t_pack<<" "<<f_dat<<endl;
	}
	in1.close();
	in2.close();
	out1.close();
	out2.close();
	return 0;
}