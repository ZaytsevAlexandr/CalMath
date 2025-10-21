#include <iostream>
#include <cmath>

const int N = 10;
const int years[N] = {1910, 1920, 1930, 1940, 1950, 1960, 1970, 1980, 1990, 2000};
const double pop[N] = {92228496, 106021537, 123202624, 132164569, 151325798,
                        179323175, 203211926, 226545805, 248709873, 281421906};

// t = (year-1900)/10: t = 1..11
double year_to_t(int y){ return (y - 1900)/10.0; }

// Ньютон: 
void newton_coeffs(const double *x, const double *y, int n, double *a){
    // a[k] = k-я разделённая разность
    for (int i = 0; i < n; ++i) a[i] = y[i];
    for (int j = 1; j < n; ++j){
        for (int i = n-1; i >= j; --i){
            a[i] = (a[i] - a[i-1]) / (x[i] - x[i-j]);
        }
    }
}
double newton_pol_value(double xq, const double *x, const double *a, int n){
    double s = a[n-1];
    for (int i = n-2; i >= 0; --i){
        s = s*(xq - x[i]) + a[i];
    }
    return s;
}

int main(){
    std::cout << std::fixed;
    double t[N];
    for (int i = 0; i < N; ++i) t[i] = year_to_t(years[i]);

    // Ньютон
    double a[N];
    newton_coeffs(t, pop, N, a);
    double t2010 = year_to_t(2010);
    double newton_2010 = newton_pol_value(t2010, t, a, N);
  
    const double true_2010 = 308745538.0;

    std::cout.precision(0);
    std::cout << "Экстраполяция численности населения США на 2010 год\n";
    std::cout << "Ньютон: " << newton_2010 
         << "\t   |ошибка| = " << fabs(newton_2010 - true_2010) << "\n";

    return 0;

}
