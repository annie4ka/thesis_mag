#ifndef FORWARD_EDGE_H
#define FORWARD_EDGE_H
#include "super_edge.h"
class forward_edge: public super_edge
{
public:
    forward_edge(edge* data, simpleNode* node):super_edge(data,node)
    {
    }

    void remove(simpleNode* nod)
    {
        next->remove_back(nod);
        delete (*this);
    }
};


#endif // FORWARD_EDGE_H
