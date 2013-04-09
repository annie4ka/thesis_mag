#ifndef AGENT_H
#define AGENT_H
#include <edge.h>
#include <graph_node.h>

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


class agent{

    N_1 * node_path_1;
    N_2 * node_path_2;
    N_3 * node_path_3;
    N_4 * node_path_4;
    N_5 * node_path_5;
    N_6 * node_path_6;
    N_7 * node_path_7;
    N_8 * node_path_8;
    edge <N_1> * edge_path_1;
    edge <N_2> * edge_path_2;
    edge <N_3> * edge_path_3;
    edge <N_4> * edge_path_4;
    edge <N_5> * edge_path_5;
    edge <N_6> * edge_path_6;
    edge <N_7> * edge_path_7;
    edge <N_8> * edge_path_8;

    N_S * current;
    bool reach_end;
    double level;
public:
    agent(){

        srand(time(NULL));
        reach_end = false;
        level = 0.8;

    }

    void reinforcement (double delta)
    {
        edge_path_1->set_pheromone(edge_path_1->get_pheromone()+delta);
        edge_path_2->set_pheromone(edge_path_2->get_pheromone()+delta);
        edge_path_3->set_pheromone(edge_path_3->get_pheromone()+delta);
        edge_path_4->set_pheromone(edge_path_4->get_pheromone()+delta);
        edge_path_5->set_pheromone(edge_path_5->get_pheromone()+delta);
        edge_path_6->set_pheromone(edge_path_6->get_pheromone()+delta);
        edge_path_7->set_pheromone(edge_path_7->get_pheromone()+delta);
        edge_path_8->set_pheromone(edge_path_8->get_pheromone()+delta);
    }

    void set_current(N_S * s)
    {
        current = s;

    }

    bool is_reach_end()
    {
        return reach_end;
    }

   void move1 ()
    {
        bool done = false;
        int it=0;
        while ((!done)&&(it<=100))
        {
            edge_path_1 = current->random_edge();
            if (edge_path_1->get_probability()>level)
                done = true;
            else
                ++it;
        }
        node_path_1 = edge_path_1->get_next();
     }



   void move2 ()
    {
        bool done = false;
        int it=0;
        while ((!done)&&(it<=100))
        {
            edge_path_2 = node_path_1->random_edge();
            if (edge_path_2->get_probability()>level)
                done = true;
            else
                ++it;
        }
        node_path_2 = edge_path_2->get_next();
     }

   void move3 ()
    {
        bool done = false;
        int it=0;
        while ((!done)&&(it<=100))
        {
            edge_path_3 = node_path_2->edge_i(0);
            if (edge_path_3->get_probability()>level)
                done = true;
            else
                ++it;
        }
        node_path_3 = edge_path_3->get_next();
     }



   void move4 ()
    {
        bool done = false;
        int it=0;
        while ((!done)&&(it<=100))
        {
            edge_path_4 = node_path_3->random_edge();
            if (edge_path_4->get_probability()>level)
                done = true;
            else
                ++it;
        }
        node_path_4 = edge_path_4->get_next();
     }



   void move5 ()
    {
        bool done = false;
        int it=0;
        while ((!done)&&(it<=100))
        {
            edge_path_5 = node_path_4->random_edge();
            if (edge_path_5->get_probability()>level)
                done = true;
            else
                ++it;
        }
        node_path_5 = edge_path_5->get_next();
     }


   void move6 ()
    {
        bool done = false;
        int it=0;
        while ((!done)&&(it<=100))
        {
            edge_path_6 = node_path_5->random_edge();
            if (edge_path_6->get_probability()>level)
                done = true;
            else
                ++it;
        }
        node_path_6 = edge_path_6->get_next();
     }

   void move7 ()
    {
        bool done = false;
        int it=0;
        while ((!done)&&(it<=100))
        {
            edge_path_7 = node_path_6->random_edge();
            if (edge_path_7->get_probability()>level)
                done = true;
            else
                ++it;
        }
        node_path_7 = edge_path_7->get_next();
     }

   void move8 ()
    {
        bool done = false;
        int it=0;
        while ((!done)&&(it<=100))
        {
            edge_path_8 = node_path_7->random_edge();
            if (edge_path_8->get_probability()>level)
                done = true;
            else
                ++it;
        }
        node_path_8 = edge_path_8->get_next();
     }



    void work()
    {
        move1();
        move2();
        move3();
        move4();
        move5();
        move6();
        move7();
        move8();
    }

    string toString()
    {
        string tmp = "";
        tmp += node_path_1->toString();
        tmp += node_path_2->toString();
        tmp += node_path_3->toString();
        tmp += node_path_4->toString();
        tmp += node_path_5->toString();
        tmp += node_path_6->toString();
        tmp += node_path_7->toString();
        tmp += node_path_8->toString();
        return tmp;
    }

    double count_quality(vector <double> v_time, vector <int> v_length,
                       vector <bool> v_syn, vector <bool> v_fin, vector <bool> v_ack,
                       vector <bool> v_psh, vector <bool> v_urg, vector <bool> v_rst,
                       vector <char> v_mark)
    {
        int correct =0;
        int covered =0;
        bool correctness;
        for (int i = 0; i<v_mark.size();++i)
        {
            correctness = (/*(node_path_1->tester(v_time[i]))
                           &&(node_path_2->tester(v_length[i]))&&*/
                           (node_path_3->tester(v_syn[i]))/*&&(node_path_4->tester(v_fin[i]))&&
                           (node_path_5->tester(v_ack[i]))
                           &&(node_path_6->tester(v_psh[i]))&&
                           (node_path_7->tester(v_urg[i]))&&(node_path_8->tester(v_rst[i]))*/);

          //  cout<<"1"<<node_path_1->tester(v_time[i])<<" 2"<<node_path_2->tester(v_length[i])<<" 3"<<node_path_3->tester(v_syn[i])<<endl;
            if(correctness)
            {
                ++covered;
                if (v_mark[i]=='!')
                    ++correct;
            }

        }
        if (covered==0)
            return 0;
        return (((1.0*correctness)/(covered*1.0))+((covered*1.0)/(v_mark.size()*1.0)));
     }



    double get_solution_prob()
    {
        double p=1;
        p *= edge_path_1->get_probability();
        p *= edge_path_2->get_probability();
        p *= edge_path_3->get_probability();
        p *= edge_path_4->get_probability();
        p *= edge_path_5->get_probability();
        p *= edge_path_6->get_probability();
        p *= edge_path_7->get_probability();
        p *= edge_path_8->get_probability();

        return p;
    }


};

#endif // AGENT_H
