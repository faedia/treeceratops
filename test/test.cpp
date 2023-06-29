#include <gtest/gtest.h>

#include <treeceratops/tree.hpp>

TEST(test, test) {
  treeceratops::tree<int> t;

  t.push_root(1);
  std::cout << "root 1\n";
  for (auto item : t) {
    std::cout << item << '\n';
  }

  t.push_child(t.begin(), 10);
  std::cout << "child 10\n";
  for (auto item : t) {
    std::cout << item << '\n';
  }

  t.push_root(2);
  std::cout << "root 2\n";
  for (auto item : t) {
    std::cout << item << '\n';
  }

  t.push_child(t.begin(), 100);
  std::cout << "child 100\n";
  for (auto iter = t.begin(); iter != t.end(); ++iter) {
    std::cout << "Depth " << t.depth(iter) << ' ' << *iter << '\n';
  }

  std::cout << *(t.child<0>(t.begin())) << '\n';
  std::cout << *(t.child<1>(t.begin())) << '\n';

  treeceratops::tree<std::string> t2;
  t2.push_root("Hello, world");
  for (auto iter = t2.begin(); iter != t2.end(); ++iter) {
    std::cout << "Item " << *iter << '\n';
  }
}
