// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include "tree.h"

double getCurrentTime() {
  return static_cast<double>(std::clock()) / CLOCKS_PER_SEC * 1000;
}

int main() {
  std::srand(std::time(0));
  std::vector<int> sizes = { 1, 2, 3, 4, 5, 6, 7, 8 };
  std::cout << std::fixed << std::setprecision(3);
  std::cout << "elem\tAllPerms(ms)\tGetPerm1(ms)\tGetPerm2(ms)\n";
  for (int n : sizes) {
    std::vector<char> in;
    for (int i = 0; i < n; ++i) {
      in.push_back('A' + i);
    }
    PMTree tree(in);
    int totalPerms = tree.countPermutations();
    double startAll = getCurrentTime();
    auto all = getAllPerms(tree);
    double timeAll = getCurrentTime() - startAll;
    double start1 = getCurrentTime();
    for (int i = 0; i < 10; ++i) {
      int randomPerm = 1 + (std::rand() % totalPerms);
      auto perm1 = getPerm1(tree, randomPerm);
    }
    double time1 = (getCurrentTime() - start1) / 10;
    double start2 = getCurrentTime();
    for (int i = 0; i < 10; ++i) {
      int randomPerm = 1 + (std::rand() % totalPerms);
      auto perm2 = getPerm2(tree, randomPerm);
    }
    double time2 = (getCurrentTime() - start2) / 10;
    std::cout << n << "\t"
      << timeAll << "\t"
      << std::max(time1, 0.001) << "\t"
      << std::max(time2, 0.001) << "\n";
  }
  std::vector<char> tr = { '1', '2', '3' };
  PMTree tree(tr);
  auto intPerms = getAllPerms(tree);
  std::cout << "\nInteger permutations:\n";
  for (const auto& perm : intPerms) {
    for (char c : perm) std::cout << c;
    std::cout << "\n";
  }
  return 0;
}
