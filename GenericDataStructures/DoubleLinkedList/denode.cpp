/*****************************************************************//**
 * \file   denode.cpp
 * \brief  Generic doubly linked list implementation.
 *
 * Consider "../LinkedList/node.hpp"
 *
 * \author Xuhua Huang
 * \date   December 13, 2022
 *********************************************************************/

#include <denode.hpp>

namespace util::data_structure {

    /* default constructor */
    template<typename elem_type>
    denode<elem_type>::denode()
        requires std::default_initializable<elem_type>
    : elem_value{}
    , prev_denode{ nullptr }
    , next_denode{ nullptr } {
    }

    /* overloaded constructor */
    template<typename elem_type>
    denode<elem_type>::denode(const elem_type& value)
        requires std::copy_constructible<elem_type>
    : elem_value{ value }
    , prev_denode{ nullptr }
    , next_denode{ nullptr } {
    }

} // util::data_structure
