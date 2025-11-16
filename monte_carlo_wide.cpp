#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <iomanip>
#include <algorithm>

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::min;
using std::fixed;
using std::max;
using std::setprecision;
using std::mt19937_64;
using std::uniform_real_distribution;

struct Circle {
    double x, y, r;
};

bool is_inside_all(double x, double y, Circle c[3]) {
    for (int j = 0; j < 3; ++j) {
        double dx = x - c[j].x;
        double dy = y - c[j].y;
        if (dx * dx + dy * dy > c[j].r * c[j].r) {
            return false;
        }
    }
    return true;
}


int main() {
    // Отключить синхронизацию между iostream и stdio.
    std::ios::sync_with_stdio(false);

    // Отключить синхронизацию между std::cin и std::cout.
    std::cin.tie(nullptr);
    Circle c[3];
    for (int i = 0; i < 3; ++i) {
        cin >> c[i].x >> c[i].y >> c[i].r;
    }
    double minX, maxX, minY, maxY;
    minX = c[0].x - c[0].r;
    maxX = c[0].x + c[0].r;
    minY = c[0].y - c[0].r;
    maxY = c[0].y + c[0].r;
    for (int i = 1; i < 3; ++i) {
        minX = min(minX, c[i].x - c[i].r);
        maxX = max(maxX, c[i].x + c[i].r);
        minY = min(minY, c[i].y - c[i].r);
        maxY = max(maxY, c[i].y + c[i].r);
    }
    double width = maxX - minX;
    double height = maxY - minY;
    if (width <= 0.0 || height <= 0.0) {
        cout << std::fixed << std::setprecision(15) << 0.0;
        return 0;
    }

    double Srect = width * height;
    long long N;
    cin >> N;

    mt19937_64 rng(52);
    uniform_real_distribution<double> dx(minX, maxX);
    uniform_real_distribution<double> dy(minY, maxY);


    long long inside = 0;
    for (long long i = 0; i < N; ++i) {
        double x = dx(rng), y = dy(rng);
        if (is_inside_all(x, y, c)) {
            ++inside;
        }
    }

    double estimate = Srect * (double(inside) / double(N));
    cout << std::fixed << std::setprecision(15) << estimate;
    return 0;
}
