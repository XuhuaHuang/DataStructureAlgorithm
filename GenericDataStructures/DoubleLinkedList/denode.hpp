/*****************************************************************//**
 * \file   denode.hpp
 * \brief  Generic doubly linked list implementation.
 * 
 * Consider "../LinkedList/node.hpp"
 * 
 * \author Xuhua Huang
 * \date   December 13, 2022
 *********************************************************************/

#ifndef DENODE_HPP
#define DENODE_HPP

#include <iostream>
#include <concepts>
#include <new>
#include <format>
#include <type_traits>

namespace util::data_structure {

template<typename _Elem>
class denode;

template<typename _Elem>
using double_linked_list = denode<_Elem>;

template<typename _Elem>
class denode final {
    using elem_type = _Elem;

public:

    /* default constructor */
    /* std::is_default_constructible<elem_type>::value */
    explicit denode<elem_type>()
    requires std::default_initializable<elem_type>;

    /* overloaded constructor */
    /* std::is_copy_constructible<elem_type>::value */
    explicit denode<elem_type>(const elem_type& value)
    requires std::copy_constructible<elem_type>;

    /* specialized overload for head node of double linked list */
    explicit denode<elem_type>(const elem_type& value, denode<elem_type>* const next)
    requires std::copy_constructible<elem_type>;

    /* specialized overload for tail node of double linked list */
    explicit denode<elem_type>(denode<elem_type>* const prev, const elem_type& value)
    requires std::copy_constructible<elem_type>;

    /* specialized overload for ordinary node */
    explicit denode<elem_type>(const elem_type& value, denode<elem_type>* const prev, denode<elem_type>* const next)
    requires std::copy_constructible<elem_type>;

    /* copy constructor */
    /* std::is_copy_constructible<denode<elem_type>>::value */
    denode<elem_type>(const denode<elem_type>& rhs)
    requires std::copy_constructible<elem_type>::value;

    /* copy assignment operator overload */
    /* std::is_copy_assignable<elem_type>::value */
    [[nodiscard]] denode<elem_type>& operator = (const denode<elem_type>& rhs)
    requires std::copyable<elem_type>;

    /* move constructor overload */
    /* std::is_move_constructible<denode<elem_type>>::value */
    denode<elem_type>(denode<elem_type>&& rhs) noexcept
    requires std::movable<elem_type>;

    /* move assignment operator overload */
    /* std::is_move_assignable<elem_type>::value
    && std::is_copy_assignable<elem_type>::value */
    [[nodiscard]] denode<elem_type>& operator = (denode<elem_type>&& rhs) noexcept
    requires std::copyable<elem_type>
    && std::movable<elem_type>
    && std::is_nothrow_move_assignable<elem_type>::value;

    /* destructor */
    ~denode<elem_type>()
    requires std::destructible<elem_type>;

    /* overloaded new and delete operator */
    /* otherwise denode<_Elem>* will fail */
    [[nodiscard]] static void* operator new(std::size_t size);
    static void operator delete(void* ptr) noexcept;

    [[nodiscard]] static void* operator new[](std::size_t count);
    static void operator delete[](void* ptr, std::size_t size);

    /* elem_value mutator and accessor */
    /* std::is_copy_assignable<elem_type>::value */
    /* std::is_copy_assignable_v<elem_type> */
    inline elem_type& value()
    requires std::is_copy_assignable<elem_type>::value { return elem_value; }

    inline elem_type const value() const
    requires std::copyable<elem_type> { return elem_value; }

    /* previous node mutator and accessor */
    inline denode<elem_type>* prev() const { return prev_denode; }
    inline void set_prev(denode<elem_type>* prev) { prev->next_denode = this; prev_denode = prev; }

    /* next node mutator and accessor */
    inline denode<elem_type>* next() const { return next_denode; }
    inline void set_next(denode<elem_type>* next) { next->prev_denode = this; next_denode = next; }

    /* link-as-previous node member function */
    void linear_prepend(denode<elem_type>* node);

    /* link-as-next node member function */
    void linear_append(denode<elem_type>* node);

    static inline void drop_all_before(denode<elem_type>* node);

    static inline void drop_all_after(denode<elem_type>* node);

    /* prefix increment operator */
    [[nodiscard]] denode<elem_type>& operator ++ ();

    /* postfix increment operator */
    denode<elem_type> operator ++ (int) = delete;

    /* prefix decrement operator */
    [[nodiscard]] denode<elem_type>& operator -- ();

    /* postfix increment operator */
    denode<elem_type> operator -- (int) = delete;

    /* three-way comparison operator */
    inline auto operator <=> (const denode<elem_type>& node) const
    requires std::three_way_comparable<elem_type> {
        return elem_value <=> node.elem_value;
    }

    /* equality comparison operator */
    inline bool operator == (const denode<elem_type>& node) const
    requires std::equality_comparable<elem_type>;

    /* inequality comparison operator */
    inline bool operator != (const denode<elem_type>& node) const
    requires std::equality_comparable<elem_type> {
        return !(operator == (node));
    }

    /* operator >> overload to link a node */
    inline friend void operator >> (denode<elem_type>& lhs, denode<elem_type>* rhs) noexcept;

    /* operator << overload with attribute-like signature */
    inline friend std::ostream& operator << (std::ostream& out, const denode<elem_type>& node) {
        return out << __func__ << " [[std::ostream&]] << denode data: " << node.elem_value << "\n";
    }

    // friend denode<elem_type>& operator << (denode<elem_type>& lhs, denode<elem_type>* const rhs);
    friend auto operator << (denode<elem_type>& lhs, denode<elem_type>* const rhs) -> denode<elem_type>&;

    /* supportive debug and print functionality */
    inline void debug_this();

    inline void debug_this(std::ostream& out);

    /* non-member static function */
    static void print_all_before(const double_linked_list<elem_type>* const node);

    static void print_all_after(const double_linked_list<elem_type>* const node);

private:
    elem_type elem_value;
    denode<elem_type>* prev_denode;
    denode<elem_type>* next_denode;
};

template<typename elem_type>
inline void denode<elem_type>::print_all_before(const double_linked_list<elem_type>* const node)
{
}

} // util::data_structure

#endif // DENODE_HPP
