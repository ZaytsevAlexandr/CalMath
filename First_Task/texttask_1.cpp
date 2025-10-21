#include <iostream>
#include "math.h"

int main() {
    double x = -1;
    double y = -1;

    double epsilon = 1e-6;

    double dx, dy;

    int i = 0;

    do {
        double f1 = x * x + y * y - 1;  
        double f2 = y - tan(x);         

        double j11 = 2 * x;    
        double j12 = 2 * y;     
        double j21 = -1 / (cos(x) * cos(x));  
        double j22 = 1;         

        double det = j11 * j22 - j12 * j21;

        dx = (f1 * j22 - f2 * j12) / det;
        dy = (f2 * j11 - f1 * j21) / det;

        x = x - dx;
        y = y - dy;

        i++;

        std::cout << i << ": x = " << x << ", y = " << y << ", dx = " << dx << ", dy = " << dy << "\n";

    } while (abs(dx) >= epsilon or abs(dy) >= epsilon);

    std::cout << "x = " << x << "\n";
    std::cout << "y = " << y << "\n";
}
