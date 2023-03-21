/*****************************************************************//**
 * \file   qtest_primitive_node.cpp
 * \brief  Primitive data type specialization node<> test.
 *
 * \author Xuhua Huang
 * \date   December 11, 2022
 *********************************************************************/

#include <iostream>
#include <QTest>
#include <QDebug>
#include <node.hpp>

class TestPrimitiveNode : public QObject
{
    Q_OBJECT

public:
    void initTestCase() {}
    void cleanupTestCase() {}

private slots:
    /* initializers */
    void testDefaultInit();
    void testOverloadedInit();
    void testCopyInit();
    void testMoveInit();

    /* mutator and accessor */
    void testNodeDataMutateAccess();
    void testNextNodeMutateAccess();

    /* insert and drop */
    void testLinearInsert();
    void testDropAllAfter();

    /* miscellaneous print overloads */
    void testMiscPrintFn();
};

void TestPrimitiveNode::testDefaultInit()
{
    using namespace util::data_structure;
    std::cout << "\033[32mTesting default initialized nodes \033[m" << "\n";

    node<int> init_node{};

    QVERIFY(init_node.value() == 0);
    QVERIFY(init_node.next() == nullptr);

    init_node.debug_this();

    return;
}

void TestPrimitiveNode::testOverloadedInit()
{
    using namespace util::data_structure;
    std::cout << "\033[32mTesting node<double> \033[m" << "\n";

    node<double> n1{ 3.1416, nullptr };
    QVERIFY(n1.value() == 3.1416);
    QVERIFY(n1.next() == nullptr);

    node<double> n2{ 0.9265, nullptr };
    QVERIFY(n2.value() == 0.9265);
    QVERIFY(n2.next() == nullptr);

    n1.debug_this();
    n2.debug_this();

    return;
}

void TestPrimitiveNode::testCopyInit()
{
    return;
}

void TestPrimitiveNode::testMoveInit()
{
    using namespace util::data_structure;
    std::cout << "\033[32mTesting overloaded move constructor \033[m" << "\n";

    node<double> n1{ 3.1416, nullptr };
    node<double> n2{ std::move(n1) };

    QVERIFY(n2.value() == 3.1416);
    QVERIFY(n2.next() == nullptr);

    return;
}

void TestPrimitiveNode::testNodeDataMutateAccess()
{
    using namespace util::data_structure;
    std::cout << "\033[32mTesting node data mutator and accessor \033[m" << "\n";

    node<double> n1{ 3.1416, nullptr };
    n1.value() = 0.9265;
    QVERIFY(n1.value() == 0.9265);

    return;
}

void TestPrimitiveNode::testNextNodeMutateAccess()
{
    using namespace util::data_structure;
    std::cout << "\033[32mTesting next node mutator and accessor \033[m" << "\n";

    node<double> n1{ 3.1416, nullptr };
    node<double> n2{ 0.9265, nullptr };
    n1.link_next(&n2);

    QVERIFY(n1.next() == &n2);

    return;
}

void TestPrimitiveNode::testLinearInsert()
{
    using namespace util::data_structure;
    std::cout << "\033[32mTesting linear insert functionality \033[m" << "\n";

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
    head->link_next(&n2);
    // n1.link_next(&n2); // skipping n1
    n2.link_next(&n4);
    // n3.link_next(&n4); // skipping n3
    n4.link_next(nullptr);

    node<int>::print_all_after(head); // 1 -> 2 -> 5 -> nullptr

    head->linear_insert(&n1);
    node<int>::print_all_after(head); // 1 -> 1 -> 2 -> 5 -> nullptr

    n2.linear_insert(&n3);

    std::cout << "\033[32mDone linking nodes; printing linked list \033[m" << "\n";
    node<int>::print_all_after(head); // 1 -> 1 -> 2 -> 3 -> 5 -> nullptr

    std::cout << "\033[32mTesting linear insert at the end of the linked list \033[m" << "\n";
    node<int> test_node{};

    qDebug() << "Attempting to insert nullptr and a linked node";

    head->linear_insert(nullptr);
    head->linear_insert(&n1);
    n1.linear_insert(&n2);

    test_node.value() = 8;
    n4.linear_insert(&test_node);

    std::cout << "\033[32mDone inserting; printing linked list \033[m" << "\n";
    node<int>::print_all_after(head); // 1 -> 1 -> 2 -> 3 -> 5 -> 8 -> nullptr

    delete head;

    return;
}

void TestPrimitiveNode::testDropAllAfter()
{
    using namespace util::data_structure;
    std::cout << "\033[32mTesting drop all functionality \033[m" << "\n";

    linked_list<int>* head = new linked_list<int>(1, nullptr);
    node<int> n1(1, nullptr), n2(2, nullptr), n3(3, nullptr), n4(5, nullptr);

    *head >> &n1; n1 >> &n2; n2 >> &n3; n3 >> &n4;

    node<int>::print_all_after(head); // 1 -> 1 -> 2 -> 3 -> 5 -> nullptr

    node<int>::drop_all_after(&n2);

    node<int>::print_all_after(head); // 1 -> 1 -> 2 -> nullptr

    delete head;

    return;
}

void TestPrimitiveNode::testMiscPrintFn()
{
    using namespace util::data_structure;
    std::cout << "\033[32mTesting overloaded debug_this(std::ostream&) \033[m" << "\n";

    node<double> n1{ 3.1416, nullptr };
    node<double> n2{ 0.9265, nullptr };

    n1.debug_this(std::cerr);
    n2.debug_this(std::clog);

    return;
}

QTEST_MAIN(TestPrimitiveNode)
#include "qtest_primitive_node.moc"
