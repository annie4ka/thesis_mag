#include "simple_node.h"
#include "super_edge.h"
double super_edge::get_prob_mul()
{
    double a = data->getPheromone();
    double b = next->getHeuristic();
    return a*b;

}
void super_edge::count_probability()
{
    next->count_probability();
}
