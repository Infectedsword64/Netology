#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include<catch2/catch_session.hpp>

struct ListNode
{
public:
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

public:
    int value;
    ListNode* prev;
    ListNode* next;
};


class List
{
public:
    List()
        : m_head(new ListNode(static_cast<int>(0))), m_size(0),
        m_tail(new ListNode(0, m_head))
    {
    }

    virtual ~List()
    {
        Clear();
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }

    unsigned long Size() { return m_size; }

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    void Clear()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;
            delete extractPrev(current);
        }
    }

private:
    ListNode* extractPrev(ListNode* node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};


int main(int argc, char* argv[]) {
    return Catch::Session().run(argc, argv);
}

TEST_CASE("test list", "[list]") {
    SECTION("Emptiness") {
        List list;
        CHECK(list.Empty() == true);
        list.PushFront(100);
        CHECK(list.Empty() == false);
    }
    SECTION("Size") {
        List list;
        CHECK(list.Size() == 0);
        list.PushFront(10);
        CHECK(list.Size() == 1);
        list.PushFront(30);
        CHECK(list.Size() == 2);
        list.PopFront();
        CHECK(list.Size() == 1);
        list.PopBack();
        CHECK(list.Size() == 0);
    }
    SECTION("Clear") {
        List list;
        list.PushFront(10);
        list.PushFront(30);
        list.Clear();
        CHECK(list.Empty() == true);
    }
    SECTION("PushBack") {
        List list;
        list.PushBack(10);
        list.PushBack(30);
        list.PushBack(44);
        list.PushBack(131);
        CHECK(list.Size() == 4);
    }
    SECTION("PushFront") {
        List list;
        list.PushFront(10);
        list.PushFront(30);
        list.PushFront(30);
        list.PushFront(30);
        CHECK(list.Size() == 4);
    }
    SECTION("PopBack") {
        List list;
        list.PushFront(10);
        list.PushFront(30);
        list.PushFront(30);
        list.PushFront(30);
        list.PopBack();
        list.PopBack();
        CHECK(list.Size() == 2);
    }
    SECTION("PopFront") {
        List list;
        list.PushFront(10);
        list.PushFront(30);
        list.PushFront(30);
        list.PushFront(30);
        list.PopFront();
        list.PopFront();
        CHECK(list.Size() == 2);
    }
    system("pause");
}
