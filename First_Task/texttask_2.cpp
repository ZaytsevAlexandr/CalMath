#include <iostream>
#include <cmath>
using namespace std;

double f(double x) { return sin(100.0*x) * exp(-x*x) * cos(2.0*x); }

// Симпсон на N отрезков (N должно быть чётным)
double simpson(double a, double b, int N){
    double h = (b - a) / N;
    double s = f(a) + f(b);
    double x;

    // нечётные узлы (множитель 4)
    for (int k = 1; k < N; k += 2){
        x = a + k * h;
        s += 4.0 * f(x);
    }
    // чётные узлы (множитель 2)
    for (int k = 2; k < N; k += 2){
        x = a + k * h;
        s += 2.0 * f(x);
    }
    return s * (h / 3.0);
}

int main(){
    cout << fixed;

    const double a = 0.0, b = 3.0;
    const double accuracy = 1e-8;
    const double H_min = 1e-12;
    int N = 256;

    double S = simpson(a, b, N);
    while (true){
        int N2 = 2 * N;
        double S2 = simpson(a, b, N2);
        // Оценка ошибки по Ричардсону для Симпсона: |S2 - S| / 15
        double err = fabs(S2 - S) / 15.0;
        if(err < accuracy){
            S = S2;
            break;
        }
        S = S2;
        N = N2;
        double H = (b - a) / N;
        if (H < H_min)
            break;
    }

    cout.precision(10);
    cout << "I ≈ " << S << '\n';
    return 0;
}
