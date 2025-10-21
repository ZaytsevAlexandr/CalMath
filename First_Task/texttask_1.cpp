#include <iostream>
#include <cmath>

using namespace std;

int main() {
    // ��������� �����������
    double x = 0.8;
    double y = 0.6;

    // ��������
    double epsilon = 1e-6;

    // ������������ ���������� ��������
    int max_iterations = 100;

    for (int i = 0; i < max_iterations; i++) {
        // ��������� �������� �������
        double f1 = x * x + y * y - 1;  // x^2 + y^2 - 1 = 0
        double f2 = y - tan(x);         // y - tg(x) = 0

        // ��������� �������� ������� �����
        double j11 = 2 * x;     // ����������� f1 �� x
        double j12 = 2 * y;     // ����������� f1 �� y
        double j21 = -1 / (cos(x) * cos(x));  // ����������� f2 �� x
        double j22 = 1;         // ����������� f2 �� y

        // ������������ ������� �����
        double det = j11 * j22 - j12 * j21;

        // ������ ������� ��� ��������
        double dx = (-f1 * j22 + f2 * j12) / det;
        double dy = (-f2 * j11 + f1 * j21) / det;

        // ��������� ��������
        x = x + dx;
        y = y + dy;

        // ��������� ������� ����������
        if (abs(dx) < epsilon && abs(dy) < epsilon) {
            cout << "������� ������� �� �������� " << i + 1 << ":" << endl;
            cout << "x = " << x << endl;
            cout << "y = " << y << endl;
            cout << "��������: x^2 + y^2 - 1 = " << x * x + y * y - 1 << endl;
            cout << "��������: y - tg(x) = " << y - tan(x) << endl;
            break;
        }

        // ���� ��������� ������ ��������
        if (i == max_iterations - 1) {
            cout << "���������� ������������ ���������� ��������" << endl;
            cout << "������� �����������: x = " << x << ", y = " << y << endl;
        }
    }

    return 0;
}