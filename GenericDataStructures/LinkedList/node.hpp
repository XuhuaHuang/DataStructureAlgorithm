/*****************************************************************//**
 * \file   node.hpp
 * \brief  Generic linked list implementation.
 * Consider "../../LinkedList/link_list.c"
 * and      "../../LinkedList/node.hpp"
 * 
 * todo:
 * 1. overload debug_this() function with a std::function
 *    or some other forms of predicate.
 * 2. overload miscellaneous comparison and increment operator
 * 3. consider the possibility of adding iterator implementation
 * 
 * references:
 * 1. https://www.boost.org/doc/libs/1_80_0/libs/phoenix/doc/html/phoenix/modules/operator.html
 * 2. https://en.cppreference.com/w/cpp/language/operators
 * 3. https://en.cppreference.com/w/cpp/container/list
 * 4. https://en.cppreference.com/w/cpp/container/forward_list
 * 
 * \author Xuhua Huang
 * \date   December 10, 2022
 *********************************************************************/

#ifndef NODE_HPP
#define NODE_HPP

#ifndef _IOSTREAM_
#include <iostream>
#endif

#ifndef _CONCEPTS_
#include <concepts>
#endif

#ifndef _NEW_
#include <new>
#endif

#ifndef _FORMAT_
#include <format>
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

namespace util::data_structure {

template<typename _Elem>
class node;

template<typename elem_type>
using linked_list = node<elem_type>;

template<typename _Elem>
class node final {
    using elem_type = _Elem;

public:
    /* default constructor */
    /* std::is_default_constructible<elem_type>::value */
    explicit node<elem_type>()
    requires std::default_initializable<elem_type>
    : elem_value(elem_type())
    , next_node(nullptr) {}

    /* overloaded constructor */
    /* std::is_copy_constructible<elem_type>::value */
    explicit node<elem_type>(const elem_type& value, node<elem_type>* const next = nullptr)
    requires std::copy_constructible<elem_type>
    : elem_value(value)
    , next_node(next) {}

    /* copy constructor */
    /* std::is_copy_constructible<elem_type>::value */
    /* std::is_copy_constructible<node<elem_type>>::value */
    node<elem_type>(const node<elem_type>& rhs)
    requires std::copy_constructible<elem_type>
    : elem_value(rhs.elem_value)
    , next_node(rhs.next_node) {}

    /* copy assignment operator */
    /* std::is_copy_assignable<elem_type>::value */
    [[nodiscard]] node<elem_type>& operator = (const node<elem_type>& rhs)
    requires std::copyable<elem_type> {
        // guard self assignment
        if (this == &rhs) { return *this; }
        elem_value = rhs.elem_value;
        next_node = rhs.next_node;
        return *this;
    }

    /* move constructor */
    /* std::is_move_constructible<elem_type>::value */
    node<elem_type>(node<elem_type>&& rhs) noexcept
    requires std::movable<elem_type>
    : elem_value(std::move(rhs.elem_value))
    , next_node(std::move(rhs.next_node)) {}

    /* move assignment operator */
    /* std::is_move_assignable<elem_type>::value
    && std::is_copy_assignable<elem_type>::value */
    [[nodiscard]] node<elem_type>& operator = (node<elem_type>&& rhs) noexcept
    requires std::copyable<elem_type> && std::movable<elem_type>
    && std::is_nothrow_move_assignable<elem_type>::value {
        // guard self assignment
        if (this == &rhs) { return *this; }
        elem_value = std::move(rhs.elem_value);
        next_node = std::move(rhs.next_node);
        return *this;
    }

    /* destructor */
    ~node<elem_type>()
    requires std::destructible<elem_type> = default;

    /* elem_value mutator and accessor */
    /* std::is_copy_assignable<elem_type>::value */
    /* std::is_copy_assignable_v<elem_type> */
    inline elem_type& value()
    requires std::is_copy_assignable<elem_type>::value { return elem_value; }
    inline const elem_type value() const
    requires std::copyable<elem_type> { return elem_value; }

    /* next_node mutator and accessor */
    inline node<elem_type>* next() const { return next_node; }
    /* link_next function does not check for nullptr connection */
    /* consider using linear_insert(node<elem_type>* n) instead */
    inline void link_next(node<elem_type>* node) { next_node = node; }

    /* member function */
    void linear_insert(node<elem_type>* elem) noexcept;

    void debug_this(void);
    void debug_this(std::ostream& out);

    /* non-member static function */
    static void print_all_after(const linked_list<elem_type>* const elem);

    /* drop functionality is not implemented as of now */
    /* consider using link_next() to directly link to the node after instead (skip the next node) * /
    /* ------------------------------- */
    /* node -> next_node -> node_after */
    /* node.link_next(&node_after);    */
    /* node ->    -->    -> node_after */
    /* ------------------------------- */
    /* next_node require manual deallocation if it is allocated on the heap */
    /* or automatically destructed when it goes out of scope if it is on the stack */
    static inline void drop_all_after(node<elem_type>* elem) {
        elem->link_next(nullptr);
    }

    /* overloaded new and delete operator */
    /* otherwise linked_list<>* will fail */
    [[nodiscard]] static void* operator new(std::size_t size);
    static void operator delete(void* ptr) noexcept;
    [[nodiscard]] static void* operator new[](std::size_t count);
    static void operator delete[](void* ptr, std::size_t size);

    /* prefix increment */
    [[nodiscard]] inline node<elem_type>& operator ++ () {
        if (next_node != nullptr) {
            return *next_node;
        }
        else {
            return *this;
        }
    }

    /* postfix increment */
    node<elem_type> operator ++ (int) = delete;

    /* prefix and postfix decrement */
    node<elem_type>& operator -- () = delete;
    node<elem_type> operator -- (int) = delete;

    /* comparison operator */
    inline auto operator <=> (const node<elem_type>& elem) const
    requires std::three_way_comparable<elem_type> {
        return elem_value <=> elem.elem_value;
    }

    /* equality comparator */
    inline bool operator == (const node<elem_type>& elem) const
    requires std::equality_comparable<elem_type> {
        /* another alternative approach is to use <=> operator */
        /* and compare the output with std::strong_ordering::equal */
        return elem_value == elem.elem_value && next_node == elem.next_node;
    }

    /* inequality comparator */
    inline bool operator != (const node<elem_type>& elem) const
    requires std::equality_comparable<elem_type> {
        return !(operator == (elem));
    }

    /* operator >> overload to link nodes */
    /* lhs >> &rhs */
    /* does not support chained linking operation */
    inline friend void operator >> (node<elem_type>& lhs, node<elem_type>* rhs) noexcept {
        lhs.linear_insert(rhs);
        return;
    }

    /* operator << overload with attribute-like signature */
    inline friend std::ostream& operator << (std::ostream& out, const node<elem_type>& elem) {
        return out << __func__ << " [[std::ostream&]] << node data: " << elem.value() << "\n";
    }

    inline friend node<elem_type>& operator << (node<elem_type>& lhs, node<elem_type>* rhs) {
        lhs.linear_insert(rhs);
        return (node<elem_type>&)*rhs;
    }

private:
    elem_type elem_value;
    node<elem_type>* next_node;
};

/**
 * Insert a node linearly and maintain the connection with the nodes after.
 *
 * \param elem
 * \return void
 */
template<typename elem_type>
void
node<elem_type>::linear_insert(node<elem_type>* elem) noexcept {
    if (elem == nullptr) {
        std::cout << "Warning! Attempting to linearly link a null pointer" << "\n";
        std::cout << "Returning the control flow" << "\n";
    }
    else if (next_node == elem) {
        std::cout << "Warning! Attempting to linearly link a node already linked as the next" << "\n";
        std::cout << "Returning the control flow" << "\n";
    }
    else [[likely]] {
        node<elem_type>* copy = next_node;
        link_next(elem);
        elem->link_next(copy);
    }

    return;
}

/**
 * Format and print node to stdout.
 *
 * \param void
 */
template<typename elem_type>
void
node<elem_type>::debug_this(void)
// requires elem_type::operator << || std::convertible_to<elem_type, std::string>
{
    if (next_node != nullptr) [[likely]] {
        // consider the following alternatives:
        // std::cout << hex << next_node;
        // std::cout << reinterpret_cast<void*>(next_node);
        // std::reinterpret_pointer_cast<void*>(next_node);
#ifdef __cpp_lib_print
        if constexpr (std::is_same<elem_type, int>::value || std::convertible_to<elem_type, int>) {
            std::print(
                std::cout,
                "node data: {}, next node: {}", elem_value, next_node
            );
        }
#else
        if constexpr (std::is_same<elem_type, int>::value) {
            std::printf("node data: %d, next node: %p\n", elem_value, next_node);
        }
        else if constexpr (std::is_same<elem_type, double>::value) {
            std::printf("node data: %.4f, next node: %p\n", elem_value, next_node);
        }
        else {
            // requires elem_type::operator << (std::ostream& stdcout, const elem_type& elem_value)
            std::cout << "node data: " << elem_value << ", next node: " << reinterpret_cast<void*>(next_node) << "\n";
        }
#endif
    }
    else {
        // requires elem_type::operator << (std::ostream& stdcout, const elem_type& elem_value)
        std::cout << "node data: " << elem_value << ", next node: nullptr" << "\n";
    }

    return;
}

/**
 * Using class specific friend oprator << to output to received std::ostream&.
 *
 * \param out
 */
template<typename elem_type>
void
node<elem_type>::debug_this(std::ostream& out) {
    out << (*this);
    return;
}

/**
 * Non-member function to print linked list starting from a node.
 *
 * \param elem
 */
template<typename elem_type>
inline void
node<elem_type>::print_all_after(const linked_list<elem_type>* const elem) {
    std::cout << "linked_list ";
    const node<elem_type>* temp(elem);
    while (temp != nullptr) {
        std::cout << temp->value() << " -> ";
        temp = temp->next_node;
    }
    std::cout << "nullptr\n";

    return;
}

/**
 * Overloaded new operator to allocate a node on the heap.
 *
 * \param size
 * \return void*, a pointer without type information
 */
template<typename elem_type>
[[nodiscard]] void*
node<elem_type>::operator new(std::size_t size) {
    if (size == 0) {
        ++size; // avoid std::malloc(0) which may return nullptr on success
    }

    if (void* ptr = std::malloc(size)) {
        return ptr;
    }

    throw std::bad_alloc{};
}

/**
 * Overloaded delete operator to deallocate a node on the heap.
 *
 * \param ptr
 * \return void
 */
template<typename elem_type>
void
node<elem_type>::operator delete(void* ptr) noexcept {
    std::free(ptr);
    return;
}


/**
 * Overloaded new[] operator to allocate an array of node on the heap.
 *
 * \param size
 * \return void*, a pointer without type information
 */
template<typename elem_type>
[[nodiscard]] void*
node<elem_type>::operator new[](std::size_t count) {
    return ::operator new[](count);
}

/**
 * Overloaded delete[] operator to deallocate an array of node on the heap.
 *
 * \param ptr
 * \return void
 */
template<typename elem_type>
void
node<elem_type>::operator delete[](void* ptr, std::size_t size) {
    ::operator delete[](ptr);
    return;
}

} // util::data_structure

#endif
