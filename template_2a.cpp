#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


class Point {
public:
    int x;
    int y;
};

int cross(Point a, Point b, Point c)
{
    return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

std::string is_convex(const std::vector<Point>& V) {
    /*
    Given a simple polygon V1 V2 ... Vn, determine whether it is convex.
    V: vertices of polygon, vertices are listed in counterclockwise order
    return: CONVEX, if polygon is convex. NOT_CONVEX, if polygon is not convex.
    */
    std::string result;

    // YOUR CODE HERE
    result = "CONVEX";
    for (int i = 0; i < V.size(); i++)
    {
        int ia = i;
        int ib = i + 1;
        int ic = i + 2;
        if (ib >= V.size())
            ib -= V.size();
        if (ic >= V.size())
            ic -= V.size();
        Point a = V[ia], b = V[ib], c = V[ic];
        int val = cross(a, b, c);
        if (val < 0)
            return "NOT_CONVEX";
    }
    return result;
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
    std::string result = is_convex(V);
    std::cout << result << std::endl;
}
