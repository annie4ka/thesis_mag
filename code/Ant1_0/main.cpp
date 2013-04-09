#include <QtCore/QCoreApplication>
#include <QtDebug>
#include <iostream>
#include "test_empty.h"
#include "test_equal.h"
#include "test_more.h"
#include "test_between.h"
#include <edge.h>
#include <graph_node.h>
#include <agent.h>

#include <packet_parser.cpp>
# include <method.h>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
   cout<<"Hello!"<<endl;

//    parse ("K:\\Disk F\\class_TCP.log","K:\\time1.dat");

method ant;
ant.create_enveronment("K:\\time2.dat");
cout<<"World!"<<endl;


    return a.exec();
}
