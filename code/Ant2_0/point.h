#ifndef POINT_H
#define POINT_H
struct point
{
    int a;
    double b;
    int c;
    point (int aa, double bb, int cc):a(aa),b(bb),c(cc)
    {

    }

    void print ()
    {
        cout<<a<<" "<<b<<" "<<c<<endl;
    }
};

#endif // POINT_H
