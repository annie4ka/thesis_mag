#ifndef BASE_GRAPH_NODE_H
#define BASE_GRAPH_NODE_H


enum node_type {begin,ordinary,final};

class base_graph_node{
    node_type type_id;
    int owner_count;
public:
    base_graph_node (node_type type = ordinary ):type_id(type),owner_count(0)
    {

    }

    void plus_owner_count()
    {
        ++owner_count;
    }

    void minus_owner_count()
    {
        --owner_count;
    }

    int get_owner_count()
    {
        return owner_count;
    }

    base_graph_node (base_graph_node& b2)
    {
        type_id = b2.get_type();
        owner_count = 0;
    }

    node_type get_type()
    {
        return type_id;
    }

    void Link()
    {
        ++owner_count;
    }

    void UnLink()
    {
        if (owner_count==0)
            delete this;
        --owner_count;
        if (owner_count==0)
            delete this;
    }


      ~base_graph_node()
      {
      }

};


#endif // BASE_GRAPH_NODE_H
