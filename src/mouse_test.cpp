#include "input/mouse/mouse.hpp"
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_test_macros.hpp>
#include <iostream>

TEST_CASE("Testing Linearity of Mouse Deltas", "[mouse]") {
    Mouse mouse(1.0);

    std::vector<std::tuple<double, double>> mouse_deltas = {{.25, .25}, {.1, .1}, {.3, 0}, {-.2, -.5}};

    double sens = 1;
    double accumulated_x = 0.0;
    double accumulated_y = 0.0;
    double yaw_delta_stepwise = 0.0;
    double pitch_delta_stepwise = 0.0;

    for (const auto &[dx, dy] : mouse_deltas) {
        auto [yaw, pitch] = mouse.get_yaw_pitch_deltas_from_mouse_deltas(dx, dy, sens);
        yaw_delta_stepwise += yaw;
        pitch_delta_stepwise += pitch;
        accumulated_x += dx;
        accumulated_y += dy;
    }

    auto [yaw_delta_once, pitch_delta_once] =
        mouse.get_yaw_pitch_deltas_from_mouse_deltas(accumulated_x, accumulated_y, sens);

    std::cout << std::setprecision(20);
    std::cout << "yaw_delta_stepwise: " << yaw_delta_stepwise << std::endl;
    std::cout << "yaw_delta_once:     " << yaw_delta_once << std::endl;
    std::cout << "pitch_delta_stepwise: " << pitch_delta_stepwise << std::endl;
    std::cout << "pitch_delta_once:     " << pitch_delta_once << std::endl;

    REQUIRE_THAT(yaw_delta_stepwise, Catch::Matchers::WithinRel(yaw_delta_once, 0.0001));
    REQUIRE_THAT(pitch_delta_stepwise, Catch::Matchers::WithinRel(pitch_delta_once, 0.0001));
}
