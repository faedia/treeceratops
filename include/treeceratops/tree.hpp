#pragma once

#include <memory>
#include <optional>
#include <vector>

namespace treeceratops {

using nodeIdT_ = std::size_t;

template <class T> struct node_type_ {
  std::optional<nodeIdT_> parent;
  std::optional<nodeIdT_> prev;
  std::optional<nodeIdT_> next;
  T data;
  std::vector<nodeIdT_> children;
};

template <class T, class Allocator> class tree;

template <class T, class Allocator, class Ttree> class tree_iterator {

public:
  friend tree<T, Allocator>;
  template <class T1, class Allocator1, class Ttree1>
  friend class tree_iterator;

  tree_iterator(){};

  tree_iterator(Ttree *tree, nodeIdT_ node) : tree_{tree}, node_{node} {}

  T &operator*() { return tree_->data_[node_].data; }
  const T &operator*() const { return tree_->data_[node_].data; }
  T *operator->() { return &tree_->data_[node_].data; }
  const T *operator->() const { return &tree_->data_[node_].data; }

  tree_iterator operator[](std::size_t idx) {
    return {tree_, tree_->data_[node_].children[idx]};
  }

  tree_iterator &operator++() {
    if (!tree_->data_[node_].children.empty()) {
      node_ = tree_->data_[node_].children.front();
    } else {
      while (!tree_->data_[node_].next) {
        if (tree_->data_[node_].parent) {
          node_ = *tree_->data_[node_].parent;
        } else {
          tree_ = nullptr;
          node_ = 0;
          return *this;
        }
      }
      node_ = *tree_->data_[node_].next;
    }
    return *this;
  }

  tree_iterator operator++(int) {
    auto old = *this;
    this->operator++();
    return old;
  }

  template <class T1, class Allocator1, class Ttree1>
  auto operator!=(const tree_iterator<T1, Allocator1, Ttree1> &iter) const {
    return !(tree_ == iter.tree_ && node_ == iter.node_);
  }

  tree_iterator parent() {
    if (tree_->data_[node_].parent) {
      return tree_iterator{tree_, *tree_->data_[node_].parent};
    } else {
      return tree_iterator{};
    }
  }

  tree_iterator child(std::size_t idx) {
    return tree_iterator{tree_, *tree_->data_[node_].children[idx]};
  }

private:
  Ttree *tree_ = nullptr;
  nodeIdT_ node_ = 0;
};

template <class T, class Allocator = std::allocator<node_type_<T>>> class tree {
public:
  using node_type = node_type_<T>;
  using node_id = nodeIdT_;
  using iterator = tree_iterator<T, Allocator, tree<T, Allocator>>;
  using const_iterator =
      const tree_iterator<T, Allocator, const tree<T, Allocator>>;
  friend iterator;

  // Element Access
  T &at(node_id id) { return data_.at(id).data; }
  T &operator[](node_id id) { return data_[id].data; }

  // Iterators
  iterator begin() { return iterator{this, *root_}; }
  const_iterator begin() const { return const_iterator{this, *root_}; }
  iterator end() { return iterator{}; }
  const_iterator end() const { return const_iterator{}; }

  // Capacity
  bool empty() { return root_.has_value(); }
  std::size_t size();

  // Modifiers
  void clear() {
    data_.clear();
    root_ = std::nullopt;
  }

  void push_root(const T &value) {
    if (root_) {
      data_[*root_].parent = data_.size();
      data_.push_back({{}, {}, {}, value, {*root_}});
    } else {
      data_.push_back({{}, {}, {}, value, {}});
    }
    root_ = data_.size() - 1;
  }

  void push_child(const iterator &pos, const T &value) {
    node_id id = data_.size();
    if (!data_[pos.node_].children.empty()) {
      data_.push_back(
          {pos.node_, data_[pos.node_].children.back(), {}, value, {}});
      data_[data_[pos.node_].children.back()].next = id;
    } else {
      data_.push_back({pos.node_, {}, {}, value, {}});
    }
    data_[pos.node_].children.push_back(id);
  }

  iterator insert(const_iterator pos, const T &value);

  template <std::size_t Idx, class TIt> TIt child(const TIt &pos) {
    return child_inner<Idx, TIt>(TIt{this, data_[pos.node_].children[0]});
  }

  int depth(iterator pos) {
    assert(pos.tree_ = this);
    int d = 0;

    while (pos != begin()) {
      pos = pos.parent();
      ++d;
    }

    return d;
  }

private:
  template <std::size_t Idx, class TIt> TIt child_inner(const TIt &pos) {
    if constexpr (Idx == 0) {
      return pos;
    } else {
      return child_inner<Idx - 1, TIt>(TIt{this, *data_[pos.node_].next});
    }
  }

  std::vector<node_type, Allocator> data_;
  std::optional<nodeIdT_> root_;
};

} // namespace treeceratops