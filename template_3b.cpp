#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

template <class T>
class Point {
public:
    T x;
    T y;

    Point(){}
    Point(T _x, T _y): x(_x), y(_y) {}
    Point(const Point& p): x(p.x), y(p.y) {}

    // static std::ostream& operator<<(std::ostream& os, Point& p)
    // {
    //     return os << "(" << p.x << " " << p.y << ")";
    // }
};


template <class T>
T cross(Point<T> a, Point<T> b, Point<T> a1, Point<T> b1)
{
    T x1 = b.x - a.x;
    T y1 = b.y - a.y;
    T x2 = b1.x - a1.x;
    T y2 = b1.y - a1.y;
    return x1*y2 - x2*y1;
}

enum DIR
{
    LEFT,
    RIGHT,
    ONLINE
};

template <class T>
class Intersect_Result
{
public:
    int cross_num;
    Point<T> a,b;
    DIR da, db;
};

// a,b is a line
// c,d is segment
template <class T>
Intersect_Result<T>
intersection(Point<T> a, Point<T> b, Point<T> c, Point<T> d)
{
    Intersect_Result<T> res;
    T side_c = cross(a, b, a, c);
    T side_d = cross(a, b, a, d);
    res.da = side_c < 0 ? RIGHT : (side_c == 0 ? ONLINE : LEFT);
    res.db = side_d < 0 ? RIGHT : (side_d == 0 ? ONLINE : LEFT);
    if (side_c * side_d > 0)
    {
        res.cross_num = 0;
    }
    else if (side_c == 0 && side_d == 0)
    {
        res.cross_num = 2;
        res.a = c;
        res.b = d;
    }
    else if (side_c == 0 || side_d == 0)
    {
        res.cross_num = 1;
        res.a = side_c == 0? c : d;
    }
    else
    {
        Point<T> dir;
        dir.x = b.x - a.x;
        dir.y = b.y - a.y;
        double orth_x = -dir.y;
        double orth_y =  dir.x;
        double c_len = ((c.x-a.x)*orth_x) + ((c.y-a.y)*orth_y);
        double d_len = ((d.x-a.x)*orth_x) + ((d.y-a.y)*orth_y);
        double t = (double)c_len / (double)(c_len - d_len);

        res.cross_num = 1;
        res.a.x = c.x + t*(d.x - c.x);
        res.a.y = c.y + t*(d.y - c.y);
    }
    return res;
}

template <class T>
Point<T> point_nth(const std::vector<Point<T>>& V, int i)
{
    if (i >= V.size())
        i -= V.size();
    return V[i];
}

std::vector<Point<int>>
determine_polygons_intersection(const std::vector<Point<int>>& V, const std::vector<Point<int>>& W) {
    /*
    Given 2 convex polygons, it is required to find their intersection.
    Two polygons intersect nondegenerately: the intersection of two edges occurs
    at a single point and forms a convex polygon. The intersection may also be absent,
    in this case output 0.
    V and W are given as lists of vertices in counterclockwise order
    Return a list of vertices of their intersection.
    */
    std::vector<Point<int>> result;
    // convert into double
    std::vector<Point<double>> result_f;
    for (Point<int> p: W)
    {
        result_f.push_back(Point<double>(p.x, p.y));
    }
    for (int i = 0; i < V.size(); i++)
    {
        Point<int> ia = point_nth(V, i);
        Point<int> ib = point_nth(V, i+1);
        Point<double> a(ia.x, ia.y);
        Point<double> b(ib.x, ib.y);
        // printf("----------------------\nclip line (%f,%f)_(%f,%f)\n", a.x, a.y, b.x, b.y);
        std::vector<Point<double>> tmp_polygon;
        for (int j = 0; j < result_f.size(); j++)
        {
            // cross by line ab
            Point<double> c = point_nth(result_f, j);
            Point<double> d = point_nth(result_f, j + 1);
            // printf("test segment (%f,%f)_(%f,%f)\n", c.x, c.y, d.x, d.y);
            // 4 case to deal
            Intersect_Result<double> res = intersection<double>(a, b, c, d);
            if (res.cross_num == 1 && res.da != ONLINE && res.db != ONLINE)
            {
                if (res.da == LEFT)
                {
                    tmp_polygon.push_back(res.a);
                    // printf("--> cross:(%f,%f)\n", res.a.x, res.a.y);
                }
                else
                {
                    tmp_polygon.push_back(res.a);
                    tmp_polygon.push_back(d);
                    // printf("--> cross:(%f,%f)\n", res.a.x, res.a.y);
                    // printf("--> left: (%f,%f)\n", d.x, d.y);
                }
            }
            else if (res.db == ONLINE || res.db == LEFT)
            {
                tmp_polygon.push_back(d);
                // printf("--> line: (%f,%f)\n", d.x, d.y);
            }
        }
        result_f = tmp_polygon;
        // // printf ("POLYGON((");
        // for (int k = 0; k <= result.size(); k++)
        // {
        //     Point p = point_nth(result, k);
        //     // printf("%d %d", p.x, p.y);
        //     if (k != result.size())
        //         // printf(",");
        // }
        // // printf("))\n");
    }
    for (Point<double> p: result_f)
    {
        result.push_back(Point<int>(round(p.x), round(p.y)));
    }
    return result;
}

int test_intersection()
{
    Intersect_Result<int> res;
    Point<int> a(6,-7);
    Point<int> b(3,14);
    Point<int> c(-1,7);
    Point<int> d(11,-7);
    res = intersection(a, b, c, d);
    std::cout << res.cross_num << "\n";
    // if (res.cross_num == 1)
    //     std::cout << res.a << "\n";
    // else if (res.cross_num == 2)
    //     std::cout << res.a << ", " << res.b << "\n";
    return 0;
}

int main() {
    // return test_intersection();
    int n;
    std::cin >> n;
    std::vector<Point<int>> V(n);
    std::vector<int> V_coord(2 * n);
    for (int &item : V_coord) {
        std::cin >> item;
    }
    for (int i = 0; i < n; ++i) {
        V[i].x = V_coord[2 * i];
        V[i].y = V_coord[2 * i + 1];
    }
    int m;
    std::cin >> m;
    std::vector<Point<int>> W(m);
    std::vector<int> W_coord(2 * m);
    for (int &item : W_coord) {
        std::cin >> item;
    }
    for (int i = 0; i < m; ++i) {
        W[i].x = W_coord[2 * i];
        W[i].y = W_coord[2 * i + 1];
    }
    std::vector<Point<int>> res;
    res = determine_polygons_intersection(V, W);
    int res_size = res.size();
    std::cout << res_size << std::endl;
    for (int i = 0; i < res_size; ++i) {
        std::cout << res[i].x << ' ' << res[i].y << ' ' << " ";
    }
}
