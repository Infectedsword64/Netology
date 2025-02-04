#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include "My_list.h"


int main(int argc, char* argv[]) {
    return Catch::Session().run(argc, argv);
}

TEST_CASE("test list", "[list]") {
    SECTION("Emptiness") {
        List list;
        REQUIRE_THROWS(list.PopBack());
        REQUIRE_THROWS(list.PopFront());
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
        REQUIRE_THROWS(list.PopBack());
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
        REQUIRE_THROWS(list.PopFront());
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
