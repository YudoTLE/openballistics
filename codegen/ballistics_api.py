from itertools import product
from typing import NamedTuple

from .constants import INDENT
from .utils import format_lines
from .specs import Parameter


def ballistics_api(
    *,
    weapon_parameters: list[Parameter],
    class_name: str,
) -> list[str]:
    lines = [
        f"template <typename Derived>",
        f"struct ballistics<Derived, models::{class_name}<Derived>>",
        f"{{",
        *format_lines(
            [
                *_compute_final_position_api(weapon_parameters),
                *_compute_trajectory_api(weapon_parameters),
                *_optimize_time_of_flight_api(weapon_parameters),
                *_solve_time_of_flight_api(weapon_parameters),
                *_optimize_launch_direction_api(weapon_parameters),
                *_optimize_launch_angles_api(weapon_parameters),
                *_solve_launch_direction_api(weapon_parameters),
                *_solve_launch_angles_api(weapon_parameters),
                *_solve_launch_direction_and_time_of_flight_api(weapon_parameters),
                *_solve_launch_angles_and_time_of_flight_api(weapon_parameters),
            ],
            prefix=INDENT,
        ),
        f"}};",
    ]
    return lines


class Overload(NamedTuple):
    id: str
    parameter: str
    forwarded: str


DIRECTION_OVERLOADS = [
    Overload(
        id="direction",
        parameter="const vector3 &launch_direction",
        forwarded="launch_direction.stableNormalized()",
    ),
    Overload(
        id="angles",
        parameter="const angles &launch_angles",
        forwarded="launch_angles.to_unit_direction()",
    ),
]

VELOCITY_OVERLOADS = [
    Overload(
        id="moving",
        parameter="const vector3 &platform_velocity",
        forwarded="platform_velocity",
    ),
    Overload(id="stationary", parameter="__SKIP__", forwarded="vector3::Zero()"),
]


def _compute_final_position_api(weapon_parameters: list[Parameter]) -> list[str]:
    __ = INDENT
    lines: list[str] = []
    for direction_overload, velocity_overload in product(
        DIRECTION_OVERLOADS, VELOCITY_OVERLOADS
    ):
        lines += [
            f"[[nodiscard]] vector3 compute_final_position(",
            f"{__}const vector3 &launch_position,",
            f"{__}{direction_overload.parameter},",
            f"{__}{velocity_overload.parameter},",
            *_model_parameter_decls(weapon_parameters),
            f"{__}const scalar time_of_flight) const",
            f"{{",
            f"{__}return static_cast<const Derived *>(this)->compute_final_position_impl(",
            f"{__}{__}launch_position,",
            f"{__}{__}{direction_overload.forwarded},",
            f"{__}{__}{velocity_overload.forwarded},",
            f"{__}{__}{_model_parameter_args(weapon_parameters)},",
            f"{__}{__}time_of_flight);",
            f"}}",
        ]
    return lines


def _compute_trajectory_api(weapon_parameters: list[Parameter]) -> list[str]:
    __ = INDENT
    lines: list[str] = []
    for direction_overload in DIRECTION_OVERLOADS:
        for velocity_overload in VELOCITY_OVERLOADS:
            lines += [
                f"[[nodiscard]] std::vector<vector3> compute_trajectory(",
                f"{__}const vector3 &launch_position,",
                f"{__}{direction_overload.parameter},",
                f"{__}{velocity_overload.parameter},",
                *_model_parameter_decls(weapon_parameters),
                f"{__}const scalar time_of_flight,",
                f"{__}const scalar sample_interval = 0.2) const",
                f"{{",
                f"{__}return static_cast<const Derived *>(this)->compute_trajectory_impl(",
                f"{__}{__}launch_position,",
                f"{__}{__}{direction_overload.forwarded},",
                f"{__}{__}{velocity_overload.forwarded},",
                f"{__}{__}{_model_parameter_args(weapon_parameters)},",
                f"{__}{__}time_of_flight,",
                f"{__}{__}sample_interval);",
                f"}}",
            ]
    return lines


def _optimize_time_of_flight_api(weapon_parameters: list[Parameter]) -> list[str]:
    __ = INDENT
    lines: list[str] = []
    for direction_overload in DIRECTION_OVERLOADS:
        for velocity_overload in VELOCITY_OVERLOADS:
            lines += [
                f"template <typename TargetPosition>",
                f"[[nodiscard]] scalar optimize_time_of_flight(",
                f"{__}const vector3 &launch_position,",
                f"{__}{direction_overload.parameter},",
                f"{__}{velocity_overload.parameter},",
                f"{__}const TargetPosition &target_position,",
                *_model_parameter_decls(weapon_parameters),
                f"{__}const scalar min_time_of_flight,",
                f"{__}const scalar max_time_of_flight,",
                f"{__}const priority solution_priority = priority::earliest,",
                f"{__}const uint32_t max_iterations = 30) const",
                f"{{",
                f"{__}return static_cast<const Derived *>(this)->optimize_time_of_flight_impl(",
                f"{__}{__}launch_position,",
                f"{__}{__}{direction_overload.forwarded},",
                f"{__}{__}{velocity_overload.forwarded},",
                f"{__}{__}target_position,",
                f"{__}{__}{_model_parameter_args(weapon_parameters)},",
                f"{__}{__}min_time_of_flight,",
                f"{__}{__}max_time_of_flight,",
                f"{__}{__}solution_priority,",
                f"{__}{__}max_iterations);",
                f"}}",
            ]
    return lines


def _solve_time_of_flight_api(weapon_parameters: list[Parameter]) -> list[str]:
    __ = INDENT
    lines: list[str] = []
    for direction_overload in DIRECTION_OVERLOADS:
        for velocity_overload in VELOCITY_OVERLOADS:
            lines += [
                f"template <typename TargetPosition>",
                f"[[nodiscard]] std::optional<scalar> solve_time_of_flight(",
                f"{__}const vector3 &launch_position,",
                f"{__}{direction_overload.parameter},",
                f"{__}{velocity_overload.parameter},",
                f"{__}const TargetPosition &target_position,",
                *_model_parameter_decls(weapon_parameters),
                f"{__}const scalar min_time_of_flight,",
                f"{__}const scalar max_time_of_flight,",
                f"{__}const scalar miss_distance_threshold = 1.0,",
                f"{__}const priority solution_priority = priority::earliest,",
                f"{__}const uint32_t max_iterations = 30) const",
                f"{{",
                f"{__}return static_cast<const Derived *>(this)->solve_time_of_flight_impl(",
                f"{__}{__}launch_position,",
                f"{__}{__}{direction_overload.forwarded},",
                f"{__}{__}{velocity_overload.forwarded},",
                f"{__}{__}target_position,",
                f"{__}{__}{_model_parameter_args(weapon_parameters)},",
                f"{__}{__}min_time_of_flight,",
                f"{__}{__}max_time_of_flight,",
                f"{__}{__}miss_distance_threshold,",
                f"{__}{__}solution_priority,",
                f"{__}{__}max_iterations);",
                f"}}",
            ]
    return lines


def _optimize_launch_direction_api(weapon_parameters: list[Parameter]) -> list[str]:
    __ = INDENT
    lines: list[str] = []
    for velocity_overload in VELOCITY_OVERLOADS:
        lines += [
            f"template <typename TargetPosition>",
            f"[[nodiscard]] vector3 optimize_launch_direction(",
            f"{__}const vector3 &launch_position,",
            f"{__}{velocity_overload.parameter},",
            f"{__}const TargetPosition &target_position,",
            *_model_parameter_decls(weapon_parameters),
            f"{__}const scalar time_of_flight,",
            f"{__}const uint32_t max_iterations = 25) const",
            f"{{",
            f"{__}return static_cast<const Derived *>(this)->optimize_launch_direction_impl(",
            f"{__}{__}launch_position,",
            f"{__}{__}{velocity_overload.forwarded},",
            f"{__}{__}target_position,",
            f"{__}{__}{_model_parameter_args(weapon_parameters)},",
            f"{__}{__}time_of_flight,",
            f"{__}{__}max_iterations);",
            f"}}",
        ]
    return lines


def _optimize_launch_angles_api(weapon_parameters: list[Parameter]) -> list[str]:
    __ = INDENT
    lines: list[str] = []
    for velocity_overload in VELOCITY_OVERLOADS:
        lines += [
            f"template <typename TargetPosition>",
            f"[[nodiscard]] angles optimize_launch_angles(",
            f"{__}const vector3 &launch_position,",
            f"{__}{velocity_overload.parameter},",
            f"{__}const TargetPosition &target_position,",
            *_model_parameter_decls(weapon_parameters),
            f"{__}const scalar time_of_flight,",
            f"{__}const uint32_t max_iterations = 25) const",
            f"{{",
            f"{__}return angles::from_unit_direction(",
            f"{__}{__}static_cast<const Derived *>(this)->optimize_launch_direction_impl(",
            f"{__}{__}{__}launch_position,",
            f"{__}{__}{__}{velocity_overload.forwarded},",
            f"{__}{__}{__}target_position,",
            f"{__}{__}{__}{_model_parameter_args(weapon_parameters)},",
            f"{__}{__}{__}time_of_flight,",
            f"{__}{__}{__}max_iterations));",
            f"}}",
        ]
    return lines


def _solve_launch_direction_api(weapon_parameters: list[Parameter]) -> list[str]:
    __ = INDENT
    lines: list[str] = []
    for velocity_overload in VELOCITY_OVERLOADS:
        lines += [
            f"template <typename TargetPosition>",
            f"[[nodiscard]] std::optional<vector3> solve_launch_direction(",
            f"{__}const vector3 &launch_position,",
            f"{__}{velocity_overload.parameter},",
            f"{__}const TargetPosition &target_position,",
            *_model_parameter_decls(weapon_parameters),
            f"{__}const scalar time_of_flight,",
            f"{__}const scalar miss_distance_threshold = 1.0,",
            f"{__}const uint32_t max_iterations = 25) const",
            f"{{",
            f"{__}return static_cast<const Derived *>(this)->solve_launch_direction_impl(",
            f"{__}{__}launch_position,",
            f"{__}{__}{velocity_overload.forwarded},",
            f"{__}{__}target_position,",
            f"{__}{__}{_model_parameter_args(weapon_parameters)},",
            f"{__}{__}time_of_flight,",
            f"{__}{__}miss_distance_threshold,",
            f"{__}{__}max_iterations);",
            f"}}",
        ]
    return lines


def _solve_launch_angles_api(weapon_parameters: list[Parameter]) -> list[str]:
    __ = INDENT
    lines: list[str] = []
    for velocity_overload in VELOCITY_OVERLOADS:
        lines += [
            f"template <typename TargetPosition>",
            f"[[nodiscard]] std::optional<angles> solve_launch_angles(",
            f"{__}const vector3 &launch_position,",
            f"{__}{velocity_overload.parameter},",
            f"{__}const TargetPosition &target_position,",
            *_model_parameter_decls(weapon_parameters),
            f"{__}const scalar time_of_flight,",
            f"{__}const scalar miss_distance_threshold = 1.0,",
            f"{__}const uint32_t max_iterations = 25) const",
            f"{{",
            f"{__}std::optional<vector3> launch_direction = static_cast<const Derived *>(this)->solve_launch_direction_impl(",
            f"{__}{__}launch_position,",
            f"{__}{__}{velocity_overload.forwarded},",
            f"{__}{__}target_position,",
            f"{__}{__}{_model_parameter_args(weapon_parameters)},",
            f"{__}{__}time_of_flight,",
            f"{__}{__}miss_distance_threshold,",
            f"{__}{__}max_iterations);",
            f"{__}if (!launch_direction.has_value())",
            f"{__}{__}return std::nullopt;",
            f"{__}return angles::from_unit_direction(launch_direction.value());",
            f"}}",
        ]
    return lines


def _solve_launch_direction_and_time_of_flight_api(
    weapon_parameters: list[Parameter],
) -> list[str]:
    __ = INDENT
    lines: list[str] = []
    for velocity_overload in VELOCITY_OVERLOADS:
        lines += [
            f"template <typename TargetPosition>",
            f"[[nodiscard]] std::optional<std::pair<vector3, scalar>> solve_launch_direction_and_time_of_flight(",
            f"{__}const vector3 &launch_position,",
            f"{__}{velocity_overload.parameter},",
            f"{__}TargetPosition &&target_position,",
            *_model_parameter_decls(weapon_parameters),
            f"{__}const scalar min_time_of_flight,",
            f"{__}const scalar max_time_of_flight,",
            f"{__}const scalar miss_distance_threshold = 1.0,",
            f"{__}const priority solution_priority = priority::earliest,",
            f"{__}const scalar time_of_flight_segment_size = 0.5,",
            f"{__}const uint32_t time_of_flight_max_iterations = 30,",
            f"{__}const uint32_t launch_direction_max_iterations = 25) const",
            f"{{",
            f"{__}return static_cast<const Derived *>(this)->solve_launch_direction_and_time_of_flight_impl(",
            f"{__}{__}launch_position,",
            f"{__}{__}{velocity_overload.forwarded},",
            f"{__}{__}target_position,",
            f"{__}{__}{_model_parameter_args(weapon_parameters)},",
            f"{__}{__}min_time_of_flight,",
            f"{__}{__}max_time_of_flight,",
            f"{__}{__}miss_distance_threshold,",
            f"{__}{__}solution_priority,",
            f"{__}{__}time_of_flight_segment_size,",
            f"{__}{__}time_of_flight_max_iterations,",
            f"{__}{__}launch_direction_max_iterations);",
            f"}}",
        ]
    return lines


def _solve_launch_angles_and_time_of_flight_api(
    weapon_parameters: list[Parameter],
) -> list[str]:
    __ = INDENT
    lines: list[str] = []
    for velocity_overload in VELOCITY_OVERLOADS:
        lines += [
            f"template <typename TargetPosition>",
            f"[[nodiscard]] std::optional<std::pair<angles, scalar>> solve_launch_angles_and_time_of_flight(",
            f"{__}const vector3 &launch_position,",
            f"{__}{velocity_overload.parameter},",
            f"{__}TargetPosition &&target_position,",
            *_model_parameter_decls(weapon_parameters),
            f"{__}const scalar min_time_of_flight,",
            f"{__}const scalar max_time_of_flight,",
            f"{__}const scalar miss_distance_threshold = 1.0,",
            f"{__}const priority solution_priority = priority::earliest,",
            f"{__}const scalar time_of_flight_segment_size = 0.5,",
            f"{__}const uint32_t time_of_flight_max_iterations = 30,",
            f"{__}const uint32_t launch_direction_max_iterations = 25) const",
            f"{{",
            f"{__}auto result = static_cast<const Derived *>(this)->solve_launch_direction_and_time_of_flight_impl(",
            f"{__}{__}launch_position,",
            f"{__}{__}{velocity_overload.forwarded},",
            f"{__}{__}target_position,",
            f"{__}{__}{_model_parameter_args(weapon_parameters)},",
            f"{__}{__}min_time_of_flight,",
            f"{__}{__}max_time_of_flight,",
            f"{__}{__}miss_distance_threshold,",
            f"{__}{__}solution_priority,",
            f"{__}{__}time_of_flight_segment_size,",
            f"{__}{__}time_of_flight_max_iterations,",
            f"{__}{__}launch_direction_max_iterations);",
            f"{__}if (!result.has_value())",
            f"{__}{__}return std::nullopt;",
            f"{__}return std::make_pair(angles::from_unit_direction(result->first), result->second);",
            f"}}",
        ]
    return lines


def _model_parameter_decls(
    weapon_parameters: list[Parameter],
) -> list[str]:
    return [
        f"{INDENT}{f'{p.qualifier} ' if p.qualifier else ''}{p.type} {p.name},"
        for p in weapon_parameters
    ]


def _model_parameter_args(weapon_parameters: list[Parameter]) -> str:
    return "{" + ", ".join(p.name for p in weapon_parameters) + "}"
