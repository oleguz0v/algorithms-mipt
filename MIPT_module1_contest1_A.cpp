#include <algorithm>
#include <iostream>
#include <vector>

// Сортировка Merge_sort
std::vector<std::pair<int, int> > Merges(
    std::vector<std::pair<int, int> >& lst) {
  int n = (int)lst.size();  // Размер переданного массива
  if (n <= 1) {  // Если менять элементы не надо, возвращаем массив, заканчиваем
                 // рекурсию
    return lst;
  }
  if (n == 2) {  // Если осталось два элемента, возвращаем отсортированный массив
    if (lst[0].first < lst[1].first or
        (lst[0].first == lst[1].first and lst[0].second < lst[1].second)) {
      return lst;
    }
    swap(lst[0], lst[1]);
    return lst;
  }
  std::vector<std::pair<int, int> > a; // Массив, в который складываем левую часть lst
  int len_a = n / 2; // Кол-во элементов в левой части
  std::vector<std::pair<int, int> > b; // Массив, в который складываем правую часть lst
  int len_b = (n - n / 2); // Кол-во элементов в правой части
  for (int i = 0; i < n / 2; ++i) {
    a.push_back(lst[i]);
  }
  for (int i = n / 2; i < n; ++i) {
    b.push_back(lst[i]);
  }
  a = Merges(a); // Запускаем рекурсивную сортировку для левой части
  b = Merges(b); // Запускаем рекурсивную сортировку для правой части
  int p_a = 0; // Сливаем два отсортированных массива в один отсортированный массив
  int p_b = 0;
  std::vector<std::pair<int, int> > cd;
  while (p_a < len_a and p_b < len_b) {
    if (a[p_a].first < b[p_b].first or
        (a[p_a].first == b[p_b].first and a[p_a].second < b[p_b].second)) {
      cd.push_back(a[p_a]);
      ++p_a;
    } else {
      cd.push_back(b[p_b]);
      ++p_b;
    }
  }
  while (p_a < len_a) {
    cd.push_back(a[p_a]);
    ++p_a;
  }
  while (p_b < len_b) {
    cd.push_back(b[p_b]);
    ++p_b;
  }
  return cd; // возвращаем отсортированный массив
}

int main() {
  // ввод переменных согласно формату входных данных из задачи
  int n;
  std::cin >> n;
  int l;
  int r;
  std::vector<std::pair<int, int> > lst;
  std::pair<int, int> buf;
  for (int i = 0; i < n; ++i) {
    std::cin >> l >> r;
    buf.first = l;
    buf.second = -1;
    lst.push_back(buf);
    buf.first = r;
    buf.second = 1;
    lst.push_back(buf);
  }
  // сортировка массива lst с помощью сортировки merge_sort
  lst = Merges(lst);
  // решение задачи с помощью отсортированного массива lst
  int balance = 0;
  std::vector<std::pair<int, int> > ans;
  int rn = -1;
  int ln = -1;
  for (auto el : lst) {
    balance += el.second;
    if (balance == 0) {
      rn = el.first;
      buf.first = ln;
      buf.second = rn;
      ans.push_back(buf);
    } else if (balance == -1 and el.second == -1) {
      ln = el.first;
    }
  }
  // вывод ответа
  std::cout << ans.size() << '\n';
  for (auto el : ans) {
    std::cout << el.first << ' ' << el.second << '\n';
  }
}