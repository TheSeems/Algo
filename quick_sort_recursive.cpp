#include <bits/stdc++.h>
using namespace std;

// Stands for element type
using el_t = int;

// Stands for index type
using ind_t = int64_t;

// Get pivot from array, can be overloaded
inline el_t get_pivot(el_t* a, ind_t l, ind_t r) {
  return a[(l + r) / 2];
}

void quick_sort(el_t* a, ind_t l, ind_t r) {
  ind_t i = l, j = r;
  el_t pivot = get_pivot(a, l, r);

  // aparting array
  while (i <= j) {
    while (a[i] < pivot)
      i++;
    while (a[j] > pivot)
      j--;
    if (i <= j)
      swap(a[i], a[j]), i++, j--;
  }

  // divide and conquer
  // left part
  if (l < j)
    quick_sort(a, l, j);
  // right part
  if (i < r)
    quick_sort(a, i, r);
}

// Driver
// Tested at task: https://informatics.mccme.ru/mod/statements/view3.php?id=1129&chapterid=766#1
int main() {
  ind_t size = 0;
  cin >> size;

  el_t* arr = new el_t[size];
  for (ind_t i = 0; i < size; i++)
    cin >> arr[i];

  quick_sort(arr, 0, size - 1);
  
  for (ind_t i = 0; i < size; i++)
    cout << arr[i] << ' ';
    
  return 0;
}
