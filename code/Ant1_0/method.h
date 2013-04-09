#ifndef METHOD_H
#define METHOD_H

#include <graph_node.h>
#include <test_equal.h>
#include <test_between.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <agent.h>


using namespace std;

typedef graph_node <bool,int> N_E;
typedef graph_node <bool,N_E> N_8;
typedef graph_node <bool,N_8> N_7;
typedef graph_node <bool,N_7> N_6;
typedef graph_node <bool,N_6> N_5;
typedef graph_node <bool,N_5> N_4;
typedef graph_node <bool,N_4> N_3;
typedef graph_node <int,N_3> N_2;
typedef graph_node <double,N_2> N_1;
typedef graph_node <int,N_1> N_S;

class method {
    double alpha;
    double beta;
    double po;
    int ant_number;
    int iteration_number;
    double coverage_degree;
    base_graph_node * env;
    double t_min;
    double t_max;
public:
    method ()
    {
        alpha = 2;
        beta = 1;
        po = 0.85;
        ant_number =5000;
        iteration_number = 1000;
        coverage_degree=0.95;
        t_max = 15;
        t_min = 0.15;
    }

    void t_max_new (double d_best)
    {

        t_max=1/(1-po)*d_best;
    }

    void create_enveronment(string file_name)
    {
        vector <N_1*> layer1;
        vector <N_2*> layer2;
        vector <N_3*> layer3;
        vector <N_4*> layer4;
        vector <N_5*> layer5;
        vector <N_6*> layer6;
        vector <N_7*> layer7;
        vector <N_8*> layer8;
        N_S *start;
        N_E *end;

        fstream read;
        read.open(file_name.c_str(),ios::in);
        if (!read.is_open())
        {
            cout<<"no";
            return;
        }


        double time;
        int length;
        bool syn,fin,ack,psh,urg,rst;
        char mark;

        vector <double> v_time;
        vector <int> v_length;
        vector <bool> v_syn;
        vector <bool> v_fin;
        vector <bool> v_ack;
        vector <bool> v_psh;
        vector <bool> v_urg;
        vector <bool> v_rst;
        vector <char> v_mark;

        int count = 0 ;
        int count_r = 0;


        set <double> all_time;
        set <int> all_length;

        while (! read.eof())
        {


                read>>time>> length >> syn >> fin >> ack >> psh >> urg >> rst>>mark;
           if (!read.eof())
           {

                all_time.insert(time);
                all_length.insert(length);
                v_time.push_back(time);
                v_length.push_back (length);
                v_syn.push_back(syn);
                v_fin.push_back(fin);
                v_ack.push_back(ack);
                v_psh.push_back(psh);
                v_urg.push_back(urg);
                v_rst.push_back(rst);
                v_mark.push_back (mark);
                ++count;
                if (mark=='!')
                    ++count_r;
            }
        }
        cout<<"Data have been loaded...\n";

        set<double>::iterator jt = all_time.begin();
        cout<<(*jt);
        set <double>::iterator it = all_time.end();
        --it;

        double diap = (*it) -(*jt);

        double delta = diap/100;

        for (double i = (*jt);i<=(*it);i+=delta)
        {

            layer1.push_back(N_1::make(new test_between<double> (i,i+delta, "time"),0));


        }
        layer1.push_back(N_1::make(new test_empty<double> ("time"),0));

        for (set <int>::iterator it = all_length.begin();it!=all_length.end();++it)
        {
            layer2.push_back(N_2::make(new test_equal<int> ((*it), "length"),0));
        }


        layer2.push_back(N_2::make(new test_empty<int> ("length"),0));
        layer3.push_back(N_3::make(new test_equal<bool> (true, "syn"),0));
        layer4.push_back(N_4::make(new test_equal<bool> (true, "fin"),0));
        layer5.push_back(N_5::make(new test_equal <bool> (true, "ack"),0));
        layer6.push_back(N_6::make(new test_equal <bool>(true, "psh"),0));
        layer7.push_back(N_7::make(new test_equal <bool>(true, "urg"),0));
        layer8.push_back(N_8::make(new test_equal <bool>(true, "rst"),0));
        layer3.push_back(N_3::make(new test_equal<bool> (false, "syn"),0));
        layer4.push_back(N_4::make(new test_equal<bool> (false, "fin"),0));
        layer5.push_back(N_5::make(new test_equal <bool> (false, "ack"),0));
        layer6.push_back(N_6::make(new test_equal <bool>(false, "psh"),0));
        layer7.push_back(N_7::make(new test_equal <bool>(false, "urg"),0));
        layer8.push_back(N_8::make(new test_equal <bool>(false, "rst"),0));
        layer3.push_back(N_3::make(new test_empty<bool> ("syn"),0));
        layer4.push_back(N_4::make(new test_equal<bool> (true, "fin"),0));
        layer5.push_back(N_5::make(new test_equal <bool> (true, "ack"),0));
        layer6.push_back(N_6::make(new test_equal <bool>(true, "psh"),0));
        layer7.push_back(N_7::make(new test_equal <bool>(true, "urg"),0));
        layer8.push_back(N_8::make(new test_equal <bool>(true, "rst"),0));
        start = N_S::make(new test_empty<int>("start"),1,begin);
        end = N_E::make(new test_empty<bool>("start"),1,final);


        cout<<"l1 "<<layer1.size()<<endl;
        cout<<"l2 "<<layer2.size()<<endl;
        cout<<"l3 "<<layer3.size()<<endl;
        cout<<"l4 "<<layer4.size()<<endl;
        cout<<"l5 "<<layer5.size()<<endl;
        cout<<"l6 "<<layer6.size()<<endl;
        cout<<"l7 "<<layer7.size()<<endl;
        cout<<"l8 "<<layer8.size()<<endl;

        cout<<"Graph nodes had been created...\n";


        heuristic_recount<double,N_1>(layer1,v_time,v_mark);
        heuristic_recount<int,N_2>(layer2,v_length,v_mark);
        heuristic_recount<bool,N_3>(layer3,v_syn,v_mark);
        heuristic_recount<bool,N_4>(layer4,v_fin,v_mark);
        heuristic_recount<bool,N_5>(layer5,v_ack,v_mark);
        heuristic_recount<bool,N_6>(layer6,v_psh,v_mark);
        heuristic_recount<bool,N_7>(layer7,v_urg,v_mark);
        heuristic_recount<bool,N_8>(layer8,v_rst,v_mark);

        cout<<"heuristic had been recounted...\n";

       connect<N_S,N_1> (start,layer1);
       cout<<"1";
       connect<N_1,N_2> (layer1,layer2);
       cout<<"2";
       connect<N_2,N_3> (layer2,layer3);
       connect<N_3,N_4> (layer3,layer4);
       connect<N_4,N_5> (layer4,layer5);
       connect<N_5,N_6> (layer5,layer6);
       connect<N_6,N_7> (layer6,layer7);
       connect<N_7,N_8> (layer7,layer8);
       connect<N_8,N_E> (layer8,end);

       cout<<"Layers had been reconnected...\n";
       double q=0;
       double w;bool done =false;

       while (!done)
       {

           recount_probability_i <N_S> (start);
       recount_probability <N_1> (layer1);
       recount_probability <N_2> (layer2);
       recount_probability <N_3> (layer3);
       recount_probability <N_4> (layer4);
       recount_probability <N_5> (layer5);
       recount_probability <N_6> (layer6);
       recount_probability <N_7> (layer7);
       recount_probability <N_8> (layer8);
       recount_probability_i <N_E> (end);

       cout<<"Transition probability had been recounted...\n";


    agent * agents = new agent[ant_number];
       double max_quality = 0;
       int best_agent = -1;
       for (int i=0; i<ant_number;++i)
       {

           agents [i].set_current(start);
           agents [i].work();

           q = agents[i].count_quality(v_time,v_length,v_syn,v_fin,v_ack,v_psh,v_urg,v_rst,v_mark);
           if (q>=max_quality)
           {
               best_agent = i;
               max_quality = q;
           }

           w=agents[best_agent].get_solution_prob();
           done = (w==(int)pow(t_max,8));


       }

       cout<<"q="<<max_quality<<endl;
       cout<<"Rule:"<<agents[best_agent].toString()<<endl;

       ph_evaporation<N_S,N_1>(start);
       ph_evaporation<N_1,N_2>(layer1);
        ph_evaporation<N_2,N_3>(layer2);
         ph_evaporation<N_3,N_4>(layer3);
          ph_evaporation<N_4,N_5>(layer4);
           ph_evaporation<N_5,N_6>(layer5);
            ph_evaporation<N_6,N_7>(layer6);
             ph_evaporation<N_7,N_8>(layer7);
              ph_evaporation<N_8,N_E>(layer8);

              agents[best_agent].reinforcement(q);

              t_max_new(q);

}



    }


    template <typename T1, typename T2>
    void heuristic_recount(vector<T2*> layer, vector<T1> data, vector <char> mark)
    {
        int* g_count;
        int* r_count;
        g_count = new int [layer.size()];
        r_count = new int [layer.size()];
        for (int i = 0; i<layer.size();++i)
        {
            g_count[i]=0;
            r_count[i]=0;
        }
        for (int i = 0;i<mark.size();++i)
        {
            for (int j = 0; j<layer.size();++j)
            {

                if(layer[j]->tester(data[i]))
                {
                    ++g_count[j];
                    if(mark[i]=='!')
                    {
                        ++r_count[j];
                    }
                }
            }

        }

        for (int j = 0; j<layer.size();++j)
        {
            layer[j]->set_heuristic(r_count[j]*1.0/(g_count[j]*1.0));
        }



    }

    template <typename T1,typename T2>
    void connect(vector<T1*>layer1, vector <T2*> layer2)
    {
        for (typename vector <T1*>::iterator it = layer1.begin();it!=layer1.end();++it) //layer7->layer8
        {
             for (typename vector <T2*>::iterator yt = layer2.begin();yt!=layer2.end();++yt)
             {
                 connect <T1,T2> ((*it),(*yt));
             }
        }

    }


    template <typename T1,typename T2>
    void connect(T1 * node1, vector <T2*> layer2)
    {

             for (typename vector <T2*>::iterator yt = layer2.begin();yt!=layer2.end();++yt)
             {
                 connect <T1,T2> (node1,(*yt));
             }

    }

    template <typename T1,typename T2>
    void connect(vector <T1*> layer1, T2* node2)
    {
             for (typename vector <T1*>::iterator yt = layer1.begin();yt!=layer1.end();++yt)
             {
                 connect <T1,T2> ((*yt), node2);
             }

    }


    template <typename T1,typename T2>
    void connect(T1* node1, T2* node2)
    {
        //node2->Link();
        node1->add_the_edge(new edge<T2>(1.0,t_min,node2));
    }

    template <typename T>
    void recount_probability(   vector <T*> layer)
    {
        typename  vector <T*>::iterator it;
        for ( it= layer.begin();it!=layer.end();++it)
        {
            recount_probability_i<T>(*it);
        }
    }

    template <typename T>
    void recount_probability_i(   T* node)
    {

        int n;
            double factor = probability_factor <T>(node);
            double p;

            n = node->get_degree();
            for (int i = 0; i<n;++i)
            {
                p = 1;
                p *= pow(node->get_i_edge_ph(i),alpha);
                p *= pow(node->get_i_edge_next_h(i),alpha);
                if (factor!=0)
                    node->set_i_edge_prob(i,p/factor);
                else
                    node->set_i_edge_prob(i,0);
            }

    }

    template <typename T,typename T1>
    void ph_evaporation(vector <T*> layer)
    {
        int n;
        for (typename vector< T*>::iterator it = layer.begin();it!=layer.end();++it)
        {
            n = (*it)->get_degree();
            for (int i = 0; i<n;++i)
            {
                (*it)-> set_i_edge_ph(i,(*it)->get_i_edge_ph(i)*po);
            }

        }


    }

    template <typename T,typename T1>
    void ph_evaporation(T* start)
    {
            int n = start->get_degree();
            for (int i = 0; i<n;++i)
            {
                start->set_i_edge_ph(i,start->get_i_edge_ph(i)*po);
            }
    }

    template <typename T>
    double probability_factor( T * node)
    {

        double factor = 0;
        double factor_s ;
        int n = node->get_degree();
        for (int i = 0; i<n; ++i)
        {
            factor_s = 1;
            factor_s *= pow(node->get_i_edge_ph(i),alpha);
            factor_s *= pow(node->get_i_edge_next_h(i),beta);
            factor += factor_s;

        }

        return factor;

    }
};

#endif // METHOD_H
