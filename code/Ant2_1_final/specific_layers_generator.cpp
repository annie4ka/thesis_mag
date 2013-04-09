#include "specific_layers_generator.h"

bool func1 (void* p1, void* p2)
{
    int *a1 = (int*)p1;    int *a2 = (int*)p2;
    return (*a1)<(*a2);
}

bool func3 (void* p1, void* p2)
{
    string *a1 = (string*)p1;    string *a2 = (string*)p2;
    return (*a1)<(*a2);
}

bool func2 (void* p1, void* p2)
{
    double *b1 = (double*)p1;
    double *b2 = (double*)p2;
    return (*b1)<(*b2);
}

list <checker*> layer_char(vector <void*> w,string name)
{
    sort(w.begin(),w.end(),func1);

    int prev;
    list <checker*> node_func;
    vector <void*>::iterator it = w.begin();
    if(w.begin()!=w.end())
    {
        prev =(*((char*)(*it)));
        node_func.push_back(new test_equal<char>(prev,name));
        ++it;
        while(it!=w.end())
        {
            if ((*((char*)(*it)))!=prev)
            {

                prev = (*((char*)(*it)));
                node_func.push_back(new test_equal<char>(prev,name));
            }
            ++it;
        }
    }

    node_func.push_back(new test_empty(name));
    return node_func;
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




list <checker*> layer_str(vector <void*> w,string name)
{
    sort(w.begin(),w.end(),func3);

    string prev;
    list <checker*> node_func;
    vector <void*>::iterator it = w.begin();
    if(w.begin()!=w.end())
    {
        prev =(*((string*)(*it)));
        node_func.push_back(new test_equal<string>(prev,name));
        ++it;
        while(it!=w.end())
        {
            if ((*((string*)(*it)))!=prev)
            {

                prev = (*((string*)(*it)));
                node_func.push_back(new test_equal<string>(prev,name));
            }
            ++it;
        }
    }

    node_func.push_back(new test_empty(name));
    return node_func;
}

list <checker*> layer_cont(vector <void*> w, string name, double precision)
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
	vector <void*>::iterator it = w.begin();
	double prev;
    if(w.begin()!=w.end())
    {
        prev =(*((double*)(*it)));
        node_func.push_back(new test_equal<double>(prev,name));
        ++it;
        while(it!=w.end())
        {
            if ((*((double*)(*it)))!=prev)
            {

                prev = (*((double*)(*it)));
                node_func.push_back(new test_equal<double>(prev,name));
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
list <checker*> layer12(vector <void*> w, string name, int precision)
{
    sort(w.begin(),w.end(),func1);
	list<checker*> node_func;
    if (w.begin()!=w.end())
    {
        vector<void*>::iterator it_b,it_e;
        double b_min,b_max;
        it_b=w.begin();
        b_min=(*((int*)(*it_b)));
        it_e=w.end();
        --it_e;
        b_max=(*((int*)(*it_e)));
		if (b_max<b_min)
		{
			int r = b_max;
			b_max=b_min;
			b_min=r;
		}
		while ((b_min+precision)<b_max)
        {
            node_func.push_back(new test_between<int>(b_min,b_min+precision,name));
            b_min=b_min+precision;
        }
        node_func.push_back(new test_between<double>(b_min,b_max,name));
    }
	
    
    node_func.push_back(new test_empty(name));
    return node_func;

}

list <checker*> layer_equal_points(vector <void*> w, string name, int quan)
{
    sort(w.begin(),w.end(),func1);
	//int quan = w.size()/num;
	list<checker*> node_func;
    if (w.begin()!=w.end())
    {
       	vector <pair<int,int>> count;
        

		vector<void*>::iterator it;
		it = w.begin();
		
		if (it!=w.end())
		{
			count.push_back(pair<int,int>((*(int*)(*it)),1));
			++it;
		}
		while (it!=w.end())
		{
			if ( (*(int*)(*it))!= count.back().first)
			{
				count.push_back(pair<int,int>((*(int*)(*it)),1));
			}
			else 
			{
				count.back().second = count.back().second + 1; 
			}
			++it;
		}
			
		int last; int first;
		int count_int;
		while (!count.empty())
		{
		count_int = 0;
		last = count.back().first;
		first = last;
		count_int = count.back().second;
		count.pop_back();
		while ((!count.empty())&&((count_int+count.back().second)<quan))
		{
			first = count.back().first;
			count_int += count.back().second;
			count.pop_back();
		}
		if(!count.empty())
		{
			if((count_int+count.back().second-quan)<(quan-count_int))
			{
				first = count.back().first;
				count_int += count.back().second;
				count.pop_back();
			}
			
		}
		if (first>last)
		{
			int r = first;
			first = last;
			last = r;
		}
		node_func.push_back(new test_between<int>(first,last,name));


		}
		
    }
	
    
    node_func.push_back(new test_empty(name));
    return node_func;

}

list <checker*> layer_equal_double(vector <void*> w, string name, int num)
{
     sort(w.begin(),w.end(),func2);
	int quan = w.size()/num;
	list<checker*> node_func;
    if (w.begin()!=w.end())
    {
       	vector <pair<double,int>> count;
        

		vector<void*>::iterator it;
		it = w.begin();
		
		if (it!=w.end())
		{
			count.push_back(pair<double,int>((*(double*)(*it)),1));
			++it;
		}
		while (it!=w.end())
		{
			if ( (*(double*)(*it))!= count.back().first)
			{
				count.push_back(pair<double,int>((*(double*)(*it)),1));
			}
			else 
			{
				count.back().second = count.back().second + 1; 
			}
			++it;
		}
			
		double last; double first;
		int count_int;
		while (!count.empty())
		{
		count_int = 0;
		last = count.back().first;
		first = last;
		count_int = count.back().second;
		count.pop_back();
		while ((!count.empty())&&((count_int+count.back().second)<quan))
		{
			first = count.back().first;
			count_int += count.back().second;
			count.pop_back();
		}
		if(!count.empty())
		{
			if((count_int+count.back().second-quan)<(quan-count_int))
			{
				first = count.back().first;
				count_int += count.back().second;
				count.pop_back();
			}
			
		}
		if (first>last)
		{
			double r = first;
			first = last;
			last = r;
		}
		node_func.push_back(new test_between<double>(first,last,name));


		}
		
    }
	
    
    node_func.push_back(new test_empty(name));
    return node_func;
}

list <checker*> layer_dense_points(vector <void*> w, string name, int epsilon)
{
	sort(w.begin(),w.end(),func1);
	list<checker*> node_func;
	vector <void*>::iterator it;
	it = w.begin();
	if (it!=w.end())
	{
		int prev, first,last;
		first = (*(int*)(*it));
		last = first;
		++it;
		while (it!=w.end())
		{
			if (((last -(*(int*) (*it)))>epsilon)||(((*(int*) (*it))-last)>epsilon))
			{
				if (first<last)
					node_func.push_back(new test_between<int>(first,last,name));
				else 
					node_func.push_back(new test_between<int>(last,first,name));
				++it;
				if (it!=w.end())
					{
						first = (*(int*)(*it));
				last = first;
				++it;
				}
			
			}
			else 
			{
				last = (*(int*)(*it));
				++it;
			}

		}

		if (last<first)
		node_func.push_back(new test_between<int>(last,first,name));
		else
			node_func.push_back(new test_between<int>(first,last,name));

				
				
	}
	node_func.push_back(new test_empty(name));
				return node_func;
}