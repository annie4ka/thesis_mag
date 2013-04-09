#include "ant_types.h"
#include "ant_miner.h"
#include "logger.h"
#include <iostream>
#include <fstream>
#include <string>
# define eps 0.1
#define NORMAL_NUM 500
#define ATTACK_NUM 450
using namespace std;


#include "specific_layers_generator.h"

int KDD_anomaly();
int port_80_rule();
int process_KDD();
int process_simple();