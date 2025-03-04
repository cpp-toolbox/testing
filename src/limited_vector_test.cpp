#include "utility/limited_vector/limited_vector.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Test Push Back", "[limited_vector]") {
    LimitedVector<int> lv(3);
    lv.push_back(1);
    lv.push_back(2);
    lv.push_back(3);

    REQUIRE(lv.size() == 3);
    REQUIRE(lv[0] == 1);
    REQUIRE(lv[1] == 2);
    REQUIRE(lv[2] == 3);
}

TEST_CASE("Test Overflow Push Back", "[limited_vector]") {
    LimitedVector<int> lv(3);
    lv.push_back(1);
    lv.push_back(2);
    lv.push_back(3);
    lv.push_back(4);

    // After pushing the 4th element, the first element should be removed
    REQUIRE(lv.size() == 3);
    REQUIRE(lv[0] == 2);
    REQUIRE(lv[1] == 3);
    REQUIRE(lv[2] == 4);
}

TEST_CASE("Test Access", "[limited_vector]") {
    LimitedVector<int> lv(3);
    lv.push_back(1);
    lv.push_back(2);

    // Test operator[]
    REQUIRE(lv[0] == 1);
    REQUIRE(lv[1] == 2);

    // Test const access
    const LimitedVector<int> &const_lv = lv;
    REQUIRE(const_lv[0] == 1);
    REQUIRE(const_lv[1] == 2);
}

TEST_CASE("Test Front and Back", "[limited_vector]") {
    LimitedVector<int> lv(3);
    lv.push_back(10);
    lv.push_back(20);
    lv.push_back(30);

    REQUIRE(lv.front() == 10);
    REQUIRE(lv.back() == 30);
}

TEST_CASE("Test Clear", "[limited_vector]") {
    LimitedVector<int> lv(3);
    lv.push_back(1);
    lv.push_back(2);

    lv.clear();
    REQUIRE(lv.size() == 0);
    REQUIRE(lv.empty());
}

TEST_CASE("Test Empty", "[limited_vector]") {
    LimitedVector<int> lv(3);
    REQUIRE(lv.empty());

    lv.push_back(100);
    REQUIRE(!lv.empty());
}

TEST_CASE("Test Size", "[limited_vector]") {
    LimitedVector<int> lv(5);
    REQUIRE(lv.size() == 0);

    lv.push_back(1);
    lv.push_back(2);
    REQUIRE(lv.size() == 2);

    lv.push_back(3);
    lv.push_back(4);
    lv.push_back(5);
    REQUIRE(lv.size() == 5);
}

TEST_CASE("Test Iterators", "[limited_vector]") {
    LimitedVector<int> lv(3);
    lv.push_back(10);
    lv.push_back(20);
    lv.push_back(30);

    int i = 10;
    for (auto it = lv.begin(); it != lv.end(); ++it) {
        REQUIRE(*it == i);
        i += 10;
    }
}

TEST_CASE("Test Const Iterators", "[limited_vector]") {
    LimitedVector<int> lv(3);
    lv.push_back(1);
    lv.push_back(2);
    lv.push_back(3);

    const LimitedVector<int> &const_lv = lv;

    int i = 1;
    for (auto it = const_lv.begin(); it != const_lv.end(); ++it) {
        REQUIRE(*it == i);
        ++i;
    }
}

TEST_CASE("Test Front Const", "[limited_vector]") {
    LimitedVector<int> lv(3);
    lv.push_back(1);
    lv.push_back(2);
    lv.push_back(3);

    const LimitedVector<int> &const_lv = lv;

    REQUIRE(const_lv.front() == 1);
}

TEST_CASE("Test Back Const", "[limited_vector]") {
    LimitedVector<int> lv(3);
    lv.push_back(10);
    lv.push_back(20);
    lv.push_back(30);

    const LimitedVector<int> &const_lv = lv;

    REQUIRE(const_lv.back() == 30);
}
