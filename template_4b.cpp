#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

class Point {
public:
    Point(){}
    Point(int64_t a, int64_t b): x(a), y(b){}
    int64_t x;
    int64_t y;
};

bool operator== (const Point &a, const Point &b)
{
    return a.x == b.x && a.y == b.y;
}

int cross(Point a, Point b)
{
    return a.x * b.y - b.x * a.y;
}

bool segment_cross(Point a, Point b, Point c, Point d, bool debug = false)
{
    if (std::min(a.x, b.x) > std::max(c.x, d.x) ||
        std::max(a.x, b.x) < std::min(c.x, d.x) ||
        std::min(a.y, b.y) > std::max(c.y, d.y) ||
        std::max(a.y, b.y) < std::min(c.y, d.y))
        return false;

    Point ab(b.x - a.x, b.y - a.y);
    Point ac(c.x - a.x, c.y - a.y);
    Point ad(d.x - a.x, d.y - a.y);

    Point cd(d.x - c.x, d.y - c.y);
    Point ca(a.x - c.x, a.y - c.y);
    Point cb(b.x - c.x, b.y - c.y);
    int64_t c1 = cross(ab, ac);
    int64_t c2 = cross(ab, ad);
    int64_t c3 = cross(cd, ca);
    int64_t c4 = cross(cd, cb);
    if (debug)
    {
        printf("cross: %lld, %lld, %lld, %lld\n", c1, c2, c3, c4);
    }
    long long c12 = (long long)c1 * (long long)c2;
    long long c34 = (long long)c3 * (long long)c4;
    if (c12 <= 0 && c34 <= 0)
        return true;

    return false; // disjoint
}

bool inner_point(Point a, Point b, Point c, Point d)
{
    Point bc(c.x - b.x, c.y - b.y);
    Point ba(a.x - b.x, a.y - b.y);
    Point bd(d.x - b.x, d.y - b.y);
    int64_t c1 = cross(ba, bc);
    int64_t c2 = cross(ba, bd);
    if (c1 <= 0)
    {
        if (c2 >= 0)
        {
            return false;
        }
        else
        {
            double a1 = (ba.x*bc.x + ba.y*bc.y) / sqrt(bc.x*bc.x + bc.y*bc.y);
            double a2 = (ba.x*bd.x + ba.y*bd.y) / sqrt(bd.x*bd.x + bd.y*bd.y);
            if (a1 > a2)
                return false;
            else
                return true;
        }
    }
    else
    {
        if (c2 <= 0)
        {
            return true;
        }
        else
        {
            double a1 = (ba.x*bc.x + ba.y*bc.y) / sqrt(bc.x*bc.x + bc.y*bc.y);
            double a2 = (ba.x*bd.x + ba.y*bd.y) / sqrt(bd.x*bd.x + bd.y*bd.y);
            if (a1 > a2)
                return true;
            else
                return false;
        }
    }
}

bool is_diagnoal(const std::vector<Point>& V, int a, int b) {
    /*
    Given a simple polygon and its diagonal,
    check, whether it is external, internal, or intersects the side.
    V is an array of vertices of a polygon, a and b are indices of considered vertices.
    Return one of the following messages: {"INTERSECT, "INTERNAL", "EXTERNAL"}.
    */
    // YOUR CODE HERE
    bool debug = false;
    int cnt = V.size();

    Point va = V[a];
    Point vb = V[b];

    if (debug){
        printf("\n\na-b: %lld %lld, ", va.x, va.y);
        printf(" %lld %lld\n", vb.x, vb.y);
    }
    for (int i = 0; i < cnt; i++)
    {
        int next = i + 1;
        Point c = V[i];
        if (next == cnt)
            next = 0;
        // ignore the neighbour
        if (i == a || i == b || next == a || next == b)
            continue;
        Point d = V[next];
        if (segment_cross(va, vb, c, d))
        {
            // if (debug)
            // {
            //     printf("c: %lld %lld\n", c.x, c.y);
            //     printf("d: %lld %lld\n", d.x, d.y);
            //     segment_cross(va, vb, c, d, true);
            // }
            return false;
        }
        // else if (debug){
        //     printf("c: %lld %lld\n", c.x, c.y);
        //     printf("d: %lld %lld\n", d.x, d.y);
        //     printf("not cross with a-b\n");
        // }
    }
    // no cross
    int b0 = b - 1;
    int b1 = b + 1;
    if (b0 < 0)
        b0 = cnt - 1;
    if (b1 >= cnt)
        b1 = b1 - cnt;
    Point vb0 = V[b0];
    Point vb1 = V[b1];
    if (inner_point(vb0, vb, vb1, va))
    {
        if (debug){
            printf("a-b is a diagnal\n");
        }
        return true;
    }
    else
        return false;
}

std::vector<std::vector<Point>> list_all_triangles(const std::vector<Point>& polygon) {
    /*
    Triangulate a~given polygon by the ear-cutting algorithm.
    Polygon is given as an array of its vertices.
    Return an array of triples (A, B, C) for every triangle ABC.
    */
    std::vector<std::vector<Point>> list_of_triangles;

    // YOUR CODE HERE
    std::vector<Point> polygon_array = polygon;
    while (polygon_array.size() > 3)
    {
        for (int i = 0; i < polygon_array.size(); i++)
        {
            int a = i - 1;
            int b = i + 1;
            if (a < 0) a = polygon_array.size() - 1;
            if (b == polygon_array.size()) b = 0;
            if (is_diagnoal(polygon_array, a, b))
            {
                list_of_triangles.push_back({polygon_array[a], polygon_array[i], polygon_array[b]});
                polygon_array.erase(polygon_array.begin() + i);
                break;
            }
        }
        // printf("can`t find a diagnoal of polygon\n");
        // for (Point p: polygon_array)
        // {
        //     printf("%lld %lld,", p.x, p.y);
        // }
        // exit(1);
    }
    list_of_triangles.push_back({
        polygon_array[0],
        polygon_array[1],
        polygon_array[2]});
    return list_of_triangles;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<Point> V(n);
    std::vector<int> V_coord(2 * n);
    for (int &item : V_coord) {
        std::cin >> item;
    }
    for (int i = 0; i < n; ++i) {
        V[i].x = V_coord[2 * i];
        V[i].y = V_coord[2 * i + 1];
    }
    std::vector<std::vector<Point>> triangulation;
    triangulation = list_all_triangles(V);
    int number_of_triags;
    number_of_triags = triangulation.size();
    std::cout << number_of_triags << std::endl;
    for (int i = 0; i < number_of_triags; ++i) {
        std::cout << triangulation[i][0].x << ' ' << triangulation[i][0].y << ' ' << triangulation[i][1].x << ' ' << triangulation[i][1].y << ' ' << triangulation[i][2].x << ' ' << triangulation[i][2].y << std::endl;
    }
}
