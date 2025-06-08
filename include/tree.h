// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <memory>
class PMTree {
 public:
  struct Node {
    char value;
    std::vector<std::unique_ptr<Node>> children;
  };

 private:
  std::unique_ptr<Node> root;
  std::vector<char> elements;
  void buildTree(Node* parent, const std::vector<char>& remaining);
  int factorial(int n) const;

 public:
  explicit PMTree(const std::vector<char>& input);
  const std::vector<char>& getElements() const { return elements; }
  std::vector<std::vector<char>> getAllPerms() const;
  int countPermutations() const;
};
std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);
#endif  // INCLUDE_TREE_H_
