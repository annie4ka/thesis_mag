#ifndef ANT_TYPES_H
#define ANT_TYPES_H
#define null 0
#include "checker.h"
#include "ant_exception.h"
#include "test_between.h"
#include "test_equal.h"
#include "test_empty.h"
#include <list>
#include <vector>
#include <algorithm>
typedef vector < list< pair< checker*, pair<int,int> > > > base_type;
typedef list < pair< checker*, pair<int,int> > > pre_node_type;
typedef pair<checker*,pair<int,int> > in_pair;
#endif // ANT_TYPES_H
