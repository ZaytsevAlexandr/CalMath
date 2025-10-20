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

// Кубический сплайн: решение на M''(xi)
// Решаем трёхдиагональную систему методом прогонки.
void spline_M_default(const double *x, const double *y, int n, double *M){
    // граничные условия: M[0]=M[n-1]=0
    M[0] = 0.0; M[n-1] = 0.0;

    double a[N], b[N], c[N], d[N]; // диагонали и правая часть для i=1..n-2
    for (int i = 1; i <= n-2; ++i){
        double h0 = x[i]   - x[i-1];
        double h1 = x[i+1] - x[i];
        a[i] = h0;
        b[i] = 2.0*(h0 + h1);
        c[i] = h1;
        d[i] = 6.0 * ( (y[i+1]-y[i]) / h1 - (y[i]-y[i-1]) / h0 );
    }

    // Прогонка
    double c1[N], d1[N];
    c1[1] = c[1] / b[1];
    d1[1] = d[1] / b[1];
    for (int i = 2; i <= n-2; ++i){
        double denom = b[i] - a[i]*c1[i-1];
        c1[i] = c[i] / denom;
        d1[i] = (d[i] - a[i]*d1[i-1]) / denom;
    }
    M[n-2] = d1[n-2];
    for (int i = n-3; i >= 1; --i){
        M[i] = d1[i] - c1[i]*M[i+1];
    }
}

// Кубический сплайн-полином на отрезке [x_i,x_(i+1)] (допускаем x вне отрезка — формула всё равно задаёт кубик)
double spline_value_segment(double xq, const double *x, const double *y, const double *M, int i){
    double h = x[i+1]-x[i];
    double A = (x[i+1]-xq)/h;
    double B = (xq - x[i])/h;
    double term =  ( (A*A*A - A)*h*h/6.0 )*M[i]
                 + ( (B*B*B - B)*h*h/6.0 )*M[i+1]
                 + A*y[i] + B*y[i+1];
    return term;
}

double spline_value_extrap_right(double xq, const double *x, const double *y, const double *M, int n){
// используем последний кубический сегмент [x_(n-2), x_(n-1)] как продолжение
    int i = n-2;
    return spline_value_segment(xq, x, y, M, i);
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

    // Сплайн
    double Mnat[N];
    spline_M_default(t, pop, N, Mnat);
    double spline_nat_2010 = spline_value_extrap_right(t2010, t, pop, Mnat, N);

    const double true_2010 = 308745538.0;

    std::cout.precision(0);
    std::cout << "Экстраполяция численности населения США на 2010 год\n";
    std::cout << "Ньютон: " << newton_2010 
         << "\t   |ошибка| = " << fabs(newton_2010 - true_2010) << "\n";
    std::cout << "Сплайн: " << spline_nat_2010
         << "\t   |ошибка| = " << fabs(spline_nat_2010 - true_2010) << "\n";

    return 0;
}