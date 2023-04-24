#include "Point.h"

Point::Point(int x, int y) : d_x(x), d_y(y){

   // this->d_x = d_x;
    //this->d_y = d_y;
}

int Point::getX() {
    return d_x;
}

int Point::getY() {
    return d_y;
}

void Point::setX(int x) {
    d_x = x;
}

void Point::setY(int y) {
    d_y = y;
}

void Point::move(int x, int y) {
    d_x = x;
    d_y = y;
}

void Point::shift(int x, int y) {
    d_x += x;
    d_y += y;
}

void Point::read() {
    int nx, ny;
    cout << "Entrer les coordonnees d_x et d_y du point : ";
    cin >> nx >> ny;
    setX(nx);
    setY(ny);
}

void Point::print() {
    cout << toString() << endl;
}

string Point::toString() {
    return "(" + to_string(d_x) + ", " + to_string(d_y) + ")";
}

bool Point::operator==(Point &p) {
    return (p.getX() == this->d_x && p.getY() == this->d_y);
}


