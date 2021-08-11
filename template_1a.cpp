#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


std::string determine_point_position(int A_x, int A_y, int B_x, int B_y, int p_x, int p_y) {
    /*
    Given a vector AB (starting at point A and ending at point B) and point p on the plane,
    determine the relative position of each point with respect to the vector:
    point lies either on the right side, or on the left side,
    or on the vector, or on the continuation of the vector.
    A_x, A_y, B_x, B_y are coordinates of A and B respectively.
    p_x, p_y - coordinates of p.
    return: one of {"LEFT", "RIGHT", "ON_SEGMENT", "ON_LINE"}
    */
    std::string result;

    // YOUR CODE HERE
    int val = (B_x - A_x)*(p_y - A_y) - (B_y - A_y)*(p_x - A_x);
    if (val > 0)
        result = "LEFT";
    else if (val < 0)
        result = "RIGHT";
    else if (val == 0)
    {
        int dir_x = (p_x - A_x)*(p_x - B_x);
        int dir_y = (p_y - A_y)*(p_y - B_y);
        if (dir_x > 0 || dir_y > 0)
            result = "ON_LINE";
        else
            result = "ON_SEGMENT";
    }
    return result;
}

int main() {
    int A_x, A_y, B_x, B_y;
    std::cin >> A_x >> A_y >> B_x >> B_y;
    int n;
    std::cin >> n;
    std::vector<int> p_x(n);
    std::vector<int> p_y(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> p_x[i] >> p_y[i];
    }
    for (int i = 0; i < n; ++i) {
        std::string result;
        result = determine_point_position(A_x, A_y, B_x, B_y, p_x[i], p_y[i]);
        std::cout << result << std::endl;
    }
}
