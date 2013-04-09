#ifndef BACK_EDGE_H
#define BACK_EDGE_H
#include "super_edge.h"

class back_edge: public super_edge
{
    back_edge(edge* data, simpleNode* node): super_edge(data,node)
    {
    }

    void remove(simpleNode* nod)
    {
        next->remove_forward(nod);
        delete(*this);
    }

};

#endif // BACK_EDGE_H
