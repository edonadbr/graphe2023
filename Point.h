#ifndef POINT_H
#define POINT_H

#include<iostream>
using namespace std;

class Point {
private:
    int d_x, d_y;

public:
    Point(int x, int y);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    void move(int x, int y);
    void shift(int x, int y);
    void read();
    void print();
    string toString();
    bool operator==(Point &p);
};

#endif /* POINT_H */
