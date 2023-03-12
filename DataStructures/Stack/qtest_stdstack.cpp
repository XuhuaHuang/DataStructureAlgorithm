/*****************************************************************//**
 * \file   qtest_stdstack.cpp
 * \brief  Demonstrate use case of std::stack<> with QTest framework.
 *
 * \author Xuhua Huang
 * \date   December 09, 2022
 *********************************************************************/

#include <iostream>
#include <stack>
#include <deque>
#include <algorithm>

#include <QTest>
#include <QDebug>
#include <QString>

class TestStdStack : public QObject
{
    Q_OBJECT

public:
    // default constructor implicitly tests std::stack copy construction
    // and its ability to initialize from a std::deque
    // probably not the best approach
    // but we are (so far) confident and comfortable doing so
    TestStdStack() : is(init_que), is_copy(is) {}
    void initTestCase()
    {
        // make sure private data member are initialized
        QVERIFY2(is.size() == 5, "Private data member constructed from init_que is not initalized properly");
        QVERIFY2(is_copy.size() == 5, "Private data member copy constructed is not initalized properly");
    }
    void cleanupTestCase() {}

private slots:
    void miscStackObjectConstruction() const;
    void spaceshipComparator() const;
    void lessThanAndLessThanEqualsOperator() const;

private:
    const std::deque<int> init_que = { 5, 4, 3, 2, 1 };
    std::stack<int> is;
    std::stack<int> is_copy;
};

void TestStdStack::miscStackObjectConstruction() const
{
    qDebug() << "Default constructor";
    std::stack<int> is;
    QVERIFY(is.empty() == true);
    QCOMPARE_EQ(is.size(), 0);

    qDebug() << "Initialization from container iterator";
#ifdef __cpp_lib_adaptor_iterator_pair_constructor
    const std::initializer_list<int> init_list = { 5, 4, 3, 2, 1 };
    std::stack<int> is2{ init_list.begin(), init_list.end() }; // requires C++23
    qDebug() << "is2.size() -> " << is2.size();
    QVERIFY(init_list.size() == 5 && is2.size() == 5);
    QVERIFY(is2.top() == 1);
#endif

    qDebug() << "Initialization from double-ended queue";
    // moved to private data member field to avoid code duplication
    // const std::deque<int> init_que = { 5, 4, 3, 2, 1 };
    std::stack<int> is3(this->init_que);
    QVERIFY(this->init_que.size() == 5 && is3.size() == 5);
    QVERIFY(is3.top() == 1);

    qDebug() << "Copy constructor and equality comparator";
    const std::stack<int> is4(is3);
    QVERIFY(is3 == is4);

    return;
}

void TestStdStack::spaceshipComparator() const
{
    // moved to private data member field to avoid code duplication
    // const std::deque<int> init_que = { 5, 4, 3, 2, 1 };
    // std::stack<int> is(init_que);
    // std::stack<int> is_copy(is);

    // <=> operator returns a std::compare_three_way_result_t<Container>
    // which is most likely a std::strong_ordering
    qDebug() << "Calling <=> spaceship comparator";
    QCOMPARE_EQ((is <=> is_copy)._Value, 0);

    return;
}

void TestStdStack::lessThanAndLessThanEqualsOperator() const
{
    std::stack<int> mutable_is(this->is);
    QVERIFY(!mutable_is.empty());
    QVERIFY(mutable_is.top() == 1);
    mutable_is.pop();

    qDebug() << "Calling less-than operator";
    QVERIFY(mutable_is < is);
    QCOMPARE(is < mutable_is, false);

    qDebug() << "Calling less-than-or-equals-to operator";
    QVERIFY(mutable_is <= is); // less-than
    mutable_is.push(1);
    QVERIFY(mutable_is <= is); // equality

    return;
}

QTEST_MAIN(TestStdStack)
#include "qtest_stdstack.moc"
