#include "utility/transform/transform.hpp"

#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_test_macros.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include <iostream>
#include <cmath>

TEST_CASE("Testing Rotation Decomposition", "[transform]") {
    // Initial rotation values
    glm::vec3 initial_rotation(0.5f, 0.25f, 0.75f); // In radians or turns
    Transform transform;

    // Set rotation only (no position or scale)
    transform.set_rotation(initial_rotation);

    // Get the transform matrix from the object
    glm::mat4 transform_matrix = transform.get_transform_matrix();

    // Decompose the matrix
    glm::vec3 decomposed_position, decomposed_scale, decomposed_skew;
    glm::quat decomposed_orientation;
    glm::vec4 decomposed_perspective;

    glm::decompose(transform_matrix, decomposed_scale, decomposed_orientation, decomposed_position, decomposed_skew,
                   decomposed_perspective);

    // Convert quaternion to Euler angles (pitch, yaw, roll)
    glm::vec3 decomposed_rotation = glm::eulerAngles(decomposed_orientation);
    // to turns
    decomposed_rotation /= (2.0f * glm::pi<float>());

    // Print the values for debugging (optional)
    std::cout << "Decomposed Rotation: " << decomposed_rotation.x << ", " << decomposed_rotation.y << ", "
              << decomposed_rotation.z << std::endl;

    // Assertions to verify the correctness of the rotation decomposition
    REQUIRE_THAT(decomposed_rotation.x, Catch::Matchers::WithinRel(initial_rotation.x, 0.0001f));
    REQUIRE_THAT(decomposed_rotation.y, Catch::Matchers::WithinRel(initial_rotation.y, 0.0001f));
    REQUIRE_THAT(decomposed_rotation.z, Catch::Matchers::WithinRel(initial_rotation.z, 0.0001f));
}

TEST_CASE("Testing Translation Decomposition", "[transform]") {
    // Initial position values
    glm::vec3 initial_position(1.0f, 2.0f, 3.0f);
    Transform transform;

    // Set position only (no rotation or scale)
    transform.set_position(initial_position);

    // Get the transform matrix from the object
    glm::mat4 transform_matrix = transform.get_transform_matrix();

    // Decompose the matrix
    glm::vec3 decomposed_position, decomposed_scale, decomposed_skew;
    glm::quat decomposed_orientation;
    glm::vec4 decomposed_perspective;

    glm::decompose(transform_matrix, decomposed_scale, decomposed_orientation, decomposed_position, decomposed_skew,
                   decomposed_perspective);

    // Print the values for debugging (optional)
    std::cout << "Decomposed Position: " << decomposed_position.x << ", " << decomposed_position.y << ", "
              << decomposed_position.z << std::endl;

    // Assertions to verify the correctness of the translation decomposition
    REQUIRE_THAT(decomposed_position.x, Catch::Matchers::WithinRel(initial_position.x, 0.0001f));
    REQUIRE_THAT(decomposed_position.y, Catch::Matchers::WithinRel(initial_position.y, 0.0001f));
    REQUIRE_THAT(decomposed_position.z, Catch::Matchers::WithinRel(initial_position.z, 0.0001f));
}

TEST_CASE("Testing Scale Decomposition", "[transform]") {
    // Initial scale values
    glm::vec3 initial_scale(2.0f, 3.0f, 1.0f);
    Transform transform;

    // Set scale only (no position or rotation)
    transform.set_scale(initial_scale);

    // Get the transform matrix from the object
    glm::mat4 transform_matrix = transform.get_transform_matrix();

    // Decompose the matrix
    glm::vec3 decomposed_position, decomposed_scale, decomposed_skew;
    glm::quat decomposed_orientation;
    glm::vec4 decomposed_perspective;

    glm::decompose(transform_matrix, decomposed_scale, decomposed_orientation, decomposed_position, decomposed_skew,
                   decomposed_perspective);

    // Print the values for debugging (optional)
    std::cout << "Decomposed Scale: " << decomposed_scale.x << ", " << decomposed_scale.y << ", " << decomposed_scale.z
              << std::endl;

    // Assertions to verify the correctness of the scale decomposition
    REQUIRE_THAT(decomposed_scale.x, Catch::Matchers::WithinRel(initial_scale.x, 0.0001f));
    REQUIRE_THAT(decomposed_scale.y, Catch::Matchers::WithinRel(initial_scale.y, 0.0001f));
    REQUIRE_THAT(decomposed_scale.z, Catch::Matchers::WithinRel(initial_scale.z, 0.0001f));
}

TEST_CASE("Testing Transform Matrix Decomposition", "[transform]") {
    // Initial values to set in the Transform object
    glm::vec3 initial_position(1.0f, 2.0f, 3.0f);
    glm::vec3 initial_rotation(0.5f, 0.25f, 0.75f); // In radians or turns
    glm::vec3 initial_scale(2.0f, 3.0f, 1.0f);

    Transform transform;

    // Set position, rotation, and scale
    transform.set_position(initial_position);
    transform.set_rotation(initial_rotation);
    transform.set_scale(initial_scale);

    // Get the transform matrix from the object
    glm::mat4 transform_matrix = transform.get_transform_matrix();

    // Decompose the matrix
    glm::vec3 decomposed_position, decomposed_scale, decomposed_skew;
    glm::quat decomposed_orientation;
    glm::vec4 decomposed_perspective;

    // Call glm::decompose correctly with the right parameters
    glm::decompose(transform_matrix, decomposed_scale, decomposed_orientation, decomposed_position, decomposed_skew,
                   decomposed_perspective);

    // Convert quaternion to Euler angles (pitch, yaw, roll)
    glm::vec3 decomposed_rotation = glm::eulerAngles(decomposed_orientation);
    // to turns
    decomposed_rotation /= (2.0f * glm::pi<float>());

    // Print the values for debugging (optional)
    std::cout << "Decomposed Position: " << decomposed_position.x << ", " << decomposed_position.y << ", "
              << decomposed_position.z << std::endl;
    std::cout << "Decomposed Rotation: " << decomposed_rotation.x << ", " << decomposed_rotation.y << ", "
              << decomposed_rotation.z << std::endl;
    std::cout << "Decomposed Scale: " << decomposed_scale.x << ", " << decomposed_scale.y << ", " << decomposed_scale.z
              << std::endl;

    // Assertions to verify the correctness of the decomposition using WithinRel
    REQUIRE_THAT(decomposed_position.x, Catch::Matchers::WithinRel(initial_position.x, 0.0001f));
    REQUIRE_THAT(decomposed_position.y, Catch::Matchers::WithinRel(initial_position.y, 0.0001f));
    REQUIRE_THAT(decomposed_position.z, Catch::Matchers::WithinRel(initial_position.z, 0.0001f));

    REQUIRE_THAT(decomposed_rotation.x, Catch::Matchers::WithinRel(initial_rotation.x, 0.0001f));
    REQUIRE_THAT(decomposed_rotation.y, Catch::Matchers::WithinRel(initial_rotation.y, 0.0001f));
    REQUIRE_THAT(decomposed_rotation.z, Catch::Matchers::WithinRel(initial_rotation.z, 0.0001f));

    REQUIRE_THAT(decomposed_scale.x, Catch::Matchers::WithinRel(initial_scale.x, 0.0001f));
    REQUIRE_THAT(decomposed_scale.y, Catch::Matchers::WithinRel(initial_scale.y, 0.0001f));
    REQUIRE_THAT(decomposed_scale.z, Catch::Matchers::WithinRel(initial_scale.z, 0.0001f));
}
