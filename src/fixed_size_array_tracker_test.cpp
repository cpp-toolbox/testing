#include "utility/fixed_size_array_tracker/fixed_size_array_tracker.hpp"
#include "utility/print_utils/print_utils.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

TEST_CASE("Test Space Availability and Compactify", "[fixed_size_array_tracker]") {
    FixedSizeArrayTracker tracker(10, false);

    tracker.add_metadata(1, 0, 3);
    tracker.add_metadata(2, 3, 2);
    tracker.add_metadata(3, 5, 4);

    /*
     *  111225555
     *  0123456789
     */

    REQUIRE(tracker.get_metadata(1) == std::make_pair(0u, 3u));
    REQUIRE(tracker.get_metadata(2) == std::make_pair(3u, 2u));
    REQUIRE(tracker.get_metadata(3) == std::make_pair(5u, 4u));
    REQUIRE(tracker.get_metadata(4) == std::nullopt);

    // only one spot left, check this.
    REQUIRE(tracker.find_contiguous_space(1) == 9u);
    REQUIRE(tracker.find_contiguous_space(2) == std::nullopt);

    tracker.remove_metadata(2);

    /*
     *  111  5555
     *  0123456789
     *
     *  now there are three gaps
     */

    // there is contiguous space for 2 not three
    REQUIRE(tracker.find_contiguous_space(2) == 3u);
    REQUIRE(tracker.find_contiguous_space(3) == std::nullopt);

    // but if we compact it, there is space
    tracker.compact();

    /*
     * 3333111
     * 0123456789
     */
    REQUIRE(tracker.find_contiguous_space(3) == 7u);
}

TEST_CASE("Test Adding Overlapping Metadata", "[fixed_size_array_tracker]") {
    FixedSizeArrayTracker tracker(10, false);
    tracker.add_metadata(1, 0, 5);
    tracker.add_metadata(2, 3, 4);

    REQUIRE(tracker.get_metadata(2) == std::nullopt);
}

TEST_CASE("Test Adding Out of Bounds Metadata", "[fixed_size_array_tracker]") {
    FixedSizeArrayTracker tracker(10, false);
    tracker.add_metadata(1, 8, 3); // should be rejected
    REQUIRE(tracker.get_metadata(1) == std::nullopt);
}

TEST_CASE("Test Removing Nonexistent Metadata", "[fixed_size_array_tracker]") {
    FixedSizeArrayTracker tracker(10, false);
    tracker.remove_metadata(99); // should not cause issues
    REQUIRE(tracker.get_metadata(99) == std::nullopt);
}

TEST_CASE("Test Compacting with Gaps", "[fixed_size_array_tracker]") {
    FixedSizeArrayTracker tracker(10, false);
    tracker.add_metadata(1, 0, 3);
    tracker.add_metadata(2, 4, 3);
    tracker.add_metadata(3, 8, 2);
    tracker.remove_metadata(2);
    tracker.compact();

    REQUIRE(tracker.get_metadata(1) == std::make_pair(2u, 3u));
    REQUIRE(tracker.get_metadata(3) == std::make_pair(0u, 2u));
}

TEST_CASE("Test Large Contiguous Space Allocation", "[fixed_size_array_tracker]") {
    FixedSizeArrayTracker tracker(30, false);
    tracker.add_metadata(1, 0, 5);
    tracker.add_metadata(2, 6, 5);
    tracker.add_metadata(3, 12, 5);

    REQUIRE(tracker.find_contiguous_space(10) == 17u);
}

TEST_CASE("Benchmark FixedSizeArrayTracker with Large Dataset", "[benchmark]") {
    const unsigned int size = 100'000;

    BENCHMARK("Add Large Number of Metadata") {
        FixedSizeArrayTracker tracker(size, false);
        for (int i = 0; i < 1000; ++i) {
            unsigned int start = i * 100;
            unsigned int length = 100;
            tracker.add_metadata(i, start, length);
        }
        return tracker.get_all_metadata().size();
    };

    BENCHMARK("Remove Large Number of Metadata") {
        FixedSizeArrayTracker tracker(size, false);
        for (int i = 0; i < 1000; ++i) {
            unsigned int start = i * 100;
            unsigned int length = 100;
            tracker.add_metadata(i, start, length);
        }

        for (int i = 0; i < 1000; ++i) {
            tracker.remove_metadata(i);
        }

        return tracker.get_all_metadata().size();
    };

    BENCHMARK("Find Contiguous Space with Small Gaps") {
        FixedSizeArrayTracker tracker(size, false);

        // insert metadata with gaps smaller than 100
        for (int i = 0; i < 500; ++i) {
            unsigned int start = i * 50;
            unsigned int length = 50;
            tracker.add_metadata(i, start, length);
        }

        return tracker.find_contiguous_space(100).has_value();
    };

    BENCHMARK("Compact Array After Large Number of Entries") {
        FixedSizeArrayTracker tracker(size, false); // create a new tracker for each benchmark
        for (int i = 0; i < 1000; ++i) {
            unsigned int start = i * 100;
            unsigned int length = 100;
            tracker.add_metadata(i, start, length);
        }

        tracker.compact();
        return tracker.get_all_metadata().size();
    };
}
