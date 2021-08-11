#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <set>
#include <deque>

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
        return a.y > b.y;
}

int64_t cross(Point a, Point b, Point a1, Point b1)
{
    int64_t x1 = b.x - a.x;
    int64_t y1 = b.y - a.y;
    int64_t x2 = b1.x - a1.x;
    int64_t y2 = b1.y - a1.y;
    return x1*y2 - x2*y1;
}

std::vector<Point> convert_UP(std::set<Point> &order_point)
{
    std::deque<Point> ch_deque;
    auto iter_order = order_point.rbegin();
    ch_deque.push_back(*iter_order++);
    ch_deque.push_back(*(iter_order++));
    for (; iter_order != order_point.rend(); iter_order++)
    {
        while(true)
        {
            auto deq_iter = ch_deque.rbegin();
            Point b = *deq_iter++;
            Point a = *deq_iter;
            Point c = *iter_order;
            // on the left
            if (cross(a,b, a,c) <= 0)
            {
                // printf("on the right or line:\n(%d %d),(%d %d),(%d %d)\n",
                //         a.x, a.y, b.x, b.y, c.x, c.y);
                ch_deque.pop_back();
                if (ch_deque.size() < 2)
                {
                    ch_deque.push_back(c);
                    break;
                }
            }
            else
            {
                // printf("on the left:\n(%d %d),(%d %d),(%d %d)\n",
                //         a.x, a.y, b.x, b.y, c.x, c.y);
                ch_deque.push_back(c);
                break;
            }
        }
    }
    std::vector<Point> result(ch_deque.begin(), ch_deque.end());
    return result;
}

std::vector<Point> convert_LOW(std::set<Point> &order_point)
{
    std::deque<Point> ch_deque;
    auto iter_order = order_point.begin();
    ch_deque.push_back(*iter_order++);
    ch_deque.push_back(*(iter_order++));
    for (; iter_order != order_point.end(); iter_order++)
    {
        while(true)
        {
            auto deq_iter = ch_deque.rbegin();
            Point b = *deq_iter++;
            Point a = *deq_iter;
            Point c = *iter_order;
            // on the left
            if (cross(a,b, a,c) <= 0)
            {
                // printf("on the right or line:\n(%d %d),(%d %d),(%d %d)\n",
                //         a.x, a.y, b.x, b.y, c.x, c.y);
                ch_deque.pop_back();
                if (ch_deque.size() < 2)
                {
                    ch_deque.push_back(c);
                    break;
                }
            }
            else
            {
                // printf("on the left:\n(%d %d),(%d %d),(%d %d)\n",
                //         a.x, a.y, b.x, b.y, c.x, c.y);
                ch_deque.push_back(c);
                break;
            }
        }
    }
    std::vector<Point> result(ch_deque.begin(), ch_deque.end());
    return result;
}

std::vector<Point> convex_hull(const std::vector<Point>& V) {
    /*
    Build a convex hull of the given n points (i.e., build a convex polygon
    with a minimum perimeter that contains all the points).
    V is a set of points.
    Return a subset of V, which describes a convex hull.
    */
    std::vector<Point> result;

    // YOUR CODE HERE
    // std::sort(V.begin(), V.end());
    std::set<Point> order_point(V.begin(), V.end());
    // printf("=======UP HULL\n");
    std::vector<Point> res1 = convert_UP(order_point);
    // for (Point p: res1)
    // {
    //     printf("%d %d, ", p.x, p.y);
    // }
    // printf("\n");
    // printf("=======UP LOW\n");
    std::vector<Point> res2 = convert_LOW(order_point);
    // for (Point p: res2)
    // {
    //     printf("%d %d, ", p.x, p.y);
    // }
    // printf("\n");
    result.insert(result.end(), res1.begin(), res1.end());
    if (res2.size() > 2)
        result.insert(result.end(), res2.begin() + 1, res2.end() - 1);
    return result;
}

int main() {
    int n;
    std::cin >> n;
    int m;
    std::vector<Point> V(n);
    std::vector<Point> p;
    std::vector<int> V_coord(2 * n);
    for (int &item : V_coord) {
        std::cin >> item;
    }
    for (int i = 0; i < n; ++i) {
        V[i].x = V_coord[2 * i];
        V[i].y = V_coord[2 * i + 1];
    }
    p = convex_hull(V);
    m = p.size();
    std::cout << m << std::endl;
    for (int i = 0; i < m; ++i) {
        std::cout << p[i].x << ' ' << p[i].y << ' ' << " ";
    }
    return 0;
}
