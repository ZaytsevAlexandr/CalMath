#include <iostream>

#include "math.h"


double f(double x) { return x * exp(-x*x); }

double left_root(double H, double epsilon=1e-3, int max_it=100000) {
    // из x*e^{-x^2}=H => x = H * e^{x^2}
    double x = H; // чтобы старт близко к левому корню
    for (int it = 0; it < max_it; it++) {
        double x_new = H * exp(x*x);
        if (fabs(x_new - x) < epsilon) return x_new;
        x = x_new;
    }
    return x;
}

double right_root(double H, double epsilon=1e-3, int max_it=100000) {
    // из x*e^{-x^2}=H => x^2 = ln(x/H) -> x = sqrt(ln(x/H))
    double x = 1.0; // чтобы старт правее максимума
    for (int it = 0; it < max_it; it++) {
        double x_new = sqrt(log(x / H));
        if (fabs(x_new - x) < epsilon) return x_new;
        x = x_new;
    }
    return x;
}

int main() {
    const double x0  = 1. / sqrt(2.); // точка максимума
    const double fmax = f(x0);
    const double H = 0.5 * fmax; // полувысота

    double x1 = left_root(H);
    double x2 = right_root(H);
    double width = x2 - x1;

    std::cout << std::fixed;
    std::cout.precision(3);
    std::cout << "x1 = " << x1 << ", f(x1) = " << f(x1) << '\n';
    std::cout << "x2 = " << x2 << ", f(x2) = " << f(x2) << '\n';
    std::cout << "x2 - x1 = " << width << '\n';
    return 0;
}

