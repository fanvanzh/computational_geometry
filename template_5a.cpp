#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

bool debug = false;

class Node
{
public:
    Node *a, *b;
    int _val = 0;
public:
    Node(int val){
        a = b = NULL;
        _val = val;
    }

    ~Node()
    {
        if (a)
            delete a;
        if (b)
            delete b;
    }

    void insert(int val)
    {
        if (val < _val)
        {
            if (a != NULL)
                a->insert(val);
            else
                a = new Node(val);
        }
        else
        {
            if (b != NULL)
                b->insert(val);
            else
                b = new Node(val);
        }
    }

    void findCloset(int q, int& low, int& up)
    {
        if (q == _val)
        {
            low = up = q;
            if (debug)
                printf("found val: %d\n", _val);
        }
        else if (q < _val)
        {
            up = _val;
            if (debug)
                printf("found up val: %d\n", _val);
            if (a)
            {
                return a->findCloset(q, low, up);
            }
        }
        else if (q > _val)
        {
            low = _val;
            if (debug)
                printf("found low val: %d\n", _val);
            if(b)
            {
                return b->findCloset(q, low, up);
            }
        }
    }
};

std::vector<int> determine_nearest_point(const std::vector<int>& S, const std::vector<int>& Q) {
    /*
    Given a set S of points on a line and a set Q of query points,
    find the closest neighbor of the query point,
    i.e., a point from S with the minimum distance to the query point.
    Return array of answers on the queries
    */
    std::vector<int> results;

    // YOUR CODE HERE
    if (S.empty())
        return results;

    Node *node = new Node(S.front());
    for (int i = 1; i < S.size(); i++)
    {
        node->insert(S[i]);
    }

    for (int q: Q)
    {
        int v0 = INT_MIN, v1 = INT_MAX;
        if (debug)
            printf("\n--- found %d \n", q);
        node->findCloset(q, v0, v1);
        if (v0 == v1)
            results.push_back(v0);
        else if (v0 == INT_MIN)
            results.push_back(v1);
        else if (v1 == INT_MAX)
            results.push_back(v0);
        else
            results.push_back(
                abs(q - v0) >= abs(q - v1) ? v1 : v0
            );
    }
    delete node;
    return results;
}

int main() {
    int n;
    std::cin >> n;
    int m;
    std::vector<int> line_points(n);
    for (int &item : line_points) {
        std::cin >> item;
    }
    std::cin >> m;
    std::vector<int> queries(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> queries[i];
    }
    std::vector<int> result;
    result = determine_nearest_point(line_points, queries);
    for (int i = 0; i < m; ++i) {
        std::cout << result[i] << std::endl;
    }
}
