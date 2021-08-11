#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Point {
public:
    int x;
    int y;
    Point(){x = 0; y = 0;}
    Point(int _x, int _y): x(_x), y(_y){}
    Point(const Point& p){ x = p.x; y = p.y;}
    bool operator == (Point& b)
    {
        return this->x == b.x && this->y == b.y;
    }
};

bool operator< (const Point &a, const Point &b)
{
    if (a.x != b.x)
        return a.x < b.x;
    else
        return a.y < b.y;
}

int64_t cross(Point a, Point b, Point a1, Point b1)
{
    int64_t x1 = b.x - a.x;
    int64_t y1 = b.y - a.y;
    int64_t x2 = b1.x - a1.x;
    int64_t y2 = b1.y - a1.y;
    return x1*y2 - x2*y1;
}

bool box_disjoint(Point a, Point b, Point c, Point d)
{
    if (std::max(a.x, b.x) < std::min(c.x, d.x))
        return true;
    if (std::max(a.y, b.y) < std::min(c.y, d.y))
        return true;
    if (std::min(a.x, b.x) > std::max(c.x, d.x))
        return true;
    if (std::min(a.y, b.y) > std::max(c.y, d.y))
        return true;
    return false;
}

std::string determine_relative_position(int A_x, int A_y, int B_x, int B_y, int C_x, int C_y, int D_x, int D_y) {
    /*
    Determine relative position of segments AB and CD.
    8 args of this function are coordinates of A, B, C, D
    Return one message of one of the following formats:
    No common points.
    The intersection point is (E_x, E_y).
    A common segment of non-zero length.
    */
    std::string result;

    // YOUR CODE HERE
    Point a(A_x, A_y);
    Point b(B_x, B_y);
    Point c(C_x, C_y);
    Point d(D_x, D_y);
    if (box_disjoint(a, b, c, d))
    {
        result = "No common points.";
        return result;
    }
    char msg[512];
    // two side
    int64_t side_c = cross(a, b, a, c);
    int64_t side_d = cross(a, b, a, d);
    // two side
    int64_t side_a = cross(c, d, c, a);
    int64_t side_b = cross(c, d, c, b);
    if (side_c * side_d > 0)
    {
        result = "No common points.";
    }
    else if (side_c * side_d < 0)
    {
        if (side_a * side_b > 0)
        {
            result = "No common points.";
        }
        else
        {
            double t = (double)side_c / (double)(side_c - side_d);
            t = std::abs(t);
            int x = c.x + (d.x - c.x)*t;
            int y = c.y + (d.y - c.y)*t;
            sprintf(msg, "The intersection point is (%d, %d).", x, y);
            result = msg;
        }
    }
    else
    {
        // a,b colinear c,d
        if (side_c == 0 && side_d == 0)
        {
            std::vector<Point> ab = {a,b};
            std::vector<Point> cd = {c,d};
            std::sort(ab.begin(), ab.end());
            std::sort(cd.begin(), cd.end());
            if (ab[1] == cd[0])
            {
                sprintf(msg, "The intersection point is (%d, %d).", cd[0].x, cd[0].y);
                result = msg;
            }
            else if (ab[0] == cd[1])
            {
                sprintf(msg, "The intersection point is (%d, %d).", ab[0].x, ab[0].y);
                result = msg;
            }
            else
            {
                result = "A common segment of non-zero length.";
            }
        }
        else if (side_c == 0)
        {
            sprintf(msg, "The intersection point is (%d, %d).", c.x, c.y);
            result = msg;
        }
        else
        {
            sprintf(msg, "The intersection point is (%d, %d).", d.x, d.y);
            result = msg;
        }
    }
    return result;
}

int main() {
    int A_x, A_y, B_x, B_y, C_x, C_y, D_x, D_y;
    std::cin >> A_x >> A_y >> B_x >> B_y;
    std::cin >> C_x >> C_y >> D_x >> D_y;
    std::string result = determine_relative_position(A_x, A_y, B_x, B_y, C_x, C_y, D_x, D_y);
    std::cout << result << std::endl;
}
