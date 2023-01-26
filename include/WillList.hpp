// Copyright 2017 William Jagels
#pragma once
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <memory>
#include <utility>

namespace wijagels {
namespace detail {
struct Node_Base {
  constexpr Node_Base() : Node_Base{this, this} {}
  constexpr Node_Base(Node_Base *prev, Node_Base *next)
      : d_prev_p{prev}, d_next_p{next} {}
  constexpr Node_Base(const Node_Base &other) = default;
  constexpr Node_Base(Node_Base &&other) noexcept
      : d_prev_p{other.d_prev_p}, d_next_p{other.d_next_p} {
    other.d_next_p = &other;
    other.d_prev_p = &other;
  }
  ~Node_Base() = default;
  constexpr Node_Base &operator=(const Node_Base &) = default;
  constexpr Node_Base &operator=(Node_Base &&other) noexcept {
    if (this != &other) {
      d_prev_p = other.d_prev_p;
      d_next_p = other.d_next_p;
      other.d_next_p = &other;
      other.d_prev_p = &other;
    }
    return *this;
  }

  Node_Base *d_prev_p, *d_next_p;
};

template <typename T>
struct Node : Node_Base {
  constexpr Node(Node *prev, Node *next, const T &data)
      : Node_Base{prev, next}, d_data{data} {}

  constexpr explicit Node(const T &data) : Node{this, this, data} {}

  constexpr Node(Node *prev, Node *next,
                 T &&data) noexcept(std::is_nothrow_move_constructible_v<T>)
      : Node_Base{prev, next}, d_data{std::move(data)} {}

  template <typename... Args>
  constexpr explicit Node(Args &&... args) noexcept(
      std::is_nothrow_constructible_v<Node, Node *, Node *, Args...>)
      : Node{this, this, std::forward<Args>(args)...} {}

  template <typename... Args>
  explicit Node(Node *prev, Node *next, Args &&... args) noexcept(
      std::is_nothrow_constructible_v<T, Args...>)
      : Node_Base{prev, next}, d_data{args...} {}

  constexpr T &operator*() { return d_data; }

  constexpr T *operator->() { return &d_data; }

  constexpr friend void swap(Node &lhs, Node &rhs) noexcept {
    std::swap(lhs.d_next_p, rhs.d_next_p);
    std::swap(lhs.d_prev_p, rhs.d_prev_p);
  }

  T d_data;
};
}  // namespace detail

template <typename T, class Allocator = std::allocator<T>>
class list {
  using Node_Base = detail::Node_Base;
  using Node = detail::Node<T>;

 public:
  class iterator;
  class const_iterator;
  using value_type = T;
  using allocator_type = Allocator;
  using node_allocator_type = typename std::allocator_traits<
      allocator_type>::template rebind_alloc<Node>;
  using node_alloc_traits = typename std::allocator_traits<node_allocator_type>;
  using size_type = size_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = typename std::allocator_traits<allocator_type>::pointer;
  using const_pointer =
      typename std::allocator_traits<allocator_type>::const_pointer;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

 public:
  class iterator {
   public:
    Node_Base *d_node_p;
    friend list;

   public:
    using value_type = T;
    using difference_type = size_t;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = typename std::allocator_traits<allocator_type>::pointer;
    using const_pointer =
        typename std::allocator_traits<allocator_type>::const_pointer;
    using iterator_category = std::bidirectional_iterator_tag;

    constexpr explicit iterator(Node_Base *node) : d_node_p{node} {}

    constexpr iterator &operator++() {
      d_node_p = d_node_p->d_next_p;
      return *this;
    }

    constexpr iterator operator++(int) {
      iterator ret = iterator{*this};
      d_node_p = d_node_p->d_next_p;
      return ret;
    }

    constexpr iterator &operator--() {
      d_node_p = d_node_p->d_prev_p;
      return *this;
    }

    constexpr iterator operator--(int) {
      iterator ret = iterator{*this};
      d_node_p = d_node_p->d_prev_p;
      return ret;
    }

    constexpr reference operator*() const {
      return static_cast<Node *>(d_node_p)->d_data;
    }

    constexpr pointer operator->() const {
      return &(static_cast<Node *>(d_node_p)->d_data);
    }

    constexpr friend bool operator==(const iterator &lhs, const iterator &rhs) {
      return lhs.d_node_p == rhs.d_node_p;
    }

    constexpr friend bool operator!=(const iterator &lhs, const iterator &rhs) {
      return lhs.d_node_p != rhs.d_node_p;
    }

    constexpr friend difference_type distance(const iterator &lhs,
                                              const iterator &rhs) {
      size_type d = 0;
      auto it = lhs;
      while (it++ != rhs) d++;
      return d;
    }
  };

  class const_iterator {
    const Node_Base *d_node_p;
    friend list;

   public:
    using value_type = T;
    using difference_type = size_t;
    using reference = const value_type &;
    using pointer = typename std::allocator_traits<Allocator>::const_pointer;
    using iterator_category = std::bidirectional_iterator_tag;

    constexpr explicit const_iterator(const Node_Base *node) : d_node_p{node} {}

    constexpr const_iterator(const iterator &other)
        : d_node_p{other.d_node_p} {}

    constexpr const_iterator &operator++() {
      d_node_p = d_node_p->d_next_p;
      return *this;
    }

    constexpr const_iterator operator++(int) {
      const_iterator ret = const_iterator{*this};
      d_node_p = d_node_p->d_next_p;
      return ret;
    }

    constexpr const_iterator &operator--() {
      d_node_p = d_node_p->d_prev_p;
      return *this;
    }

    constexpr const_iterator operator--(int) {
      const_iterator ret = const_iterator{*this};
      d_node_p = d_node_p->d_prev_p;
      return ret;
    }

    constexpr reference operator*() const {
      return static_cast<const Node *>(d_node_p)->d_data;
    }

    constexpr pointer operator->() const {
      return &(static_cast<const Node *>(d_node_p)->d_data);
    }

    constexpr friend bool operator==(const const_iterator &lhs,
                                     const const_iterator &rhs) {
      return lhs.d_node_p == rhs.d_node_p;
    }

    constexpr friend bool operator!=(const const_iterator &lhs,
                                     const const_iterator &rhs) {
      return lhs.d_node_p != rhs.d_node_p;
    }

    constexpr friend difference_type distance(const const_iterator &lhs,
                                              const const_iterator &rhs) {
      difference_type d = 0;
      auto it = lhs;
      while (it++ != rhs) d++;
      return d;
    }

   private:
    /**
     * Note that this is only used in the context of having a mutable reference
     * into the underlying container.
     */
    constexpr iterator un_const() {
      return iterator{const_cast<Node_Base *>(d_node_p)};  // NOLINT
    }
  };

 public:
  constexpr list() noexcept(noexcept(Allocator())) : list{Allocator()} {}

  constexpr explicit list(const Allocator &alloc) : d_alloc{alloc} {}

  list(size_type count, const T &value, const Allocator &alloc = Allocator())
      : d_alloc{alloc} {
    for (; count > 0; --count) push_back(value);
  }

  explicit list(size_type count, const Allocator &alloc = Allocator())
      : list{alloc} {
    for (; count > 0; --count) emplace_back();
  }

  template <class InputIt>
  list(InputIt first, InputIt last, const Allocator &alloc = Allocator())
      : list{alloc} {
    for (; first != last; ++first) {
      push_back(*first);
    }
  }

  list(const list &other)
      : d_alloc{std::allocator_traits<allocator_type>::
                    select_on_container_copy_construction(other.d_alloc)} {
    for (const_reference e : other) push_back(e);
  }

  list(const list &other, const Allocator &alloc) : list{alloc} {
    for (const_reference e : other) push_back(e);
  }

  list(size_type count, const_reference value) : list{} {
    while (count--) {
      push_back(value);
    }
  }

  list(list &&other) noexcept(std::is_nothrow_move_constructible_v<Allocator>)
      : d_alloc{std::move(other.d_alloc)},
        d_node_alloc{std::move(other.d_alloc)} {
    splice(cend(), std::move(other));
  }

  list(std::initializer_list<T> init, const Allocator &alloc = Allocator())
      : d_alloc{alloc} {
    for (auto &e : init) {
      emplace_back(e);
    }
  }

  ~list() { clear(); }

  list &operator=(const list &other) {
    if (this == &other) return *this;
    clear();
    if (std::allocator_traits<
            allocator_type>::propagate_on_container_copy_assignment::value) {
      d_alloc = other.d_alloc;
    }
    for (auto e : other) {
      push_back(e);
    }
    return *this;
  }

  list &operator=(list &&other) noexcept(
      std::allocator_traits<allocator_type>::is_always_equal::value
          &&std::is_nothrow_move_assignable_v<allocator_type> &&
      (!std::allocator_traits<
           allocator_type>::propagate_on_container_move_assignment::value ||
       std::is_nothrow_move_assignable_v<value_type>)) {
    if (this == &other) return *this;
    clear();
    if constexpr (std::allocator_traits<allocator_type>::
                      propagate_on_container_move_assignment::value) {
      d_alloc = std::move(other.d_alloc);
      splice(cend(), std::move(other));
    } else {
      for (auto &e : other) {
        emplace_back(std::move(e));
      }
      other.clear();
    }
    return *this;
  }

  list &operator=(std::initializer_list<T> ilist) {
    for (auto e : ilist) {
      push_back(e);
    }
    return *this;
  }

  void assign(size_type count, const T &value) {
    clear();
    for (; count > 0; --count) {
      push_back(value);
    }
  }

  template <class InputIt>
  void assign(InputIt first, InputIt last) {
    clear();
    for (; first != last; ++first) {
      push_back(*first);
    }
  }

  void assign(std::initializer_list<T> ilist) {
    clear();
    for (const auto &e : ilist) {
      push_back(e);
    }
  }

  allocator_type get_allocator() { return d_alloc; }

  /* Element access */

  reference front() { return *(begin()); }
  const_reference front() const { return *(begin()); }

  reference back() { return *(--end()); }
  const_reference back() const { return *(--end()); }

  /* Iterators */

  iterator begin() noexcept { return iterator{d_head.d_next_p}; }
  iterator end() noexcept { return iterator{&d_head}; }

  const_iterator begin() const noexcept {
    return const_iterator{d_head.d_next_p};
  }
  const_iterator end() const noexcept { return const_iterator{&d_head}; }

  const_iterator cbegin() const noexcept {
    return const_iterator{d_head.d_next_p};
  }
  const_iterator cend() const noexcept { return const_iterator{&d_head}; }

  reverse_iterator rbegin() noexcept { return reverse_iterator{end()}; }
  reverse_iterator rend() noexcept { return reverse_iterator{begin()}; }

  const_reverse_iterator rbegin() const noexcept { return crbegin(); }
  const_reverse_iterator rend() const noexcept { return crend(); }

  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator{cend()};
  }
  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator{cbegin()};
  }

  /* Capacity */

  constexpr bool empty() const noexcept { return cbegin() == cend(); }

  size_type size() const noexcept { return std::distance(begin(), end()); }

  constexpr size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max();
  }

  /* Modifiers */

  void clear() noexcept {
    while (begin() != end()) erase(begin());
  }

 private:
  static constexpr void link_(Node_Base *first, Node_Base *last) {
    first->d_next_p = last;
    last->d_prev_p = first;
  }

  template <typename... Args>
  static constexpr void link_(Node_Base *first, Node_Base *second,
                              Args... rest) {
    link_(first, second);
    link_(second, rest...);
  }

 public:
  iterator insert(const iterator &pos, const_reference data) {
    Node *node = node_alloc_traits::allocate(d_node_alloc, 1);
    node_alloc_traits::construct(d_node_alloc, node, data);
    link_(pos.d_node_p->d_prev_p, node, pos.d_node_p);
    return iterator{node};
  }

  template <class... Args>
  iterator emplace(const iterator &pos, Args &&... args) {
    Node *node = node_alloc_traits::allocate(d_node_alloc, 1);
    node_alloc_traits::construct(d_node_alloc, node,
                                 std::forward<Args>(args)...);
    link_(pos.d_node_p->d_prev_p, node, pos.d_node_p);
    return iterator{node};
  }

  void erase(const iterator &iter) {
    link_(iter.d_node_p->d_prev_p, iter.d_node_p->d_next_p);
    node_alloc_traits::destroy(d_node_alloc, iter.d_node_p);
    node_alloc_traits::deallocate(d_node_alloc,
                                  static_cast<Node *>(iter.d_node_p), 1);
  }

  void push_back(const_reference data) { insert(end(), data); }

  template <class... Args>
  reference emplace_back(Args &&... args) {
    return *emplace(end(), std::forward<Args>(args)...);
  }

  void pop_back() { erase(--end()); }

  void push_front(const_reference data) { insert(begin(), data); }

  template <class... Args>
  reference emplace_front(Args &&... args) {
    return *emplace(begin(), std::forward<Args>(args)...);
  }

  void pop_front() { erase(begin()); }

  void resize(size_type count) { resize(count, value_type{}); }

  void resize(size_type count, const value_type &value) {
    size_type sz = size();
    if (sz == count) {
      return;
    } else if (sz < count) {
      while (sz++ < count) {
        push_back(value);
      }
    } else {  // sz > count
      sz -= count;
      while (sz--) pop_back();
    }
  }

  void swap(list &other) noexcept {
    if constexpr (std::allocator_traits<
                      allocator_type>::propagate_on_container_swap::value) {
      std::swap(d_alloc, other.d_alloc);
    }
    if constexpr (node_alloc_traits::propagate_on_container_swap::value) {
      std::swap(d_node_alloc, other.d_node_alloc);
    }
    std::swap(d_head, other.d_head);
  }

  /* Operations */

  void merge(list &other) { merge(std::move(other)); }

  void merge(list &&other) {
    merge(std::move(other),
          [](const_reference lhs, const_reference rhs) { return lhs < rhs; });
  }

  template <class Compare>
  void merge(list &other, Compare comp) {
    merge(std::move(other), comp);
  }

  template <class Compare>
  void merge(list &&other, Compare comp) {
    // make sure we aren't merging with self
    if (this == &other) return;

    auto lhs = begin();
    auto rhs = other.begin();

    for (; rhs != other.end() && lhs != end(); ++lhs) {
      if (comp(*rhs, *lhs)) {
        // node.prev <-> node.next
        // lhs.prev <-> rhs <-> lhs <-> lhs.next
        auto node = rhs.d_node_p;
        ++rhs;
        link_(node->d_prev_p, node->d_next_p);
        link_(lhs.d_node_p->d_prev_p, node, lhs.d_node_p);
        lhs.d_node_p = node;
      }
    }
    // Appends remainder if we didn't reach the end
    if (rhs != other.end()) splice(cend(), other);
  }

  void splice(const_iterator pos, list &other) {
    splice(pos, std::move(other));
  }

  void splice(const_iterator pos, list &&other) {
    splice(pos, std::move(other), other.cbegin(), other.cend());
  }

  void splice(const_iterator pos, list &other, const_iterator it) {
    splice(pos, std::move(other), it);
  }

  void splice(const_iterator pos, list &&other, const_iterator it) {
    splice(pos, std::move(other), it, other.cend());
  }

  void splice(const_iterator pos, list &other, const_iterator first,
              const_iterator last) {
    splice(pos, std::move(other), first, last);
  }

  /*
   * Other rvalue ignored, we just need access to iterators.
   * Head and tail pointer of other don't aren't a special case because of
   * how the sentinel node works.
   * Using this on iterators from a different list is undefined,
   * and will violate const-ness.
   */
  void splice(const_iterator pos, list &&, const_iterator first,
              const_iterator last) {
    iterator ipos = pos.un_const();
    iterator ifirst = first.un_const();
    iterator ilast = last.un_const();

    auto final_node = ilast.d_node_p->d_prev_p;
    // Fix pointers in other
    link_(ifirst.d_node_p->d_prev_p, ilast.d_node_p);

    link_(ipos.d_node_p->d_prev_p, ifirst.d_node_p);
    link_(final_node, ipos.d_node_p);
  }

  void remove(const T &value) {
    remove_if([&value](const_reference operand) { return operand == value; });
  }

  template <class UnaryPredicate>
  void remove_if(UnaryPredicate p) {
    for (iterator it = begin(); it != end(); ++it)
      if (p(*it)) erase(it--);
    // --begin() results in end(), ++end() results in begin()
  }

  void reverse() noexcept {
    iterator it = end();
    do {
      std::swap(it.d_node_p->d_prev_p, it.d_node_p->d_next_p);
    } while (++it != end());
  }

  void unique() {
    unique([](const_reference lhs, const_reference rhs) { return lhs == rhs; });
  }

  template <class BinaryPredicate>
  void unique(BinaryPredicate p) {
    if (empty()) return;
    auto current = *begin();
    for (iterator it = ++begin(); it != end(); ++it) {
      if (p(current, *it))
        erase(it--);
      else
        current = *it;
    }
  }

  void sort() {
    sort([](const_reference lhs, const_reference rhs) { return lhs < rhs; });
  }

  template <class Compare>
  void sort(Compare comp) {
    if (empty() || ++begin() == end()) return;
    auto tortise = cbegin();
    auto hare = cbegin();
    while (hare != cend() && ++hare != cend()) {
      ++tortise;
      ++hare;
    }
    list left, right;
    left.splice(left.cend(), *this, cbegin(), tortise);
    right.splice(right.cend(), *this);
    left.sort(comp);
    right.sort(comp);
    left.merge(right, comp);
    splice(cend(), left);
  }

  /* Friend functions */

  /*
   * Allows for argument-dependent lookup with std::swap
   */
  friend void swap(list &lhs, list &rhs) noexcept { lhs.swap(rhs); }

  friend bool operator==(const list &lhs, const list &rhs) {
    auto lit = lhs.begin();
    auto rit = rhs.begin();
    for (; lit != lhs.end() && rit != rhs.end(); ++lit, ++rit) {
      if (!(*lit == *rit)) return false;
    }
    return lit == lhs.end() && rit == rhs.end();
  }

  friend bool operator!=(const list &lhs, const list &rhs) {
    return !(lhs == rhs);
  }

  friend bool operator<(const list &lhs, const list &rhs) {
    auto lit = lhs.begin();
    auto rit = rhs.begin();
    for (; lit != lhs.end() && rit != rhs.end(); ++lit, ++rit) {
      if (*lit < *rit) return true;
      if (*rit < *lit) return false;
    }
    return lit == lhs.end() && rit != rhs.end();
  }

  friend bool operator<=(const list &lhs, const list &rhs) {
    auto lit = lhs.begin();
    auto rit = rhs.begin();
    for (; lit != lhs.end() && rit != rhs.end(); ++lit, ++rit) {
      if (*lit < *rit) return true;
      if (*rit < *lit) return false;
    }
    return lit == lhs.end();
  }

  friend bool operator>(const list &lhs, const list &rhs) { return rhs < lhs; }

  friend bool operator>=(const list &lhs, const list &rhs) {
    return rhs <= lhs;
  }

#ifdef LIST_DBG_ON
  bool verify_integrity() {
    for (iterator it = begin(); it != end(); it++) {
      if (it.d_node_p != it.d_node_p->d_prev_p->d_next_p ||
          it.d_node_p != it.d_node_p->d_next_p->d_prev_p)
        return false;
    }
    return true;
  }
#endif

#ifdef LIST_DBG_ON

 public:
#else

 private:
#endif
  Node_Base d_head;
  allocator_type d_alloc;
  node_allocator_type d_node_alloc;
};

/*
#if __cplusplus > 201402L
namespace pmr {
template <class T>
using list = list<T, std::pmr::polymorphic_allocator<T>>;
}
#endif  // __cplusplus > 201402L
*/
}  // namespace wijagels
