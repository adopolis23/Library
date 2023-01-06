#pragma once
#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <stdexcept>

namespace wijangles {
    static constexpr std::size_t g_growth_factor = 2;
    template <class T, class Allocator = std::allocator<T>>
    class vector {
    public:
        using value_type = T;
        using allocator_type = Allocator;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = typename std::allocator_traits<Allocator>::pointer;
        using const_pointer =
            typename std::allocator_traits<Allocator>::const_pointer;

        class const_iterator;
        class iterator {
        public:
            using value_type = T;
            using size_type = std::size_t;
            using difference_type = std::ptrdiff_t;
            using reference = value_type&;
            using pointer = value_type*;
            using iterator_category = std::random_access_iterator_tag;

            constexpr explicit iterator(pointer ptr) : d_data_p{ ptr } {}

            constexpr iterator& operator++() {
                ++d_data_p;
                return *this;
            }

            constexpr iterator operator++(int) {
                iterator ret = iterator{ *this };
                ++d_data_p;
                return ret;
            }

            constexpr iterator& operator+=(difference_type n) {
                d_data_p += n;
                return *this;
            }

            constexpr iterator& operator--() {
                --d_data_p;
                return *this;
            }

            constexpr iterator operator--(int) {
                iterator ret = iterator{ *this };
                --d_data_p;
                return ret;
            }

            constexpr iterator& operator-=(difference_type n) {
                d_data_p -= n;
                return *this;
            }

            constexpr reference operator*() const { return *d_data_p; }

            constexpr pointer operator->() const { return d_data_p; }

            constexpr reference operator[](difference_type n) const {
                return *(d_data_p + n);
            }

            constexpr friend inline bool operator==(const iterator& lhs,
                const iterator& rhs) {
                return lhs.d_data_p == rhs.d_data_p;
            }

            constexpr friend inline bool operator!=(const iterator& lhs,
                const iterator& rhs) {
                return !(lhs == rhs);
            }

            constexpr friend inline bool operator<(const iterator& lhs,
                const iterator& rhs) {
                return lhs.d_data_p < rhs.d_data_p;
            }

            constexpr friend inline bool operator>(const iterator& lhs,
                const iterator& rhs) {
                return rhs < lhs;
            }

            constexpr friend inline bool operator<=(const iterator& lhs,
                const iterator& rhs) {
                return !(lhs > rhs);
            }

            constexpr friend inline bool operator>=(const iterator& lhs,
                const iterator& rhs) {
                return !(lhs < rhs);
            }

            constexpr friend inline difference_type distance(const iterator& lhs,
                const iterator& rhs) {
                return lhs.d_data_p - rhs.d_data_p;
            }

            constexpr friend inline iterator operator+(const iterator& lhs,
                difference_type n) {
                return iterator{ lhs.d_data_p + n };
            }

            constexpr friend inline iterator operator+(difference_type n,
                const iterator& rhs) {
                return rhs + n;
            }

            constexpr friend inline difference_type operator-(const iterator& lhs,
                const iterator& rhs) {
                return distance(lhs, rhs);
            }

            constexpr friend inline iterator operator-(difference_type n,
                const iterator& rhs) {
                return iterator{ n - rhs.d_data_p };
            }

            constexpr friend inline iterator operator-(const iterator& lhs,
                difference_type n) {
                return iterator{ lhs.d_data_p - n };
            }

        private:
            pointer d_data_p;
            friend const_iterator;
        };

        class const_iterator {
        public:
            using value_type = const T;
            using size_type = std::size_t;
            using difference_type = std::ptrdiff_t;
            using reference = value_type&;
            using pointer = value_type*;
            using iterator_category = std::random_access_iterator_tag;

            constexpr explicit const_iterator(pointer ptr) : d_data_p{ ptr } {}
            constexpr const_iterator(const iterator& iter)
                : const_iterator{ iter.d_data_p } {}

            constexpr const_iterator& operator++() {
                ++d_data_p;
                return *this;
            }

            constexpr const_iterator operator++(int) {
                const_iterator ret = const_iterator{ *this };
                ++d_data_p;
                return ret;
            }

            constexpr const_iterator& operator+=(difference_type n) {
                d_data_p += n;
                return *this;
            }

            constexpr const_iterator& operator--() {
                --d_data_p;
                return *this;
            }

            constexpr const_iterator operator--(int) {
                const_iterator ret = const_iterator{ *this };
                --d_data_p;
                return ret;
            }

            constexpr const_iterator& operator-=(difference_type n) {
                d_data_p -= n;
                return *this;
            }

            constexpr reference operator*() const { return *d_data_p; }

            constexpr pointer operator->() const { return d_data_p; }

            constexpr reference operator[](difference_type n) const {
                return *(d_data_p + n);
            }

            constexpr friend inline bool operator==(const const_iterator& lhs,
                const const_iterator& rhs) {
                return lhs.d_data_p == rhs.d_data_p;
            }

            constexpr friend inline bool operator!=(const const_iterator& lhs,
                const const_iterator& rhs) {
                return !(lhs == rhs);
            }

            constexpr friend inline bool operator<(const const_iterator& lhs,
                const const_iterator& rhs) {
                return lhs.d_data_p < rhs.d_data_p;
            }

            constexpr friend inline bool operator>(const const_iterator& lhs,
                const const_iterator& rhs) {
                return rhs < lhs;
            }

            constexpr friend inline bool operator<=(const const_iterator& lhs,
                const const_iterator& rhs) {
                return !(lhs > rhs);
            }

            constexpr friend inline bool operator>=(const const_iterator& lhs,
                const const_iterator& rhs) {
                return !(lhs < rhs);
            }

            constexpr friend inline difference_type distance(
                const const_iterator& lhs, const const_iterator& rhs) {
                return lhs.d_data_p - rhs.d_data_p;
            }

            constexpr friend inline const_iterator operator+(const const_iterator& lhs,
                difference_type n) {
                return const_iterator{ lhs.d_data_p + n };
            }

            constexpr friend inline const_iterator operator+(
                difference_type n, const const_iterator& rhs) {
                return rhs + n;
            }

            constexpr friend inline difference_type operator-(
                const const_iterator& lhs, const const_iterator& rhs) {
                return distance(lhs, rhs);
            }

            constexpr friend inline const_iterator operator-(
                difference_type n, const const_iterator& rhs) {
                return const_iterator{ n - rhs.d_data_p };
            }

            constexpr friend inline const_iterator operator-(const const_iterator& lhs,
                difference_type n) {
                return const_iterator{ lhs.d_data_p - n };
            }

        private:
            pointer d_data_p;
            friend vector;
        };

    private:
        /* Internals */
        using alloc_traits = std::allocator_traits<allocator_type>;
        void grow_() {
            if (size() >= max_size()) {
                throw std::length_error(
                    "wijagels::vector reached allocator max size while trying to grow");
            }
            size_type new_size = std::max(1, (int)(capacity() * g_growth_factor));
            //size_type new_size = capacity() * g_growth_factor;
            if (new_size < capacity()) {
                // If this happens you have some serious issues.
                throw std::overflow_error("wijagels::vector is unable to grow");
            }
            new_size = std::min(new_size, max_size());
            change_capacity_(new_size);
        }

        /*
         * Round up to the nearest valid array size,
         * g_growth_factor^x where x is an integer
         */
        static constexpr size_type nearest_increment_(size_type n) {
            return 
                static_cast<size_type>(std::ceil(std::pow(
                    g_growth_factor,
                    std::ceil(std::log(n) / std::log(g_growth_factor)))));
        }

        void change_capacity_(size_type new_capacity) {
            new_capacity = nearest_increment_(new_capacity);
            if (new_capacity > max_size()) {
                throw std::length_error(
                    "wijagels::vector reached allocator max size while trying to grow");
            }
            pointer new_buf = alloc_traits::allocate(d_allocator, new_capacity);
            if (d_buffer_p) {
                if constexpr (std::is_trivially_copyable_v<value_type>) {
                    std::uninitialized_copy(d_buffer_p, d_buffer_p + size(), new_buf);
                }
                else {
                    for (size_type i = 0; i < size(); ++i) {
                        alloc_traits::construct(d_allocator, &new_buf[i],
                            std::move_if_noexcept(d_buffer_p[i]));
                    }
                }
                destroy_all_();
                alloc_traits::deallocate(d_allocator, d_buffer_p, capacity());
            }
            d_buffer_p = new_buf;
            d_buffer_capacity = new_capacity;
        }

        /*
         * Faster version of change_capacity_() that discards the existing values
         */
        void change_capacity_nocopy_(size_type new_capacity) {
            new_capacity = nearest_increment_(new_capacity);
            if (new_capacity > max_size()) {
                throw std::length_error(
                    "wijagels::vector reached allocator max size while trying to grow");
            }
            if (d_buffer_p) {
                clear();
                alloc_traits::deallocate(d_allocator, d_buffer_p, capacity());
            }
            pointer new_buf = alloc_traits::allocate(d_allocator, new_capacity);
            d_buffer_p = new_buf;
            d_buffer_capacity = new_capacity;
            d_size = 0;
        }

        /*
         * Utility to destroy every element in the current buffer
         */
        void destroy_all_() noexcept {
            if constexpr (!std::is_trivially_destructible_v<value_type>) {
                for (size_type i = 0; i < size(); ++i) {
                    destroy_one_(&d_buffer_p[i]);
                }
            }
        }

        void destroy_one_(pointer ptr) noexcept {
            if constexpr (!std::is_trivially_destructible_v<value_type>) {
                alloc_traits::destroy(d_allocator, ptr);
            }
        }

        void clear_and_dealloc_() {
            clear();
            if (d_buffer_p) {
                alloc_traits::deallocate(d_allocator, d_buffer_p, capacity());
                d_buffer_p = nullptr;
                d_buffer_capacity = 0;
            }
        }

        void shift_after_by_(const iterator& pos, size_t n) {
            if (n < 1) throw std::invalid_argument{ "Invalid shift size" };
            const auto end_iter = end();
            const auto shift_end = pos + static_cast<difference_type>(n - 1);
            auto input = end_iter - 1;
            auto destination = end_iter + static_cast<difference_type>(n - 1);
            while (destination > shift_end) {
                if (destination < end_iter) {
                    *destination = std::move_if_noexcept(*input);
                }
                else {
                    alloc_traits::construct(d_allocator, &*destination,
                        std::move_if_noexcept(*input));
                }
                --input;
                --destination;
            }
            d_size += n;
        }

    public:
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        /* Constructors */
        vector() noexcept(noexcept(Allocator())) : vector{ Allocator{} } {}

        explicit vector(const Allocator& alloc) noexcept : d_allocator{ alloc } {}

        vector(size_type count, const T& value, const Allocator& alloc = Allocator{})
            : vector{ alloc } {
            change_capacity_(count);
            for (size_type i = 0; i < count; i++) {
                d_buffer_p[i] = value;
            }
        }

        explicit vector(size_type count, const Allocator& alloc = Allocator{})
            : vector{ count, T{}, alloc } {}

        template <class InputIt>
        vector(InputIt first, InputIt last, const Allocator& alloc = Allocator{})
            : vector{ alloc } {
            while (first != last) {
                push_back(*first);
                ++first;
            }
        }

        vector(const vector& other)
            : vector{ other, alloc_traits::select_on_container_copy_construction(
                                other.get_allocator()) } {}

        vector(const vector& other, const Allocator& alloc) : vector{ alloc } {
            d_size = other.size();
            change_capacity_(other.size());
            for (size_type i = 0; i < other.size(); i++) {
                alloc_traits::construct(d_allocator, &d_buffer_p[i], other.d_buffer_p[i]);
            }
        }

        vector(vector&& other) noexcept
            : vector{ std::move(other),
                     alloc_traits::select_on_container_copy_construction(
                         other.get_allocator()) } {}

        vector(vector&& other, const Allocator& alloc) : vector{ alloc } {
            if (alloc != other.get_allocator()) {
                /* This path should be avoided */
                change_capacity_(other.size());
                for (size_type i = 0; i < other.size(); i++) {
                    alloc_traits::construct(d_allocator, &d_buffer_p[i],
                        std::move_if_noexcept(other.d_buffer_p[i]));
                }
                d_size = other.size();
            }
            else {
                d_buffer_p = std::move(other.d_buffer_p);
                other.d_buffer_p = nullptr;
                d_size = other.d_size;
                other.d_size = 0;
                d_buffer_capacity = other.d_buffer_capacity;
                other.d_buffer_capacity = 0;
            }
        }

        vector(std::initializer_list<T> init, const Allocator& alloc = Allocator{})
            : vector{ alloc } {
            d_size = init.size();
            change_capacity_(init.size());
            size_type i = 0;
            for (auto it = init.begin(); it != init.end(); ++i, ++it) {
                alloc_traits::construct(d_allocator, &d_buffer_p[i],
                    std::move_if_noexcept(*it));
            }
        }

        /* Destructor */
        ~vector() { clear_and_dealloc_(); }

        /* Assignment */
        vector& operator=(const vector& x) {
            if (&x == this) return *this;
            clear_and_dealloc_();
            if constexpr (alloc_traits::propagate_on_container_move_assignment::value) {
                d_allocator = x.d_allocator;
            }
            change_capacity_(x.size());
            d_size = x.d_size;
            for (size_type i = 0; i < x.size(); ++i) {
                alloc_traits::construct(d_allocator, &d_buffer_p[i], x[i]);
            }
            return *this;
        }

        vector& operator=(vector&& x) noexcept(
            std::allocator_traits<
            Allocator>::propagate_on_container_move_assignment::value ||
            std::allocator_traits<Allocator>::is_always_equal::value) {
            clear();
            alloc_traits::deallocate(d_allocator, d_buffer_p, d_buffer_capacity);
            if constexpr (alloc_traits::propagate_on_container_move_assignment::value) {
                d_allocator = x.d_allocator;
                d_buffer_p = x.d_buffer_p;
                d_size = x.d_size;
                d_buffer_capacity = x.d_buffer_capacity;
            }
            else if (d_allocator == x.d_allocator) {
                d_buffer_p = x.d_buffer_p;
                d_size = x.d_size;
                d_buffer_capacity = x.d_buffer_capacity;
            }
            else { /* Need to move individually, slow route */
                change_capacity_(x.size());
                d_size = x.size();
                for (size_type i = 0; i < x.size(); ++i) {
                    alloc_traits::construct(d_allocator, &d_buffer_p[i],
                        std::move_if_noexcept(x[i]));
                }
                x.clear_and_dealloc_();
            }
            /* Clear the properties of x */
            x.d_buffer_p = nullptr;
            x.d_size = 0;
            x.d_buffer_capacity = 0;
            return *this;
        }

        vector& operator=(std::initializer_list<T> init) {
            assign(init);
            return *this;
        }

        template <class InputIterator>
        void assign(InputIterator first, InputIterator last) {
            clear();
            for (; first != last; ++first) {
                emplace_back(std::forward<decltype(*first)>(*first));
            }
        }

        void assign(size_type n, const T& u) {
            change_capacity_nocopy_(n);
            for (size_type i = 0; i < n; i++) {
                alloc_traits::construct(d_allocator, &d_buffer_p[i], u);
            }
        }

        void assign(std::initializer_list<T> init) {
            change_capacity_nocopy_(init.size());
            size_t i = 0;
            for (auto&& el : init) {
                alloc_traits::construct(d_allocator, &d_buffer_p[i],
                    std::move_if_noexcept(el));
                ++i;
            }
            d_size = init.size();
        }

        allocator_type get_allocator() const noexcept { return d_allocator; }

        /* Iterators */
        iterator begin() noexcept { return iterator{ d_buffer_p }; }

        iterator end() noexcept { return iterator{ &d_buffer_p[size()] }; }

        const_iterator begin() const noexcept { return cbegin(); }

        const_iterator end() const noexcept { return cend(); }

        const_iterator cbegin() const noexcept { return const_iterator{ d_buffer_p }; }

        const_iterator cend() const noexcept {
            return const_iterator{ &d_buffer_p[size()] };
        }

        reverse_iterator rbegin() noexcept { return reverse_iterator{ d_buffer_p }; }

        reverse_iterator rend() noexcept {
            return reverse_iterator{ &d_buffer_p[size()] };
        }

        const_reverse_iterator rbegin() const noexcept { return crbegin(); }

        const_reverse_iterator rend() const noexcept { return crend(); }

        const_reverse_iterator crbegin() const noexcept {
            return const_reverse_iterator{ d_buffer_p };
        }

        const_reverse_iterator crend() const noexcept {
            return const_reverse_iterator{ &d_buffer_p[size()] };
        }

        /* Capacity */
        bool empty() const noexcept { return size() == 0; }

        size_type size() const noexcept { return d_size; }

        size_type max_size() const noexcept {
            return alloc_traits::max_size(d_allocator);
        }

        size_type capacity() const noexcept { return d_buffer_capacity; }

        void resize(size_type sz) { resize(sz, T{}); }

        void resize(size_type sz, const T& c) {
            if (sz < d_size) {
                for (size_type i = sz; i < d_size; ++i) {
                    destroy_one(&d_buffer_p[i]);
                }
                return;
            }
            while (d_size < sz) {
                push_back(c);
            }
        }

        void reserve(size_type n) { change_capacity_(n); }

        void shrink_to_fit() {
            if (size() < capacity() / 2) {
                change_capacity_(size());
            }
        }

        /* Element Access */
        reference operator[](size_type pos) {
            assert(pos < size());  // Be nice to devs
            return d_buffer_p[pos];
        }

        const_reference operator[](size_type pos) const {
            assert(pos < size());
            return d_buffer_p[pos];
        }

        const_reference at(size_type pos) const {
            if (pos >= size()) {
                throw std::out_of_range("Position out of range");
            }
            return operator[](pos);
        }

        reference at(size_type pos) {
            if (pos >= size()) {
                throw std::out_of_range("Position out of range");
            }
            return operator[](pos);
        }

        reference front() { return *d_buffer_p; }

        const_reference front() const { return *d_buffer_p; }

        reference back() {
            assert(size() > 0);
            return d_buffer_p[size() - 1];
        }

        const_reference back() const {
            assert(size() > 0);
            return d_buffer_p[size() - 1];
        }

        /* Data Access */
        T* data() noexcept { return d_buffer_p; }

        const T* data() const noexcept { return d_buffer_p; }

        /* Modifiers */
        template <class... Args>
        reference emplace_back(Args &&... args) {
            if (size() >= capacity()) {
                grow_();
            }
            alloc_traits::construct(d_allocator, &d_buffer_p[d_size],
                std::forward<Args>(args)...);
            ++d_size;
            return back();
        }

        void push_back(const T& x) {
            if (size() >= capacity()) {
                grow_();
            }
            alloc_traits::construct(d_allocator, &d_buffer_p[d_size], x);
            ++d_size;
        }

        void push_back(T&& x) {
            if (size() >= capacity()) {
                grow_();
            }
            alloc_traits::construct(d_allocator, &d_buffer_p[d_size], std::move(x));
            ++d_size;
        }

        void pop_back() {
            destroy_one_(&back());
            --d_size;
        }

        template <class... Args>
        iterator emplace(const_iterator position, Args &&... args) {
            // Save index before potentially invalidating
            auto idx = position - cbegin();

            if (size() >= capacity()) grow_();  // May invalidate iterators

            iterator pos = begin() + idx;
            auto end_iter = end();
            shift_after_by_(pos, 1);  // Handles size change
            if (pos != end_iter) destroy_one_(&*pos);
            alloc_traits::construct(d_allocator, &*pos, std::forward<Args>(args)...);
            return pos;
        }

        iterator insert(const_iterator position, const T& x) { emplace(position, x); }

        iterator insert(const_iterator position, T&& x) {
            return emplace(position, std::move(x));
        }

        iterator insert(const_iterator position, size_type n, const T& x) {
            // Save index before potentially invalidating
            auto idx = position - cbegin();

            // May invalidate iterators
            if (size() + n >= capacity()) change_capacity_(size() + n);

            iterator pos = begin() + idx;
            auto end_iter = end();
            shift_after_by_(pos, n);  // Handles size change
            if (pos != end_iter) destroy_one_(&*pos);
            for (; n > 0; --n) {
                auto dest = pos + n;
                if (dest < end_iter) destroy_one_(&*dest);
                alloc_traits::construct(d_allocator, &*dest, x);
            }
            return pos;
        }

        template <class InputIterator, class = typename std::iterator_traits<
            InputIterator>::iterator_category>
        iterator insert(const_iterator position, InputIterator first,
            InputIterator last) {
            auto n = std::distance(first, last);
            auto idx = position - cbegin();
            if (size() + n >= capacity()) change_capacity_(size() + n);
            iterator pos = begin() + idx;
            auto end_iter = end();
            shift_after_by_(pos, n);  // Handles size change
            if (pos != end_iter) destroy_one_(&*pos);
            for (difference_type i = 0; first != last; ++first, ++i) {
                auto dest = pos + i;
                if (dest < end_iter)
                    *dest = *first;
                else
                    alloc_traits::construct(d_allocator, &*dest, *first);
            }
            return pos;
        }

        iterator insert(const_iterator position, std::initializer_list<T> il) {
            auto idx = position - cbegin();
            if (size() + il.size() >= capacity()) change_capacity_(size() + il.size());
            auto pos = iterator{ begin() + idx };
            auto end_iter = end();
            shift_after_by_(pos, il.size());  // Handles size change
            if (pos != end_iter) destroy_one_(&*pos);
            difference_type i = 0;
            for (auto&& el : il) {
                auto dest = pos + i;
                if (dest < end_iter) {
                    *dest = std::move_if_noexcept(el);
                }
                else {
                    alloc_traits::construct(d_allocator, &*dest, std::move_if_noexcept(el));
                }
                ++i;
            }
            return pos;
        }

        iterator erase(const_iterator position) {
            return erase(position, position + 1);
        }

        iterator erase(const_iterator first, const_iterator last) {
            iterator it = begin() + (first - cbegin());
            iterator last_it = begin() + (last - cbegin());
            iterator jt = last_it;
            for (; jt != end(); ++it, ++jt) {
                *it = std::move_if_noexcept(*jt);
            }
            iterator end_it = end();
            for (; it != end_it; ++it) {
                destroy_one_(&*it);
                --d_size;
            }
            return begin() + (last_it - cbegin());
        }

        void swap(vector& other) noexcept(
            alloc_traits::propagate_on_container_swap::value ||
            alloc_traits::is_always_equal::value) {
            if constexpr (alloc_traits::propagate_on_container_swap::value) {
                std::swap(d_allocator, other.d_allocator);
            }
            std::swap(d_buffer_p, other.d_buffer_p);
            std::swap(d_size, other.d_size);
            std::swap(d_buffer_capacity, other.d_buffer_capacity);
        }

        void clear() noexcept {
            destroy_all_();
            d_size = 0;
        }

    private:
        allocator_type d_allocator;
        pointer d_buffer_p = nullptr;
        size_type d_size = 0;
        size_type d_buffer_capacity = 0;

    public:
        friend void swap(vector& lhs, vector& rhs) noexcept { lhs.swap(rhs); }

        friend bool operator==(const vector& lhs, const vector& rhs) {
            auto lit = lhs.begin();
            auto rit = rhs.begin();
            for (; lit != lhs.end() && rit != rhs.end(); ++lit, ++rit) {
                if (!(*lit == *rit)) return false;
            }
            return lit == lhs.end() && rit == rhs.end();
        }

        friend bool operator!=(const vector& lhs, const vector& rhs) {
            return !(lhs == rhs);
        }

        friend bool operator<(const vector& lhs, const vector& rhs) {
            auto lit = lhs.begin();
            auto rit = rhs.begin();
            for (; lit != lhs.end() && rit != rhs.end(); ++lit, ++rit) {
                if (*lit < *rit) return true;
                if (*rit < *lit) return false;
            }
            return lit == lhs.end() && rit != rhs.end();
        }

        friend bool operator<=(const vector& lhs, const vector& rhs) {
            auto lit = lhs.begin();
            auto rit = rhs.begin();
            for (; lit != lhs.end() && rit != rhs.end(); ++lit, ++rit) {
                if (*lit < *rit) return true;
                if (*rit < *lit) return false;
            }
            return lit == lhs.end();
        }

        friend bool operator>(const vector& lhs, const vector& rhs) {
            return rhs < lhs;
        }

        friend bool operator>=(const vector& lhs, const vector& rhs) {
            return rhs <= lhs;
        }
    };
}