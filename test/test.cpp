#include <gtest/gtest.h>

#include <treeceratops/tree.hpp>

TEST(test, test)
{
    treeceratops::tree<int> t;

    t.push_root(1);
    std::cout << "root 1\n";
    for (auto item : t)
    {
        std::cout << item << '\n';
    }

    t.push_child(t.begin(), 10);
    std::cout << "child 10\n";
    for (auto item : t)
    {
        std::cout << item << '\n';
    }

    t.push_root(2);
    std::cout << "root 2\n";
    for (auto item : t)
    {
        std::cout << item << '\n';
    }

    t.push_child(t.begin(), 100);
    std::cout << "child 100\n";
    for (auto iter = t.begin(); iter != t.end(); ++iter)
    {
        std::cout << "Depth " << t.depth(iter) << ' ' << *iter << '\n';
    }

    std::cout << *(t.child<0>(t.begin())) << '\n';
    std::cout << *(t.child<1>(t.begin())) << '\n';

    treeceratops::tree<std::string> t2;
    t2.push_root("Hello, world");
    for (auto iter = t2.begin(); iter != t2.end(); ++iter)
    {
        std::cout << "Item " << *iter << '\n';
    }
}

TEST(TreeTest, make_parent)
{

    treeceratops::tree<int> t;
    t.push_root(1);
    auto root = t.begin();
    t.push_child(root, 2);
    t.push_child(root, 3);
    auto node3 = t.child<1>(root);
    t.push_child(node3, 4);

    for (auto iter = root; iter != t.end(); ++iter)
    {
        auto d = t.depth(iter);
        for (int d = t.depth(iter); d > 0; d--)
        {
            std::cout << ' ';
        }
        std::cout << *iter << '\n';
    }

    t.make_parent(t.child<0>(root), t.child<0>(node3));

    for (auto iter = root; iter != t.end(); ++iter)
    {
        auto d = t.depth(iter);
        for (int d = t.depth(iter); d > 0; d--)
        {
            std::cout << ' ';
        }
        std::cout << *iter << '\n';
    }
}
