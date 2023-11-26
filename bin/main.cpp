#include "lib/3DArray.h"

int main() {
    Array3D array(10, 10, 10);
    array.at(0, 0, 0) = 10;
    array.at(0, 0, 1) = 2;
    std::cout << array.at(0, 0, 0) << '\n';
    std::cout << (array.at(0, 0, 0) < 2 ? "true\n" : "false\n");

    int x = 5;
    x /= 2.0;
    std::cout << x << '\n';
    return 0;
}
