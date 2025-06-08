// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <utility>
#include <memory>
#include <algorithm>
#include <vector>
#include  "tree.h"
void PMTree::buildTree(Node* parent, const vector<char>& remaining) {
  for (size_t i = 0; i < remaining.size(); ++i) {
    auto newNode = make_unique<Node>();
    newNode->value = remaining[i];
    std::vector<char> newRemaining;
    for (size_t j = 0; j < remaining.size(); ++j) {
      if (j != i) newRemaining.push_back(remaining[j]);
    }
    buildTree(newNode.get(), newRemaining);
    parent->children.push_back(move(newNode));
  }
}

PMTree::PMTree(const vector<char>& input) : elem(input) {
  sort(elem.begin(), elem.end());
  root = make_unique<Node>();
  buildTree(root.get(), elem);
}

int PMTree::factorial(int n) const {
  int res = 1;
  for (int i = 2; i <= n; ++i) res *= i;
  return res;
}

int PMTree::countPermutations() const {
  return factorial(elem.size());
}

vector<vector<char>> PMTree::getAllPerms() const {
  vector<vector<char>> res;
  if (!root) return res;
  std::vector<pair<Node*, vector<char>>> stack;
  stack.push_back({ root.get(), {} });
  while (!stack.empty()) {
    auto [node, current] = stack.back();
    stack.pop_back();
    current.push_back(node->value);
    if (node->children.empty()) {
      res.push_back(current);
    } else {
      for (auto it = node->children.rbegin();
        it != node->children.rend(); ++it) {
        stack.push_back({ it->get(), current });
      }
    }
  }
  return res;
}

vector<vector<char>> getAllPerms(const PMTree& tree) {
  return tree.getAllPerms();
}

vector<char> getPerm1(PMTree& tree, int num) {
  auto all = getAllPerms(tree);
  if (num < 1 || num > all.size()) return {};
  return all[num - 1];
}

vector<char> getPerm2(PMTree& tree, int num) {
  const auto& elem = tree.getelem();
  int total = tree.countPermutations();
  if (num < 1 || num > total) return {};
  std::vector<char> res;
  std::vector<char> remaining = elem;
  int currentNum = num - 1;
  for (int n = elem.size(); n > 0; --n) {
    int fact = 1;
    for (int i = 1; i < n; ++i) fact *= i;
    int index = currentNum / fact;
    if (index >= remaining.size()) return {};
    res.push_back(remaining[index]);
    remaining.erase(remaining.begin() + index);
    currentNum %= fact;
  }
  return res;
}
