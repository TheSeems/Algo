#include <bits/stdc++.h>

double integral(std::function<double(double)> f, double x_min, double x_max,
                double y_max, double iterations = 2e7, double y_min = 0) {

  double cnt = 0, total = 0, in_box = 0;
  for (cnt = 0; cnt < iterations; cnt++) {
    double u1 = (double)rand() / (double)RAND_MAX;
    double u2 = (double)rand() / (double)RAND_MAX;

    double dx = ((x_max - x_min) * u1) + x_min;
    double dy = ((y_max - y_min) * u2) + y_min;
    double val = f(dx);

    total++;

    if (val >= dy)
      in_box++;
  }

  double density = in_box / total;
  return (x_max - x_min) * (y_max - y_min) * density;
}

void grab_max(std::function<double(double)> f, double x_min, double x_max,
              double &mx, double epsilon = 1e-5) {
  mx = f(x_min);
  for (double d = x_min + epsilon; d <= x_max; d += epsilon) {
    double res = f(d);
    if (res > mx)
      mx = res;
  }
}

int main() {
  // Example
  auto func = [](double x) { return 0.35 * x * x - 0.95 * x + 2.7; };

  // Maximum in range [x_min, x_max] of function
  double mx;
  grab_max(func, 0, 1, mx);

  std::cout << integral(func, 0, 1, mx) << std::endl;
  return 0;
}
