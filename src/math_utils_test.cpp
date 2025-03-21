#include "utility/math_utils/math_utils.hpp"
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_test_macros.hpp>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/constants.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <random>
#include <iostream>

TEST_CASE("Testing Yaw Pitch Extraction", "[math_utils]") {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    for (int i = 0; i < 100; ++i) {
        glm::vec3 random_vector = glm::normalize(glm::vec3(dist(gen), dist(gen), dist(gen)));
        auto [yaw, pitch] = math_utils::extract_yaw_pitch(random_vector);

        float yaw_rad = glm::radians(yaw);
        float pitch_rad = glm::radians(pitch);

        glm::vec3 reconstructed_vector = glm::normalize(glm::vec3(
            std::sin(yaw_rad) * std::cos(pitch_rad), std::sin(pitch_rad), std::cos(yaw_rad) * std::cos(pitch_rad)));

        REQUIRE_THAT(reconstructed_vector.x, Catch::Matchers::WithinRel(random_vector.x, 0.0001));
        REQUIRE_THAT(reconstructed_vector.y, Catch::Matchers::WithinRel(random_vector.y, 0.0001));
        REQUIRE_THAT(reconstructed_vector.z, Catch::Matchers::WithinRel(random_vector.z, 0.0001));
    }
}
