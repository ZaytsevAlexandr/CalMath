#include <iostream>
#include <cmath>

using namespace std;

int main() {
    // Начальное приближение
    double x = 0.8;
    double y = 0.6;

    // Точность
    double epsilon = 1e-6;

    // Максимальное количество итераций
    int max_iterations = 100;

    for (int i = 0; i < max_iterations; i++) {
        // Вычисляем значения функций
        double f1 = x * x + y * y - 1;  // x^2 + y^2 - 1 = 0
        double f2 = y - tan(x);         // y - tg(x) = 0

        // Вычисляем элементы матрицы Якоби
        double j11 = 2 * x;     // производная f1 по x
        double j12 = 2 * y;     // производная f1 по y
        double j21 = -1 / (cos(x) * cos(x));  // производная f2 по x
        double j22 = 1;         // производная f2 по y

        // Определитель матрицы Якоби
        double det = j11 * j22 - j12 * j21;

        // Решаем систему для поправок
        double dx = (-f1 * j22 + f2 * j12) / det;
        double dy = (-f2 * j11 + f1 * j21) / det;

        // Обновляем значения
        x = x + dx;
        y = y + dy;

        // Проверяем условие сходимости
        if (abs(dx) < epsilon && abs(dy) < epsilon) {
            cout << "Решение найдено на итерации " << i + 1 << ":" << endl;
            cout << "x = " << x << endl;
            cout << "y = " << y << endl;
            cout << "Проверка: x^2 + y^2 - 1 = " << x * x + y * y - 1 << endl;
            cout << "Проверка: y - tg(x) = " << y - tan(x) << endl;
            break;
        }

        // Если достигнут предел итераций
        if (i == max_iterations - 1) {
            cout << "Достигнуто максимальное количество итераций" << endl;
            cout << "Текущее приближение: x = " << x << ", y = " << y << endl;
        }
    }

    return 0;
}