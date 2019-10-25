#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Point{
    private:
        double x;
        double y;

    public:
        Point();
        ~Point();
        void set_x(double xi);
        void set_y(double yi);
        double get_x();
        double get_y();
};

class Curve{
    private:
        string id;
        int m;
        vector<Point> points;
    public:
        Curve();
        ~Curve();
        void set_id(string curve_id);
        void set_m(int mi);
        void push_point(Point p);
        string get_id();
        int get_m();
        vector<Point> get_points();
};
