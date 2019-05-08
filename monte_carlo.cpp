#include <bits/stdc++.h>

double integral(std::function<double(double)> f, double x_min, double x_max,
                double y_min, double y_max, double iterations = 2e7) {

  double cnt = 0, total = 0, in_box = 0;
  for (cnt = 0; cnt < iterations; cnt++) {
    double u1 = (double)rand() / (double)RAND_MAX;
    double u2 = (double)rand() / (double)RAND_MAX;

    double dx = ((x_max - x_min) * u1) + x_min;
    double dy = ((y_max - y_min) * u2) + y_min;
    double val = f(dx);

    total++;

    if (val > dy)
      in_box++;
  }

  double density = in_box / total;
  return (x_max - x_min) * (y_max - y_min) * density;
}

void grab_max_min(std::function<double(double)> f, double a, double b,
                  double &mn, double &mx, double epsilon = 1e-6) {
  for (double d = a; d <= b; d += epsilon) {
    double res = f(d);
    if (res < mn)
      mn = res;
    if (res > mx)
      mx = res;
  }
}

int main() {
  auto func = [](double x) { return 0.35 * x * x - 0.95 * x + 2.7; };
  //auto func = [] (double x) { return x; };

  double mx, mn;
  grab_max_min(func, 0, 1, mn, mx);

  std::cout << integral(func, 0, 1, mn, mx) << std::endl;
}
