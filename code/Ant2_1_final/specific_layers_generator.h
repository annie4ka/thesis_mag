#include <list>
#include <vector>
#include <algorithm>
#include <string>
#include "ant_types.h"

using namespace std;

bool func1 (void* p1, void* p2);
bool func2 (void* p1, void* p2);

list <checker*> layer_char(vector <void*> w,string name);
list <checker*> layer1_3(vector <void*> w,string name);
list <checker*> layer_str(vector <void*> w,string name);
list <checker*> layer_cont(vector <void*> w, string name, double precision);
list <checker*> layer2(vector <void*> w, string name, double precision);
list <checker*> layer12(vector <void*> w, string name, int precision);
list <checker*> layer_equal_points(vector <void*> w, string name, int num);
list <checker*> layer_equal_double(vector <void*> w, string name, int num);
list <checker*> layer_dense_points(vector <void*> w, string name, int epsilon);

