#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


int cross(int x0, int y0, int x1, int y1, int x2, int y2)
{
    return (x1 - x0)*(y2 - y0) - (y1 - y0)*(x2 - x0);
}

bool on_segment(int x0, int y0, int x1, int y1, int px, int py)
{
    int dir_x = (px - x0)*(px - x1);
    int dir_y = (py - y0)*(py - y1);
    return (dir_x <= 0 && dir_y <= 0);
}

std::string determine_point_position(int A_x, int A_y, int B_x, int B_y, int C_x, int C_y, int p_x, int p_y) {
    /*
    Given a triangle ABC and n points p1, p2, ... , pn on the plane, determine for each point
    whether it is inside, outside, or on the border of the triangle.
    A_x, A_y, B_x, B_y, C_x, C_y are coordinates of A, B and C respectively.
    p_x, p_y - coordinates of p.
    return: one of {"INSIDE", "OUTSIDE", "BORDER"}
    */
    std::string result;

    // YOUR CODE HERE
    int dir_a = cross(A_x, A_y, B_x, B_y, p_x, p_y);
    int dir_b = cross(B_x, B_y, C_x, C_y, p_x, p_y);
    int dir_c = cross(C_x, C_y, A_x, A_y, p_x, p_y);

    if ((dir_a < 0 && dir_b < 0 && dir_c < 0) ||
        (dir_a > 0 && dir_b > 0 && dir_c > 0))
        result = "INSIDE";
    else if (dir_a == 0 && on_segment(A_x, A_y, B_x, B_y, p_x, p_y))
        result = "BORDER";
    else if (dir_b == 0 && on_segment(B_x, B_y, C_x, C_y, p_x, p_y))
        result = "BORDER";
    else if (dir_c == 0 && on_segment(C_x, C_y, A_x, A_y, p_x, p_y))
        result = "BORDER";
    else
        result = "OUTSIDE";

    return result;
}

int main() {
    int A_x, A_y, B_x, B_y, C_x, C_y;
    std::cin >> A_x >> A_y >> B_x >> B_y >> C_x >> C_y;
    int n;
    std::cin >> n;
    std::vector<int> p_x(n);
    std::vector<int> p_y(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> p_x[i] >> p_y[i];
    }
    for (int i = 0; i < n; ++i) {
        std::string result;
        result = determine_point_position(A_x, A_y, B_x, B_y, C_x, C_y, p_x[i], p_y[i]);
        std::cout << result << std::endl;
    }
}
