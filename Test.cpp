#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "doctest.h"
#include "sources/MagicalContainer.hpp"


using namespace ariel;
using namespace std;

TEST_CASE("Test addElement and size") {
    MagicalContainer mc;

    // Check that the container is initially empty
    CHECK(mc.size() == 0);

    // Check that the size increments when elements are added
    for (int i = 1; i <= 10; ++i) {
        mc.addElement(i);
        CHECK(mc.size() == i);
    }
}

TEST_CASE("Test removeElement") {
    MagicalContainer mc;

    // Add some elements
    for (int i = 1; i <= 10; ++i) {
        mc.addElement(i);
    }

    // Check that the size decrements when elements are removed
    for (int i = 10; i >= 1; --i) {
        mc.removeElement(i);
        CHECK(mc.size() == i - 1);
    }

    // Try to remove an element that is not in the container
    mc.removeElement(100);
    CHECK(mc.size() == 0);
}

TEST_CASE("Test iterators") {
    MagicalContainer mc;

    // Add some elements
    for (int i = 1; i <= 10; ++i) {
        mc.addElement(i);
    }

    // Check AscendingIterator
    MagicalContainer::AscendingIterator asc_it(mc);
    auto it = asc_it.begin();
    for (int i = 1; i <= 10; ++i) {
        CHECK(*it == i);
        ++it;
    }

    // Check SideCrossIterator
    MagicalContainer::SideCrossIterator cross_it(mc);
    auto it2 = cross_it.begin();
    CHECK(*it2 == 1); ++it2;
    CHECK(*it2 == 10); ++it2;
    CHECK(*it2 == 2); ++it2;
    // ...

    // Check PrimeIterator
    MagicalContainer::PrimeIterator prime_it(mc);
    auto it3 = prime_it.begin();
    CHECK(*it3 == 2); ++it3;
    CHECK(*it3 == 3); ++it3;
    CHECK(*it3 == 5); ++it3;
    CHECK(*it3 == 7); ++it3;
}

TEST_CASE("Test edge cases") {
    MagicalContainer mc;

    // Check with large numbers
    mc.addElement(1000000000);
    mc.addElement(2000000000);
    CHECK(mc.size() == 2);

    // Check with negative numbers
    mc.addElement(-1);
    mc.addElement(-2);
    CHECK(mc.size() == 4);

    // Check with zero
    mc.addElement(0);
    CHECK(mc.size() == 5);
}

TEST_CASE("Test duplicate elements") {
    MagicalContainer mc;

    // Add some elements
    mc.addElement(1);
    mc.addElement(1);
    mc.addElement(2);
    mc.addElement(2);
    mc.addElement(3);

    // Check size
    CHECK(mc.size() == 5);

    // Check unique elements (assuming AscendingIterator only returns unique elements)
    MagicalContainer::AscendingIterator it(mc);
    auto it2 = it.begin();
    CHECK(*it2 == 1); ++it2;
    CHECK(*it2 == 2); ++it2;
    CHECK(*it2 == 3); ++it2;
}

TEST_CASE("Test iterator invalidation") {
    MagicalContainer mc;

    // Add some elements
    for (int i = 1; i <= 5; ++i) {
        mc.addElement(i);
    }

    // Get an iterator and advance it
    MagicalContainer::AscendingIterator it(mc);
    auto it2 = it.begin();
    ++it2;

    // Remove an element
    mc.removeElement(1);

    // Check that the iterator was invalidated
    CHECK_THROWS(*it2);
}

TEST_CASE("Test empty iterator") {
    MagicalContainer mc;

    // Check that an exception is thrown when dereferencing an empty iterator
    MagicalContainer::AscendingIterator it(mc);
    CHECK_THROWS(*it);
}

TEST_CASE("Test multiple iterators") {
    MagicalContainer mc;

    // Add some elements
    for (int i = 1; i <= 5; ++i) {
        mc.addElement(i);
    }

    // Check with multiple iterators simultaneously
    MagicalContainer::AscendingIterator it1(mc);
    MagicalContainer::AscendingIterator it2(mc);
    CHECK(*it1 == *it2);
    ++it1;
    CHECK(*it1 != *it2);
    ++it2;
    CHECK(*it1 == *it2);
}

TEST_CASE("Test iterator equality") {
    MagicalContainer mc;

    // Add some elements
    for (int i = 1; i <= 5; ++i) {
        mc.addElement(i);
    }

    // Check iterator equality
    MagicalContainer::AscendingIterator it1(mc);
    MagicalContainer::AscendingIterator it2(mc);
    CHECK(it1 == it2);
    ++it1;
    CHECK(it1 != it2);
}

TEST_CASE("Test out-of-bounds iterator") {
    MagicalContainer mc;

    // Add some elements
    for (int i = 1; i <= 5; ++i) {
        mc.addElement(i);
    }

    // Check that an exception is thrown when advancing an iterator past the end
    MagicalContainer::AscendingIterator it(mc);
    for (int i = 0; i < 5; ++i) {
        ++it;
    }
    CHECK_THROWS(++it);
}


TEST_CASE("Test iterator after removing elements") {
    MagicalContainer mc;

    // Add some elements
    for (int i = 1; i <= 5; ++i) {
        mc.addElement(i);
    }

    // Remove an element and check the remaining elements with an iterator
    mc.removeElement(3);
    MagicalContainer::AscendingIterator it(mc);
    CHECK(*it == 1); ++it;
    CHECK(*it == 2); ++it;
    CHECK(*it == 4); ++it;
    CHECK(*it == 5); ++it;
    CHECK(it.end() == it);
}

TEST_CASE("Test adding duplicate elements with iterators") {
    MagicalContainer mc;

    // Add duplicate elements
    mc.addElement(1);
    mc.addElement(1);

    // Check the size with an iterator
    MagicalContainer::AscendingIterator it(mc);
    CHECK(*it == 1); ++it;
    CHECK(*it == 1); ++it;
}

TEST_CASE("Test adding negative numbers with iterators") {
    MagicalContainer mc;

    // Add negative numbers
    mc.addElement(-1);
    mc.addElement(-2);

    // Check the values with an iterator
    MagicalContainer::AscendingIterator it(mc);
    CHECK(*it == -2); ++it;
    CHECK(*it == -1); ++it;
}

TEST_CASE("Test adding zero with iterators") {
    MagicalContainer mc;

    // Add zero
    mc.addElement(0);

    // Check the value with an iterator
    MagicalContainer::AscendingIterator it(mc);
    CHECK(*it == 0); ++it;
}

TEST_CASE("Test adding large numbers with iterators") {
    MagicalContainer mc;

    // Add large numbers
    mc.addElement(1000000);
    mc.addElement(2000000);

    // Check the values with an iterator
    MagicalContainer::AscendingIterator it(mc);
    CHECK(*it == 1000000); ++it;
    CHECK(*it == 2000000); ++it;
}

TEST_CASE("Test removing element not in container with iterators") {
    MagicalContainer mc;

    // Add some elements
    mc.addElement(1);
    mc.addElement(2);

    // Remove an element not in the container
    mc.removeElement(3);

    // Check that the size and elements did not change
    MagicalContainer::AscendingIterator it(mc);
    CHECK(*it == 1); ++it;
    CHECK(*it == 2); ++it;
}

TEST_CASE("Test AscendingIterator comparison operators") {
    ariel::MagicalContainer mc;

    mc.addElement(2);
    mc.addElement(3);
    mc.addElement(5);
    mc.addElement(7);
    mc.addElement(8);

    MagicalContainer::SideCrossIterator it1(mc);
    MagicalContainer::SideCrossIterator it2(mc);
    it1 = it1.begin();
    it2 = it2.begin();
    ++it2;
    ++it2; // Point it2 to the 3rd element

    CHECK_FALSE(it1 == it2); // They should not be equal
    CHECK(it1 != it2);       // They should be different
    CHECK(it1 < it2);        // it1 should be "smaller" (points to an earlier element)
    CHECK_FALSE(it1 > it2);  // it1 should not be "greater" (does not point to a later element)
}

TEST_CASE("Test SideCrossIterator comparison operators") {
    MagicalContainer mc;

    mc.addElement(2);
    mc.addElement(3);
    mc.addElement(5);
    mc.addElement(7);
    mc.addElement(8);

    MagicalContainer::SideCrossIterator it1(mc);
    MagicalContainer::SideCrossIterator it2(mc);
    it1 = it1.begin();
    it2 = it2.begin();
    ++it2;
    ++it2; // Point it2 to the 3rd element

    CHECK_FALSE(it1 == it2); // They should not be equal
    CHECK(it1 != it2);       // They should be different
    CHECK(it1 < it2);        // it1 should be "smaller" (points to an earlier element)
    CHECK_FALSE(it1 > it2);  // it1 should not be "greater" (does not point to a later element)
}

TEST_CASE("Test PrimeIterator comparison operators") {
    ariel::MagicalContainer mc;

    mc.addElement(2);
    mc.addElement(3);
    mc.addElement(5);
    mc.addElement(7);
    mc.addElement(8);

    MagicalContainer::SideCrossIterator it1(mc);
    MagicalContainer::SideCrossIterator it2(mc);
    it1 = it1.begin();
    it2 = it2.begin();
    ++it2;
    ++it2; // Point it2 to the 3rd element

    CHECK_FALSE(it1 == it2); // They should not be equal
    CHECK(it1 != it2);       // They should be different
    CHECK(it1 < it2);        // it1 should be "smaller" (points to an earlier element)
    CHECK_FALSE(it1 > it2);  // it1 should not be "greater" (does not point to a later element)
}

TEST_CASE("Test comparing between two different type iterators") {
    MagicalContainer mc;

    mc.addElement(2);
    mc.addElement(3);
    mc.addElement(5);
    mc.addElement(7);
    mc.addElement(8);

    MagicalContainer::SideCrossIterator it1(mc);
    MagicalContainer::PrimeIterator it2(mc);
    it1 = it1.begin();
    it2 = it2.begin();
    ++it2;
    ++it2; // Point it2 to the 3rd element

    CHECK_FALSE(*it1 == *it2); // They should not be equal
    CHECK(*it1 != *it2);       // They should be different
    CHECK(*it1 < *it2);        // it1 should be "smaller" (points to an earlier element)
    CHECK_FALSE(*it1 > *it2);  // it1 should not be "greater" (does not point to a later element)
}
