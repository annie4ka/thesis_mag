#include "process_different.h"
#include <map>
using namespace std;

int process_simple(int argc, char *argv[])
{
    

    fstream x1, x2,logger,outer;
    int num = 3;
    x1.open("X1.dat",ios::in);
    x2.open("X2.dat",ios::in);
	
	outer.open("rules.txt",ios::out);
    vector <vector<void*> > x(num);
    vector <vector <void*> > y(num);
    vector <checker*> a_vector,c_vector;
    vector <checker*> b_equal, b_inter;

    int *a,*c;
    double *b;
    while (!x1.eof())
    {
        a = new int;
        c = new int;
        b = new double;
        x1>>(*a)>>(*b)>>(*c);
        x[0].push_back((void*)a);
        x[1].push_back((void*)b);
        x[2].push_back((void*)c);

    }
    while (!x2.eof())
    {
        a = new int;
        c = new int;
        b = new double;
        x2>>(*a)>>(*b)>>(*c);
        y[0].push_back((void*)a);
        y[1].push_back((void*)b);
        y[2].push_back((void*)c);


    }
    vector<list<checker*> > layers(3);
    layers[0]=layer1_3(x[0],"a");
    layers[2]=layer1_3(x[2],"c");
    layers[1]=layer2(x[1],"b",eps);

    method_coefs K;
    K.alpha = 2;
    K.beta = 1;
    K.evap_c = 0.85;
    K.ph_min = 1;
    K.ph_max = 3;
    K.ants_number = 100;
    K.covarage = 0.95;
    ant_miner my_ant(3,x,y,layers,K);
    ant* best;

	int iteration_number = 0;
	while (!my_ant.is_covered_enough())
	{
		logger.open("log.txt",ios::out);
		cout<<"iteration number: "<<iteration_number<<endl;
		logger.close();
		best = my_ant.iteration();
		++iteration_number;
		while (best->get_probability()<0.6)
		{
			best = my_ant.iteration();
			++iteration_number;
		}

		outer<<"after "<<iteration_number<<" iterations extracted "<<endl;
		outer<<"rule: "<<best->to_string_rule()<<endl;
		logger.open("log.txt",ios::out);
		cout<<"after "<<iteration_number<<" iterations extracted "<<endl;
		cout<<"rule: "<<best->to_string_rule()<<endl;
		logger.close();
		cout<<"extracted!";
		my_ant.extract(best);
		outer<<"with coverage: "<<my_ant.get_covered()*100<<"%"<<endl;
		logger.open("log.txt",ios::out);
		cout<<"with coverage: "<<my_ant.get_covered()*100<<"%"<<endl;
		logger.close();
		outer<<endl;
		iteration_number = 0;
	}
	cout<<"Done!";
	cin.get();
    return 0;
}

int port_80_rule(int argc, char** argv)
{
	fstream learn_22,learn_80;
	fstream outer;
	learn_22.open("learn_port_22.log",ios::in);
	learn_80.open("learn_port_80.log",ios::in);
	outer.open("rule_port.txt",ios::out);
	int num = 5;
	string mark;
	vector <vector<void*> > x(num);
    vector <vector <void*> > y(num);
    vector <checker*> time_vector,from_p_vector,to_p_vector;
    vector <checker*> from_d_vector,to_d_vector;

    int *f_pack,*t_pack,*f_dat,*t_dat;
    double *time;
	int count_22 = 0, count_80 = 0;
	fstream fx, fy;
	fx.open("x_.log",ios::out);
	fy.open("y_.log",ios::out);
	while ((!learn_80.eof())&&(count_80<1000))
    {
        f_pack = new int;
		t_pack = new int;
		f_dat = new int;
		t_dat = new int;
		time = new double;
        
        learn_80>>(*time)>>(*f_pack)>>(*t_pack)>>(*f_dat)>>(*t_dat)>>mark;
		fx<<(*time)<<" "<<(*f_pack)<<" "<<(*t_pack)<<" "<<(*f_dat)<<" "<<(*t_dat)<<endl;
		if (!learn_80.eof())
			{
				
        x[0].push_back((void*)time);
        x[1].push_back((void*)f_pack);
        x[2].push_back((void*)t_pack);
		x[3].push_back((void*)f_dat);
        x[4].push_back((void*)t_dat);
		++count_80;
		}
    }
	cout<<endl<<"1";
    
      while ((!learn_22.eof())&&(count_22<1000))
    {
        f_pack = new int;
		t_pack = new int;
		f_dat = new int;
		t_dat = new int;
		time = new double;
        
        learn_22>>(*time)>>(*f_pack)>>(*t_pack)>>(*f_dat)>>(*t_dat)>>mark;
		fy<<(*time)<<" "<<(*f_pack)<<" "<<(*t_pack)<<" "<<(*f_dat)<<" "<<(*t_dat)<<endl;
		if (!learn_22.eof())
		{
        y[0].push_back((void*)time);
        y[1].push_back((void*)f_pack);
        y[2].push_back((void*)t_pack);
		y[3].push_back((void*)f_dat);
        y[4].push_back((void*)t_dat);
		++count_22;
		}

    }
	  cout<<"layers"<<endl;
    vector<list<checker*> > layers(5);
    layers[1]=layer_equal_points(x[1],"f_pack",50);
    layers[2]=layer_equal_points(x[2],"t_pack",50);
	layers[3]=layer_equal_points(x[3],"f_dat",50);
    layers[4]=layer_equal_points(x[4],"t_dat",50);
    layers[0]=layer_equal_double(x[0],"time",50);
	cout<<"q"<<endl;
    method_coefs K;
    K.alpha = 2;
    K.beta = 1;
    K.evap_c = 0.85;
    K.ph_min = 1;
    K.ph_max = 3;
    K.ants_number = 100;
    K.covarage = 0.95;
    ant_miner my_ant(num,x,y,layers,K);
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
	return 0;
}

#include <set>

int KDD_anomaly ()
{
	fstream KDD_names, KDD_out,KDD_tcp,KDD_udp,KDD_icmp,icmp_graph_smurf,icmp_graph_normal; 
	fstream fout,fout_tcp,fout_udp,fout_icmp;
	string variable, type, name;
	vector<string> names,types;
	int layer_num = 9;
	KDD_names.open("variables.txt",ios::in);
	KDD_out.open("corrected_out",ios::in);
	KDD_tcp.open("corrected_tcp",ios::in);
	KDD_udp.open("corrected_udp",ios::in);
	KDD_icmp.open("corrected_icmp",ios::in);
	icmp_graph_smurf.open("icmp_graph_smurf.log",ios::out);
	icmp_graph_normal.open("icmp_graph_normal.log",ios::out);
	vector <vector<void*> > x(layer_num);
    vector <vector <void*> > y(layer_num);

	//fout.open("disp",ios::out);
	//fout_tcp.open("disp_tcp",ios::out);
	//fout_udp.open("disp_udp",ios::out);
	//fout_icmp.open("disp_icmp",ios::out);
	

	if (!KDD_names.is_open())
		return 25;
	while (!KDD_names.eof())
	{
		KDD_names>>variable;
		if (!KDD_names.eof()){
		name = variable.substr(0,variable.find_first_of(":"));
		KDD_names>>variable;
		type = variable.substr(0,variable.find_first_of("."));
		//cout<<name<<endl;
		names.push_back(name);
	  //  cout<<type<<endl;
		types.push_back(type);

		}
}

	int n = 41;
	int count [42],count_tcp[42],count_udp[42],count_icmp[42];
	for (int i=0;i<42;++i)
	{
		count [i] = 0;
		count_tcp[i]=0;
		count_udp[i]=0;
		count_icmp[i]=0;
	}
	map <int,int> icmp_allow;
	icmp_allow[2]=0;
	icmp_allow[4]=1;
	icmp_allow[22]=2;
	icmp_allow[23]=3;
	icmp_allow[31]=4;
	icmp_allow[32]=5;
	icmp_allow[33]=6;
	icmp_allow[34]=7;
	icmp_allow[35]=8;
	//icmp_allow[39]=9;
	vector <map<string ,int> > symb (41),symb_tcp(41),symb_udp(41),symb_icmp(41);
	vector <map<double,int> > cont(41),cont_tcp(41),cont_udp(41),cont_icmp(41);
/*	while(!KDD_out.eof()) 
	{
		
		for(int i=0;i<42;++i)
		{
			if (i==41)
			{
				KDD_out>>variable;
				count [i] = -1;
			}
			else
			if(types[i]=="continuous")
			{
				double b;
				KDD_out>>(b);
				//y[i].push_back((void*)b);
				if ((b)!=0)
					++count[i];
				if (cont[i].find(b)!=cont[i].end())
					{
						cont[i][b]++;
					}
					else
					{
						cont[i][b]  = 1;	
					}
			}
			else
				if (types[i]=="symbolic")
				{
					string b;
					KDD_out>>(b);
					count [i] = -1;
					if (symb[i].find(b)!=symb[i].end())
					{
						symb[i][b]++;
					}
					else
					{
						symb[i][b]  = 1;	
					}
					//y[i].push_back((void*)b);
				}
				else 
					cout<<"error!!!"<<endl;
		}
		//++count_normal;
	
	}



	

	while(!KDD_tcp.eof()) 
	{
		
		for(int i=0;i<42;++i)
		{
			if (i==41)
			{
				KDD_tcp>>variable;
				count_tcp [i] = -1;
			}
			else
			if(types[i]=="continuous")
			{
				double b;
				KDD_tcp>>(b);
				//y[i].push_back((void*)b);
				if ((b)!=0)
					++count_tcp[i];
				if (cont_tcp[i].find(b)!=cont_tcp[i].end())
					{
						cont_tcp[i][b]++;
					}
					else
					{
						cont_tcp[i][b]  = 1;	
					}
			}
			else
				if (types[i]=="symbolic")
				{
					string b;
					KDD_tcp>>(b);
					count_tcp[i] = -1;
					if (symb_tcp[i].find(b)!=symb_tcp[i].end())
					{
						symb_tcp[i][b]++;
					}
					else
					{
						symb_tcp[i][b]  = 1;	
					}
					//y[i].push_back((void*)b);
				}
				else 
					cout<<"error!!!"<<endl;
		}
		//++count_normal;
	
	}


	while(!KDD_udp.eof()) 
	{
		
		for(int i=0;i<42;++i)
		{
			if (i==41)
			{
				KDD_udp>>variable;
				count_udp [i] = -1;
			}
			else
			if(types[i]=="continuous")
			{
				double b;
				KDD_udp>>(b);
				//y[i].push_back((void*)b);
				if ((b)!=0)
					++count_udp[i];
				if (cont_udp[i].find(b)!=cont_udp[i].end())
					{
						cont_udp[i][b]++;
					}
					else
					{
						cont_udp[i][b]  = 1;	
					}
			}
			else
				if (types[i]=="symbolic")
				{
					string b;
					KDD_udp>>(b);
					count_udp [i] = -1;
					if (symb_udp[i].find(b)!=symb_udp[i].end())
					{
						symb_udp[i][b]++;
					}
					else
					{
						symb_udp[i][b]  = 1;	
					}
					//y[i].push_back((void*)b);
				}
				else 
					cout<<"error!!!"<<endl;
		}
		//++count_normal;
	
	}

	*/
vector <double*> b_d(41);
vector <string*> b_s (41);
int count_normal_correct =0;
int count_abnormal_correct = 0;
int count_abnormal_incorrect = 0;
int count_normal_incorrect=0;
int rule_2_normal_correct =0;
int rule_2_abnormal_correct = 0;
int rule_2_abnormal_incorrect = 0;
int rule_2_normal_incorrect=0;
int count_covered = 0;
	while(!KDD_icmp.eof()) 
	{
		
		for(int i=0;i<42;++i)
		{
			if (i==41)
			{
				KDD_icmp>>variable;
				if (variable=="normal")
					icmp_graph_normal<<(*(b_d[23]))<<" "<<(*(b_d[35]))<<endl;
				else
					icmp_graph_smurf<<(*(b_d[23]))<<" "<<(*(b_d[35]))<<endl;
			}
			else
			if(types[i]=="continuous")
			{
				double b;
				if (icmp_allow.find(i)==icmp_allow.end())
					KDD_icmp>>(b);
				else 
				{
					 b_d[i] = new double;
					KDD_icmp>>(*(b_d[i]));
				}
				
			}
			else
				if (types[i]=="symbolic")
				{
					string b;
					if (icmp_allow.find(i)==icmp_allow.end())
					KDD_icmp>>(b);
				else 
				{
					 b_s[i] = new string;
					KDD_icmp>>(*(b_s[i]));
				}
				}
				else 
					cout<<"error!!!"<<endl;
		}
		//++count_normal;
		for (int i = 0;i<41;++i)
		{
			if (icmp_allow.find(i)!=icmp_allow.end())
			{
				if (variable=="normal")
				{
					
					if ((*(b_d[35]))==1)
						++count_normal_incorrect;
					else 
						{++count_normal_correct;
					if (((*(b_d[23]))>=97)&&((*(b_d[23]))<=511))
						++rule_2_normal_incorrect;
					else 
						++rule_2_normal_correct;
					if (types[i]=="continuous")
						x[icmp_allow[i]].push_back((void*)b_d[i]);
					else
						x[icmp_allow[i]].push_back((void*)b_s[i]);
					}
				}
				else
				{
					
					if ((*(b_d[35]))==1)
						++count_abnormal_correct;
					else 
						{if (((*(b_d[23]))>=506)&&((*(b_d[23]))<=511))
						++rule_2_abnormal_correct;
					else 
						++rule_2_abnormal_incorrect;
							++count_abnormal_incorrect;
					if (types[i]=="continuous")
						y[icmp_allow[i]].push_back((void*)b_d[i]);
					else
						y[icmp_allow[i]].push_back((void*)b_s[i]);
					}
				}
			}
		}
	
	}





	cout<<"readed"<<endl;
	icmp_graph_normal.close();
	icmp_graph_smurf.close();
	/*
	 vector<list<checker*> > layers(layer_num);
	 char* nae = new char[3];
	 for (int i=0; i<41;++i)
	 {
		 if (icmp_allow.find(i)!=icmp_allow.end())
		 {
			 itoa(i,nae,10);
		     if(types[i]=="continuous")
				 layers[icmp_allow[i]]=layer_equal_double(y[icmp_allow[i]],nae,5);
			 else 
				 layers[icmp_allow[i]]=layer_str(y[icmp_allow[i]],nae);
		 }
	 }
	 cout<<"layers done"<<endl;


	 method_coefs K;
    K.alpha = 2;
    K.beta = 1;
    K.evap_c = 0.85;
    K.ph_min = 1;
    K.ph_max = 3;
    K.ants_number = 100;
    K.covarage = 1.00;
    ant_miner my_ant(layer_num,y,x,layers,K);
	cout<<"constructor finished"<<endl;
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


		fstream outer;
		outer.open("KDD_icmp_rule",ios::out);
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
	*/
	cout<<"correct_normal="<<count_normal_correct<<endl;
	cout<<"incorrect_normal="<<count_normal_incorrect<<endl;
	cout<<"correct_abnormal="<<count_abnormal_correct<<endl;
	cout<<"incorrect_abnormal="<<count_abnormal_incorrect<<endl;
	cout<<"rule2_correct_normal="<<rule_2_normal_correct<<endl;
	cout<<"rule_2_incorrect_normal="<<rule_2_normal_incorrect<<endl;
	cout<<"rule_2_correct_abnormal="<<rule_2_abnormal_correct<<endl;
	cout<<"rule_2_incorrect_abnormal="<<rule_2_abnormal_incorrect<<endl;
	cout<<"Done!";


/*	cout<<"not null count"<<endl;
for (int i=0;i<42;++i)
{
	cout<<count[i]<<" ";
}
cout<<endl;
fout<<endl;
fout<<"symb:"<<endl;
fout_tcp<<endl;
fout_tcp<<"symb:"<<endl;
fout_udp<<endl;
fout_udp<<"symb:"<<endl;
fout_icmp<<endl;
fout_icmp<<"symb:"<<endl;
for (int i=0; i<41; ++i)
{
	if (!symb[i].empty())
	{
		fout<<i<<":#"<<endl;
		for (map<string,int>::iterator it = symb[i].begin(); it != symb[i].end(); ++it)
		{
			fout<<(*it).first<<" : "<<(*it).second<<endl;
		}
	}
}

for (int i=0; i<41; ++i)
{
	if (!symb_tcp[i].empty())
	{
		fout_tcp<<i<<":#"<<endl;
		for (map<string,int>::iterator it = symb_tcp[i].begin(); it != symb_tcp[i].end(); ++it)
		{
			fout_tcp<<(*it).first<<" : "<<(*it).second<<endl;
		}
	}
}
for (int i=0; i<41; ++i)
{
	if (!symb_udp[i].empty())
	{
		fout_udp<<i<<":#"<<endl;
		for (map<string,int>::iterator it = symb_udp[i].begin(); it != symb_udp[i].end(); ++it)
		{
			fout_udp<<(*it).first<<" : "<<(*it).second<<endl;
		}
	}
}
for (int i=0; i<41; ++i)
{
	if (!symb_icmp[i].empty())
	{
		fout_icmp<<i<<":#"<<endl;
		for (map<string,int>::iterator it = symb_icmp[i].begin(); it != symb_icmp[i].end(); ++it)
		{
			fout_icmp<<(*it).first<<" : "<<(*it).second<<endl;
		}
	}
}

fout<<endl;
fout_icmp<<endl;
fout_tcp<<endl;
fout_udp<<endl;
fout<<"cont:"<<endl;

fout_tcp<<"cont:"<<endl;fout_udp<<"cont:"<<endl;fout_icmp<<"cont:"<<endl;
for (int i=0; i<41; ++i)
{
	if (!cont[i].empty())
	{
		fout<<i<<":#"<<endl;
		for (map<double,int>::iterator it = cont[i].begin(); it != cont[i].end(); ++it)
		{
			fout<<(*it).first<<" : "<<(*it).second<<endl;
		}
	}
}

for (int i=0; i<41; ++i)
{
	if (!cont_tcp[i].empty())
	{
		fout_tcp<<i<<":#"<<endl;
		for (map<double,int>::iterator it = cont_tcp[i].begin(); it != cont_tcp[i].end(); ++it)
		{
			fout_tcp<<(*it).first<<" : "<<(*it).second<<endl;
		}
	}
}

for (int i=0; i<41; ++i)
{
	if (!cont_icmp[i].empty())
	{
		fout_icmp<<i<<":#"<<endl;
		for (map<double,int>::iterator it = cont_icmp[i].begin(); it != cont_icmp[i].end(); ++it)
		{
			fout_icmp<<(*it).first<<" : "<<(*it).second<<endl;
		}
	}
}
for (int i=0; i<41; ++i)
{
	if (!cont_udp[i].empty())
	{
		fout_udp<<i<<":#"<<endl;
		for (map<double,int>::iterator it = cont_udp[i].begin(); it != cont_udp[i].end(); ++it)
		{
			fout_udp<<(*it).first<<" : "<<(*it).second<<endl;
		}
	}
}
fout.close();
fout_tcp.close();
fout_udp.close();
fout_tcp.close();*/










cin.get();
}

int process_KDD(int argc, char** argv)
{
	fstream KDD, KDD_names, KDD_out,KDD_normal, KDD_attack,outer, icmp_graph_smurf, icmp_graph_normal;
	outer.open("rules1.txt",ios::out);
	LOGGER logg("log1.txt");
	string variable, type, name;
	vector<string> names,types;
	
	KDD_normal.open("KDD_normal",ios::in);
	KDD_attack.open("KDD_neupteune",ios::in);
	KDD_names.open("variables.txt",ios::in);
	//KDD.open("corrected_out", ios::in);
	//KDD_out.open("corrected_out",ios::out);
	if (!KDD_names.is_open())
		return 25;
	while (!KDD_names.eof())
	{
		KDD_names>>variable;
		if (!KDD_names.eof()){
		name = variable.substr(0,variable.find_first_of(":"));
		KDD_names>>variable;
		type = variable.substr(0,variable.find_first_of("."));
		//cout<<name<<endl;
		names.push_back(name);
		//cout<<type<<endl;
		types.push_back(type);

		}
	}
	int num = 41;
	vector <vector<void*> > x(num);
    vector <vector <void*> > y(num);
	int count_normal=0, count_attack=0;
	while ((!KDD_normal.eof())&&(count_normal<NORMAL_NUM))
	{
		for(int i=0;i<42;++i)
		{
			if (i==41)
				KDD_normal>>variable;
			else
			if(types[i]=="continuous")
			{
				double *b = new double;
				KDD_normal>>(*b);
				y[i].push_back((void*)b);
			}
			else
				if (types[i]=="symbolic")
				{
					string *b = new string;
					KDD_normal>>(*b);
					y[i].push_back((void*)b);
				}
				else 
					cout<<"error!!!"<<endl;
		}
		++count_normal;
	}
	cout<<"1";
	while ((!KDD_attack.eof())&&(count_attack<ATTACK_NUM))
	{
		for(int i=0;i<42;++i)
		{
			if (i==41)
				KDD_attack>>variable;
			else
			if(types[i]=="continuous")
			{
				double *b = new double;
				KDD_attack>>(*b);
				
				x[i].push_back((void*)b);
			}
			else
				if (types[i]=="symbolic")
				{
					string *b = new string;
					KDD_attack>>(*b);
					
					x[i].push_back((void*)b);
				}
				else 
					cout<<"error!!!"<<endl;
		}
		++count_attack;
		
	}

	cout<<"2";
	while ((!KDD_normal.eof())&&(count_attack<NORMAL_NUM))
	{
		for(int i=0;i<42;++i)
		{
			if (i==41)
				KDD_normal>>variable;
			else
				if(types[i]=="continuous")
			{
				double *b = new double;
				KDD_normal>>(*b);
				x[i].push_back((void*)b);
			}
			else
				if (types[i]=="symbolic")
				{
					string *b = new string;
					KDD_normal>>(*b);
					x[i].push_back((void*)b);
				}
				else 
					cout<<"error!!!"<<endl;
		}
		++count_attack;
	}

	cout<<"3";
	
    vector<list<checker*> > layers(num);
	for (int i=0;i<num;++i)
	{
		
		if (types[i]=="symbolic")
			layers[i]=layer_str(x[i],names[i]);
		else
			if(types[i]=="continuous")
				layers[i] = layer2(x[i],names[i],eps);
	}
	cout<<endl;
	cout<<"4";
	method_coefs K;
    K.alpha = 2;
    K.beta = 1;
    K.evap_c = 0.85;
    K.ph_min = 1;
    K.ph_max = 3;
    K.ants_number = 100;
    K.covarage = 0.95;
    ant_miner my_ant(num,x,y,layers,K);
	cout<<"5";
	cout<<endl;
    ant* best;
	fstream logger;
	int iteration_number = 0;
	while (!my_ant.is_covered_enough())
	{
		
		logg.out("iteration number: ");
		logg.out(iteration_number);
		logg.end();
		logger.close();
		best = my_ant.iteration();
		++iteration_number;
		while (best->get_probability()<0.6)
		{
			best = my_ant.iteration();
			++iteration_number;
		}

		outer<<"after "<<iteration_number<<" iterations extracted "<<endl;
		outer<<"rule: "<<best->to_string_rule()<<endl;
		logg.out("after ");
		logg.out(iteration_number);
		logg.out(" iterations extracted ");
		logg.end();
		logg.out("rule: ");
		logg.out(best->to_string_rule());
		logg.end();
		cout<<"extracted!";
		double cov = my_ant.extract(best);
		outer<<"with coverage: "<<my_ant.get_covered()*100<<"%"<<endl;
		outer<<"with specific coverage "<<cov*100<<"%"<<endl;
		logg.out("with coverage: ");
		logg.out(my_ant.get_covered()*100);
	    logg.out("%");
		logg.end();
		outer<<endl;
		iteration_number = 0;
	}
	cout<<"Done!";



	/*string variables [42];
	cout<<names.size();
	int normal_count=0, attack_count=0;
	while (!KDD.eof())
	{
		for (int i=0;i<42;++i)
		{
			KDD>>variables[i];
		}
		if (variables[41]=="normal")
			for(int i=0; i<42;++i)
			{
				KDD_normal<<variables[i];
				if(i==41)
					KDD_normal<<endl;
				else
					KDD_normal<<" ";
				++normal_count;
			}
		else
			if (variables[41]=="neptune")
			for(int i=0; i<42;++i)
			{
				KDD_attack<<variables[i];
				if(i==41)
					KDD_attack<<endl;
				else
					KDD_attack<<" ";
				++attack_count;
			}
			
	}
//	KDD_attack_normal.open("KDD_attack_normal.log",ios::out);
	cout<<"n="<<normal_count<<" a="<<attack_count<<endl;
	*/
	KDD.close();
	KDD_normal.close();
	KDD_attack.close();

	cin.get();
	return 0;
}

/*
int main(int argc, char *argv[])
{
    

    fstream x1, logger,outer;
    int num = 9;
    x1.open("tic_tac_toe_data.txt",ios::in);
    
	
	outer.open("rules.txt",ios::out);
    vector <vector<void*> > x(num);
    vector <vector <void*> > y(num);
    vector <checker*> a_vector[9];
    //vector <checker*> b_equal, b_inter;

    char *a [9];
	string mark;
	int count  = 0;
	char* zpt =new char;
    while (!x1.eof())
    {
		for (int i=0;i<9;++i)
			{
				a[i] = new char;
				//x1>>(*(a[i]));
				x1.get((a[i]),1,',');
				x1.get(zpt,1);
				cout<<(*(a[i]))<<endl;

		}
		x1>>mark;
		cout<<mark;
		if (mark=="positive")
			{
				for (int i=0;i<9;++i)
					x[i].push_back((void*)a[i]);
		}
		else
		{
			for (int i=0;i<9;++i)
				y[i].push_back((void*)a[i]);
		}
        ++count;
		if (count%500==0)
			cout<<count<<" points readed"<<endl;

    }
    
    vector<list<checker*> > layers(9);
	for (int i=0;i<9;++i)
		{
			layers[i]=layer_char(x[i],"a_"+i);
	}

    method_coefs K;
    K.alpha = 2;
    K.beta = 1;
    K.evap_c = 0.85;
    K.ph_min = 1;
    K.ph_max = 3;
    K.ants_number = 100;
    K.covarage = 0.95;
    ant_miner my_ant(3,x,y,layers,K);
    ant* best;

	int iteration_number = 0;
	while (!my_ant.is_covered_enough())
	{
		logger.open("log.txt",ios::out);
		cout<<"iteration number: "<<iteration_number<<endl;
		logger.close();
		best = my_ant.iteration();
		++iteration_number;
		while (best->get_probability()<0.6)
		{
			best = my_ant.iteration();
			++iteration_number;
		}

		outer<<"after "<<iteration_number<<" iterations extracted "<<endl;
		outer<<"rule: "<<best->to_string_rule()<<endl;
		logger.open("log.txt",ios::out);
		cout<<"after "<<iteration_number<<" iterations extracted "<<endl;
		cout<<"rule: "<<best->to_string_rule()<<endl;
		logger.close();
		cout<<"extracted!";
		my_ant.extract(best);
		outer<<"with coverage: "<<my_ant.get_covered()*100<<"%"<<endl;
		logger.open("log.txt",ios::out);
		cout<<"with coverage: "<<my_ant.get_covered()*100<<"%"<<endl;
		logger.close();
		outer<<endl;
		iteration_number = 0;
	}
	cout<<"Done!";
	cin.get();
    return 0;
}
*/