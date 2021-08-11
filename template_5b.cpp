#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


class Point {
public:
    int x;
    int y;
};

// bool debug = true;
bool debug = false;

class KDTree
{
    bool tag_x;
    int _key;
    std::vector<Point> points;
    KDTree *node_a, *node_b;
public:
    KDTree(bool _x){
        tag_x = _x;
        node_a = node_b = NULL;
    }
    void insert(Point p)
    {
        points.push_back(p);
    }
    void split()
    {
        if (points.size() > 4)
        {
            std::sort(points.begin(), points.end(), [&](const Point p1, const Point p2){
                if (tag_x)
                    return p1.x < p2.x;
                else
                    return p1.y < p2.y;
            });
            node_a = new KDTree(!tag_x);
            node_b = new KDTree(!tag_x);
            int half_size = points.size() / 2;
            _key = tag_x ?
                points[half_size - 1].x: // x next is y
                points[half_size - 1].y;
            for (int i = 0; i < points.size(); i++)
            {
                if (tag_x)
                {
                    if (points[i].x <= _key)
                        node_a->insert(points[i]);
                    else
                        node_b->insert(points[i]);
                }
                else
                {
                    if (points[i].y <= _key)
                        node_a->insert(points[i]);
                    else
                        node_b->insert(points[i]);
                }
            }
            points.clear();
        }
    }
    void query(int minx, int miny, int maxx, int maxy, int &count)
    {
        if (node_a == node_b && node_a == NULL)
        {
            for (Point p: points)
            {
                if (debug)
                    printf("point: %d, %d\n", p.x, p.y);
                if (minx <= p.x && p.x <= maxx && miny <= p.y && p.y <= maxy)
                {
                    count += 1;
                    if (debug)
                        printf("****** hit one *****\n");
                }
            }
        }
        else
        {
            int val1 = minx;
            int val2 = maxx;
            if (!tag_x)
            {
                val1 = miny;
                val2 = maxy;
            }
            if (val1 > _key)
                node_b->query(minx, miny, maxx, maxy, count);
            else if (val2 <= _key)
                node_a->query(minx, miny, maxx, maxy, count);
            else
            {
                node_a->query(minx, miny, maxx, maxy, count);
                node_b->query(minx, miny, maxx, maxy, count);
            }
        }
    }
};


std::vector<int> count_inside_points(const std::vector<Point>& S, const std::vector<std::vector<Point>>& queries) {
    /*
    Given a set of points S and a set of query rectangles with sides parallel to the axes.
    Compute the number of points from S lying inside each rectangle.
    Any of the two sides of the rectangle may have zero length
    (in such a case, the rectangle degenerates to a segment or a point).
    Return array of answers on queries.
    */
    std::vector<int> results;

    // YOUR CODE HERE
    KDTree tree(true);
    for (Point p: S)
    {
        tree.insert(p);
    }
    tree.split();
    for (std::vector<Point> rectangle: queries)
    {
        int minx = std::min(rectangle[0].x, rectangle[1].x);
        int maxx = std::max(rectangle[0].x, rectangle[1].x);
        int miny = std::min(rectangle[0].y, rectangle[1].y);
        int maxy = std::max(rectangle[0].y, rectangle[1].y);
        int count = 0;
        if (debug)
            printf("\n-- query box: %d %d, %d %d\n", minx, miny, maxx, maxy);
        tree.query(minx, miny, maxx, maxy, count);
        results.push_back(count);
    }
    return results;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<Point> points(n);
    std::vector<int> points_coord(2 * n);
    for (int &item : points_coord) {
        std::cin >> item;
    }
    for (int i = 0; i < n; ++i) {
        points[i].x = points_coord[2 * i];
        points[i].y = points_coord[2 * i + 1];
    }
    int q;
    std::cin >> q;
    std::vector<std::vector<Point>> queries(q);
    for (int i = 0; i < q; ++i) {
        std::vector<Point> rectangle(2);
        std::cin >> rectangle[0].x >> rectangle[0].y >> rectangle[1].x >> rectangle[1].y;
        queries[i] = rectangle;
    }
    std::vector<int> result;
    result = count_inside_points(points, queries);
    for (int i = 0; i < q; ++i) {
        std::cout << result[i] << std::endl;
    }
}
