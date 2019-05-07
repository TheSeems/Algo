#include <bits/stdc++.h>
using namespace std;

using el_t = int;
using ind_t = int64_t;
const int base = 10;

void count_sort(el_t* arr, ind_t n, int exp) {
  el_t* out = new el_t[n];
  int count[base] = {0};

  // Counting occurrences
  for (ind_t i = 0; i < n; i++)
    count[(arr[i] / exp) % base]++;

  // Rebuilding count
  for (ind_t i = 1; i < base; i++)
    count[i] += count[i - 1];

  // Building out
  for (ind_t i = n - 1; i >= 0; i--) {
    el_t pos = (arr[i] / exp) % base;
    out[count[pos] - 1] = arr[i];
    count[pos]--;
  }

  // copy to src
  for (ind_t i = 0; i < n; i++)
    arr[i] = out[i];
}

void radix_sort(el_t* arr, ind_t n) {
  // Get max value out of array
  el_t arr_max = arr[0];
  for (ind_t i = 1; i < n; i++)
    arr_max = max(arr_max, arr[i]);

  // count sort for every digit
  for (int exp = 1; arr_max / exp > 0; exp *= base)
    count_sort(arr, n, exp);
}

// Driver
// Tested at:
// https://informatics.mccme.ru/mod/statements/view3.php?id=1129&chapterid=766#1
// Origin: https://www.geeksforgeeks.org/radix-sort/
int main() {
  ind_t size;
  cin >> size;

  el_t* arr = new el_t[size];
  for (ind_t i = 0; i < size; i++)
    cin >> arr[i];

  radix_sort(arr, size);

  for (ind_t i = 0; i < size; i++)
    cout << arr[i] << ' ';

  return 0;
}
