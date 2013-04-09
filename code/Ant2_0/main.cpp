#include <QtCore/QCoreApplication>
#include "ant_types.h"
#include "ant_miner.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include "super_edge.h"
# define eps 0.1



bool func1 (void* p1, void* p2)
{
    int *a1 = (int*)p1;    int *a2 = (int*)p2;
    return (*a1)<(*a2);
}

bool func2 (void* p1, void* p2)
{
    double *b1 = (double*)p1;
    double *b2 = (double*)p2;
    return (*b1)<(*b2);
}



list <checker*> layer1_3(vector <void*> w,string name)
{
    sort(w.begin(),w.end(),func1);

    int prev;
    list <checker*> node_func;
    vector <void*>::iterator it = w.begin();
    if(w.begin()!=w.end())
    {
        prev =(*((int*)(*it)));
        node_func.push_back(new test_equal<int>(prev,name));
        ++it;
        while(it!=w.end())
        {
            if ((*((int*)(*it)))!=prev)
            {

                prev = (*((int*)(*it)));
                node_func.push_back(new test_equal<int>(prev,name));
            }
            ++it;
        }
    }

    node_func.push_back(new test_empty(name));
    return node_func;
}



list <checker*> layer2(vector <void*> w, string name, double precision)
{
    sort(w.begin(),w.end(),func2);
    list<checker*> node_func;
    if (w.begin()!=w.end())
    {
        vector<void*>::iterator it_b,it_e;
        double b_min,b_max;
        it_b=w.begin();
        b_min=(*((double*)(*it_b)));
        it_e=w.end();
        --it_e;
        b_max=(*((double*)(*it_e)));
        while ((b_min+precision)<b_max)
        {
            node_func.push_back(new test_between<double>(b_min,b_min+precision,name));
            b_min=b_min+precision;
        }
        node_func.push_back(new test_between<double>(b_min,b_max,name));
    }
    node_func.push_back(new test_empty(name));
    return node_func;

}


#include <set>
#include "edge.h"
#include "move_gen.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    fstream x1, x2;
    int num = 3;
    x1.open("E:\\Swarm_intelligence\\Ant\\Ant_2_0\\X1.dat",ios::in);
    x2.open("E:\\Swarm_intelligence\\Ant\\Ant_2_0\\X2.dat",ios::in);
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
    K.covarage = 0.8;
    ant_miner my_ant(3,x,y,layers,K);
ant* best;
//my_ant.evaporation();
    {
        cout<<"!!";
     //   best = my_ant.iteration();
    }

    return app.exec();
}
