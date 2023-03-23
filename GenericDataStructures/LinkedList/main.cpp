/*****************************************************************//**
 * \file   main.cpp
 * \brief  Trivial data types test cases for basic node implementation.
 *
 * \author Xuhua Huang
 * \date   December 10, 2022
 *********************************************************************/

#include <iostream>
#include <stdlib.h>
#include <type_traits>

#include <node.hpp>

auto main(void) -> int {

    using namespace util::data_structure;

    /* -------------------------------- */
    /* testing default initialized node */
    /* -------------------------------- */
    std::cout << "\033[32mTesting default initialized nodes \033[m" << "\n";
    node<int> init_node{};
    init_node.debug_this();

    node<int> init_node_copy{};
    init_node_copy.debug_this();

    std::cout << "\033[32mChanging the element value of nodes \033[m" << "\n";
    init_node.value() = 3;
    std::cout << init_node;
    init_node_copy.value() = 6;
    std::cout << init_node_copy;

    init_node.link_next(&init_node_copy);
    node<int>::print_all_after(&init_node);

    /* --------------------------------------------------- */
    /* testing linked list with a heap-allocated head node */
    /* --------------------------------------------------- */
    std::cout << "\033[32mConstructing a fibonacci series \033[m" << "\n";
    std::cout << "\033[32mPrinting individual element ... \033[m" << "\n";

    linked_list<int>* head = new linked_list<int>();
    node<int> n1, n2, n3, n4;

    head->value() = 1;
    head->debug_this();
    n1.value() = 1;
    n1.debug_this();
    n2.value() = 2;
    n2.debug_this();
    n3.value() = 3;
    n3.debug_this();
    n4.value() = 5;
    n4.debug_this();

    std::cout << "\033[32mLinking nodes ... \033[m" << "\n";
    // head->link_next(&n1);
    // n1.link_next(&n2);
    // *head >> &n1;
    // n1 >> &n2;
    // n2.link_next(&n3);
    // n3.link_next(&n4);
    // n4.link_next(nullptr);
    *head << &n1 << &n2 << &n3 << &n4 << nullptr;

    std::cout << "\033[32mDone linking nodes; printing linked list \033[m" << "\n";
    node<int>::print_all_after(head);

    /* ----------------------------------- */
    /* testing linear insert functionality */
    /* ----------------------------------- */
    std::cout << "\033[32mTesting linear insert functionality \033[m" << "\n";
    node<int> n5{};
    head->linear_insert(nullptr);
    head->linear_insert(&n1);
    n1.linear_insert(&n2);

    n5.value() = 8;
    n4.linear_insert(&n5);

    std::cout << "\033[32mDone inserting; printing linked list \033[m" << "\n";
    node<int>::print_all_after(head);

    /* ---------------------------------- */
    /* testing node<double> functionality */
    /* ---------------------------------- */
    std::cout << "\033[32mTesting node<double> \033[m" << "\n";
    node<double> dn1{ 3.1416, nullptr };
    node<double> dn2{ 0.9265, nullptr };

    dn1.debug_this();
    dn2.debug_this();
    dn1.link_next(&dn2);

    std::cout << "\033[32mTesting overloaded debug_this(std::ostream&) \033[m" << "\n";
    dn1.debug_this(std::cerr);
    dn2.debug_this(std::clog);

    /* ----------------------------------- */
    /* testing overloaded move constructor */
    /* ----------------------------------- */
    std::cout << "\033[32mTesting overloaded move constructor \033[m" << "\n";
    node<double> n6{ std::move(dn2) };

    std::cout << "\033[32mPrinting with std::cout << \033[m" << "\n";
    std::cout << n6;

    std::cout << "\033[32mPrinting with debug_this(void) \033[m" << "\n";
    n6.debug_this();

    std::cout << "\033[32mPrinting with debug_this(std::ostream&) \033[m" << "\n";
    n6.debug_this(std::cerr);

    /* ------------------------------ */
    /* testing drop all functionality */
    /* ------------------------------ */
    std::cout << "\033[32mTesting drop all functionality \033[m" << "\n";
    node<int>::drop_all_after(head);
    node<int>::print_all_after(head);
    std::cout << *head;

    /* --------------------------------- */
    /* testing prefix increment operator */
    /* --------------------------------- */
    std::cout << "\033[32mTesting prefix increment operator \033[m" << "\n";
    node<int> prev_node{};
    node<int> next_node{ 12, nullptr };

    // prev_node.link_next(&next_node);
    prev_node >> &next_node;

    node<int>::print_all_after(&prev_node);

    node<int> next_node_ref = ++prev_node;
    next_node_ref.debug_this();

    /* ------------------------------- */
    /* testing <=> comparison operator */
    /* ------------------------------- */
    std::cout << "\033[32mTesting <=> comparison operator \033[m" << "\n";
    auto use_comparison_op = [&]() mutable -> void {
        /* <=> operator */
        if ((next_node <=> next_node_ref) == std::strong_ordering::equal) {
            std::cout << "<=> operator evaluated to euqal" << "\n";
        }
        /* != operator relies on == operator */
        next_node.value() = 10;
        if (next_node != next_node_ref) {
            std::cout << "!= operator evaluated to true" << "\n";
        }
    };

    use_comparison_op();

    delete head;

    system("pause");
    return EXIT_SUCCESS;
}
