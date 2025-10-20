#include <iostream>

#define _USE_MATH_DEFINES

#include "math.h"

const double EPSILON = 1e-3;

// Минимальный n для sin t по Маклорену в 0: |R_{n+1}| <= tmax^{n+1}/(n+1)!
int min_n_sin_mac(double tmax, double epsilon){
    int n = 0;
    double term = tmax; // t^{1}/1!
    while(term > epsilon){
        n++;
        term *= tmax / (n + 1); // теперь t^{n+1}/(n+1)!
    }
    return n;
}

// Минимальный n для exp t по Маклорену в 0: |R_{n+1}| <= e^{tmax} * tmax^{n+1}/(n+1)!
int min_n_exp_mac(double tmax, double epsilon){
    int n = 0;
    double pref = exp(tmax);
    double term = pref * tmax; // e^{tmax} * t^{1}/1!
    while(term > epsilon){
        n++;
        term *= tmax / (n + 1); // умножаем на t/(n+1)
    }
    return n;
}

// Улучшение для sin: ставим в аргумент число Пи
int min_n_sin_improved(double epsilon){
    return min_n_sin_mac(M_PI, epsilon);
}

// Улучшение для экспоненты: разложение в центре t0 отрезка
// Оценка остатка: e^{t0+r} * r^{n+1}/(n+1)!, где r=(b-a)/2
int min_n_exp_center(double a, double b, double epsilon){
    double t0 = 0.5*(a+b);
    double r  = 0.5*(b-a);
    int n = 0;
    double term = exp(t0 + r) * r; // первый остаточный член
    while(term > epsilon){
        n++;
        term *= r / (n + 1);
    }
    return n;
}

int main(){
    std::cout << std::fixed;

    std::cout << "Маклорен (в 0), epsilon = 1e-3:\n";
    std::cout << " sin t на [0,1]   : n = " << min_n_sin_mac(1.0, EPSILON)  << "\n";
    std::cout << " sin t на [10,11] : n = " << min_n_sin_mac(11.0, EPSILON) << "\n";
    std::cout << " exp t на [0,1]   : n = " << min_n_exp_mac(1.0, EPSILON)  << "\n";
    std::cout << " exp t на [10,11] : n = " << min_n_exp_mac(11.0, EPSILON) << "\n\n";

    std::cout << "Улучшенные алгоритмы:\n";
    std::cout << " sin t: n = " << min_n_sin_improved(EPSILON) << "\n";
    std::cout << " exp t на [0,1]  (Тейлор в центре)   : n = " << min_n_exp_center(0.0, 1.0, EPSILON)   << "\n";
    std::cout << " exp t на [10,11] (Тейлор в центре)   : n = " << min_n_exp_center(10.0, 11.0, EPSILON) << "\n";

    return 0;
}
