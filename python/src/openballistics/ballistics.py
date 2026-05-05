from __future__ import annotations

from collections.abc import Callable
from typing import overload, Literal

import numpy as np
from numpy.typing import ArrayLike, NDArray

from .integrator import RK4, RKDP5
from .environment import RealisticEnvironment
from .projectile import RealisticProjectile

from ._core import (  # type: ignore[reportMissingModuleSource]
    Angles,
    PMRK4RealisticEnvironmentRealisticProjectile as _PMRK4RealisticEnvironmentRealisticProjectile,
    PMRKDP5RealisticEnvironmentRealisticProjectile as _PMRKDP5RealisticEnvironmentRealisticProjectile,
    MPMRK4RealisticEnvironmentRealisticProjectile as _MPMRK4RealisticEnvironmentRealisticProjectile,
    MPMRKDP5RealisticEnvironmentRealisticProjectile as _MPMRKDP5RealisticEnvironmentRealisticProjectile,
)

_Vec3 = NDArray[np.float64]


class PointMassBallistics:
    def __init__(
        self,
        *,
        integrator: RK4 | RKDP5 | Literal["rk4", "rkdp5"] = "rkdp5",
        environment: RealisticEnvironment | Literal["realistic"] = "realistic",
        projectile: RealisticProjectile | Literal["realistic"] = "realistic",
    ) -> None:
        if integrator == "rk4":
            integrator = RK4()
        elif integrator == "rkdp5":
            integrator = RKDP5()
        if environment == "realistic":
            environment = RealisticEnvironment()
        if projectile == "realistic":
            projectile = RealisticProjectile()

        if isinstance(integrator, RK4):
            self._core = _PMRK4RealisticEnvironmentRealisticProjectile()
        elif isinstance(integrator, RKDP5):  # type: ignore
            self._core = _PMRKDP5RealisticEnvironmentRealisticProjectile()
        else:
            raise TypeError("Unsupported integrator")
        if isinstance(environment, RealisticEnvironment):  # type: ignore
            self._core.environment = environment  # type: ignore
        else:
            raise TypeError("Unsupported environment")
        if isinstance(projectile, RealisticProjectile):  # type: ignore
            self._core.projectile = projectile  # type: ignore
        else:
            raise TypeError("Unsupported projectile")

    @overload
    def compute_final_position(
        self,
        launch_position: ArrayLike,
        launch_direction: ArrayLike,
        platform_velocity: ArrayLike,
        muzzle_velocity: float,
        time_of_flight: float,
    ) -> _Vec3: ...

    @overload
    def compute_final_position(
        self,
        launch_position: ArrayLike,
        launch_direction: Angles,
        platform_velocity: ArrayLike,
        muzzle_velocity: float,
        time_of_flight: float,
    ) -> _Vec3: ...

    def compute_final_position(
        self,
        launch_position: ArrayLike,
        launch_direction: ArrayLike | Angles,
        platform_velocity: ArrayLike,
        muzzle_velocity: float,
        time_of_flight: float,
    ) -> _Vec3:
        _launch_position = np.asarray(launch_position, dtype=np.float64)
        _platform_velocity = np.asarray(platform_velocity, dtype=np.float64)
        if isinstance(launch_direction, Angles):
            return self._core.compute_final_position(
                _launch_position,
                launch_direction,
                _platform_velocity,
                float(muzzle_velocity),
                float(time_of_flight),
            )
        else:
            _launch_direction = np.asarray(launch_direction, dtype=np.float64)
            return self._core.compute_final_position(
                _launch_position,
                _launch_direction,
                _platform_velocity,
                float(muzzle_velocity),
                float(time_of_flight),
            )

    @overload
    def compute_trajectory(
        self,
        launch_position: ArrayLike,
        launch_direction: ArrayLike,
        platform_velocity: ArrayLike,
        muzzle_velocity: float,
        start_time: float,
        end_time: float,
        *,
        sample_interval: float = 0.2,
    ) -> list[_Vec3]: ...

    @overload
    def compute_trajectory(
        self,
        launch_position: ArrayLike,
        launch_direction: Angles,
        platform_velocity: ArrayLike,
        muzzle_velocity: float,
        start_time: float,
        end_time: float,
        *,
        sample_interval: float = 0.2,
    ) -> list[_Vec3]: ...

    def compute_trajectory(
        self,
        launch_position: ArrayLike,
        launch_direction: ArrayLike | Angles,
        platform_velocity: ArrayLike,
        muzzle_velocity: float,
        start_time: float,
        end_time: float,
        *,
        sample_interval: float = 0.2,
    ) -> list[_Vec3]:
        _launch_position = np.asarray(launch_position, dtype=np.float64)
        _platform_velocity = np.asarray(platform_velocity, dtype=np.float64)
        if isinstance(launch_direction, Angles):
            return self._core.compute_trajectory(
                _launch_position,
                launch_direction,
                _platform_velocity,
                float(muzzle_velocity),
                float(start_time),
                float(end_time),
                float(sample_interval),
            )
        else:
            _launch_direction = np.asarray(launch_direction, dtype=np.float64)
            return self._core.compute_trajectory(
                _launch_position,
                _launch_direction,
                _platform_velocity,
                float(muzzle_velocity),
                float(start_time),
                float(end_time),
                float(sample_interval),
            )

    def optimize_launch_direction(
        self,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike,
        target_position: ArrayLike,
        muzzle_velocity: float,
        time_of_flight: float,
        *,
        max_launch_direction_optimizer_iterations: int = 25,
    ) -> _Vec3:
        return self._core.optimize_launch_direction(
            np.asarray(launch_position, dtype=np.float64),
            np.asarray(platform_velocity, dtype=np.float64),
            np.asarray(target_position, dtype=np.float64),
            float(muzzle_velocity),
            float(time_of_flight),
            int(max_launch_direction_optimizer_iterations),
        )

    def optimize_launch_angles(
        self,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike,
        target_position: ArrayLike,
        muzzle_velocity: float,
        time_of_flight: float,
        *,
        max_launch_direction_optimizer_iterations: int = 25,
    ) -> Angles:
        return self._core.optimize_launch_angles(
            np.asarray(launch_position, dtype=np.float64),
            np.asarray(platform_velocity, dtype=np.float64),
            np.asarray(target_position, dtype=np.float64),
            float(muzzle_velocity),
            float(time_of_flight),
            int(max_launch_direction_optimizer_iterations),
        )

    def solve_launch_direction(
        self,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike,
        target_position: ArrayLike,
        muzzle_velocity: float,
        time_of_flight: float,
        *,
        miss_distance_threshold: float = 1.0,
        max_launch_direction_optimizer_iterations: int = 25,
    ) -> _Vec3 | None:
        return self._core.solve_launch_direction(
            np.asarray(launch_position, dtype=np.float64),
            np.asarray(platform_velocity, dtype=np.float64),
            np.asarray(target_position, dtype=np.float64),
            float(muzzle_velocity),
            float(time_of_flight),
            float(miss_distance_threshold),
            int(max_launch_direction_optimizer_iterations),
        )

    def solve_launch_angles(
        self,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike,
        target_position: ArrayLike,
        muzzle_velocity: float,
        time_of_flight: float,
        *,
        miss_distance_threshold: float = 1.0,
        max_launch_direction_optimizer_iterations: int = 25,
    ) -> Angles | None:
        return self._core.solve_launch_angles(
            np.asarray(launch_position, dtype=np.float64),
            np.asarray(platform_velocity, dtype=np.float64),
            np.asarray(target_position, dtype=np.float64),
            float(muzzle_velocity),
            float(time_of_flight),
            float(miss_distance_threshold),
            int(max_launch_direction_optimizer_iterations),
        )

    def solve_launch_direction_and_time_of_flight(
        self,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike,
        target_motion: Callable[[float], _Vec3],
        muzzle_velocity: float,
        min_time_of_flight: float,
        max_time_of_flight: float,
        *,
        miss_distance_threshold: float = 1.0,
        segment_size: float = 0.5,
        max_time_of_flight_optimizer_iterations: int = 30,
        max_launch_direction_optimizer_iterations: int = 25,
    ) -> tuple[_Vec3, float] | None:
        return self._core.solve_launch_direction_and_time_of_flight(
            np.asarray(launch_position, dtype=np.float64),
            np.asarray(platform_velocity, dtype=np.float64),
            target_motion,
            float(muzzle_velocity),
            float(min_time_of_flight),
            float(max_time_of_flight),
            float(miss_distance_threshold),
            float(segment_size),
            int(max_time_of_flight_optimizer_iterations),
            int(max_launch_direction_optimizer_iterations),
        )

    def solve_launch_angles_and_time_of_flight(
        self,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike,
        target_motion: Callable[[float], _Vec3],
        muzzle_velocity: float,
        min_time_of_flight: float,
        max_time_of_flight: float,
        *,
        miss_distance_threshold: float = 1.0,
        segment_size: float = 0.5,
        max_time_of_flight_optimizer_iterations: int = 30,
        max_launch_direction_optimizer_iterations: int = 25,
    ) -> tuple[Angles, float] | None:
        return self._core.solve_launch_angles_and_time_of_flight(
            np.asarray(launch_position, dtype=np.float64),
            np.asarray(platform_velocity, dtype=np.float64),
            target_motion,
            float(muzzle_velocity),
            float(min_time_of_flight),
            float(max_time_of_flight),
            float(miss_distance_threshold),
            float(segment_size),
            int(max_time_of_flight_optimizer_iterations),
            int(max_launch_direction_optimizer_iterations),
        )


class ModifiedPointMassBallistics:
    def __init__(
        self,
        *,
        integrator: RK4 | RKDP5 | Literal["rk4", "rkdp5"] = "rkdp5",
        environment: RealisticEnvironment | Literal["realistic"] = "realistic",
        projectile: RealisticProjectile | Literal["realistic"] = "realistic",
    ) -> None:
        if integrator == "rk4":
            integrator = RK4()
        elif integrator == "rkdp5":
            integrator = RKDP5()
        if environment == "realistic":
            environment = RealisticEnvironment()
        if projectile == "realistic":
            projectile = RealisticProjectile()

        if isinstance(integrator, RK4):
            self._core = _MPMRK4RealisticEnvironmentRealisticProjectile()
        elif isinstance(integrator, RKDP5):  # type: ignore
            self._core = _MPMRKDP5RealisticEnvironmentRealisticProjectile()
        else:
            raise TypeError("Unsupported integrator")
        if isinstance(environment, RealisticEnvironment):  # type: ignore
            self._core.environment = environment  # type: ignore
        else:
            raise TypeError("Unsupported environment")
        if isinstance(projectile, RealisticProjectile):  # type: ignore
            self._core.projectile = projectile  # type: ignore
        else:
            raise TypeError("Unsupported projectile")

    @overload
    def compute_final_position(
        self,
        launch_position: ArrayLike,
        launch_direction: ArrayLike,
        platform_velocity: ArrayLike,
        muzzle_velocity: float,
        rifling_twist: float,
        time_of_flight: float,
    ) -> _Vec3: ...

    @overload
    def compute_final_position(
        self,
        launch_position: ArrayLike,
        launch_direction: Angles,
        platform_velocity: ArrayLike,
        muzzle_velocity: float,
        rifling_twist: float,
        time_of_flight: float,
    ) -> _Vec3: ...

    def compute_final_position(
        self,
        launch_position: ArrayLike,
        launch_direction: ArrayLike | Angles,
        platform_velocity: ArrayLike,
        muzzle_velocity: float,
        rifling_twist: float,
        time_of_flight: float,
    ) -> _Vec3:
        _launch_position = np.asarray(launch_position, dtype=np.float64)
        _platform_velocity = np.asarray(platform_velocity, dtype=np.float64)
        if isinstance(launch_direction, Angles):
            return self._core.compute_final_position(
                _launch_position,
                launch_direction,
                _platform_velocity,
                float(muzzle_velocity),
                float(rifling_twist),
                float(time_of_flight),
            )
        else:
            _launch_direction = np.asarray(launch_direction, dtype=np.float64)
            return self._core.compute_final_position(
                _launch_position,
                _launch_direction,
                _platform_velocity,
                float(muzzle_velocity),
                float(rifling_twist),
                float(time_of_flight),
            )

    @overload
    def compute_trajectory(
        self,
        launch_position: ArrayLike,
        launch_direction: ArrayLike,
        platform_velocity: ArrayLike,
        muzzle_velocity: float,
        rifling_twist: float,
        start_time: float,
        end_time: float,
        *,
        sample_interval: float = 0.2,
    ) -> list[_Vec3]: ...

    @overload
    def compute_trajectory(
        self,
        launch_position: ArrayLike,
        launch_direction: Angles,
        platform_velocity: ArrayLike,
        muzzle_velocity: float,
        rifling_twist: float,
        start_time: float,
        end_time: float,
        *,
        sample_interval: float = 0.2,
    ) -> list[_Vec3]: ...

    def compute_trajectory(
        self,
        launch_position: ArrayLike,
        launch_direction: ArrayLike | Angles,
        platform_velocity: ArrayLike,
        muzzle_velocity: float,
        rifling_twist: float,
        start_time: float,
        end_time: float,
        *,
        sample_interval: float = 0.2,
    ) -> list[_Vec3]:
        _launch_position = np.asarray(launch_position, dtype=np.float64)
        _platform_velocity = np.asarray(platform_velocity, dtype=np.float64)
        if isinstance(launch_direction, Angles):
            return self._core.compute_trajectory(
                _launch_position,
                launch_direction,
                _platform_velocity,
                float(muzzle_velocity),
                float(rifling_twist),
                float(start_time),
                float(end_time),
                float(sample_interval),
            )
        else:
            _launch_direction = np.asarray(launch_direction, dtype=np.float64)
            return self._core.compute_trajectory(
                _launch_position,
                _launch_direction,
                _platform_velocity,
                float(muzzle_velocity),
                float(rifling_twist),
                float(start_time),
                float(end_time),
                float(sample_interval),
            )

    def optimize_launch_direction(
        self,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike,
        target_position: ArrayLike,
        muzzle_velocity: float,
        rifling_twist: float,
        time_of_flight: float,
        *,
        max_launch_direction_optimizer_iterations: int = 25,
    ) -> _Vec3:
        return self._core.optimize_launch_direction(
            np.asarray(launch_position, dtype=np.float64),
            np.asarray(platform_velocity, dtype=np.float64),
            np.asarray(target_position, dtype=np.float64),
            float(muzzle_velocity),
            float(rifling_twist),
            float(time_of_flight),
            int(max_launch_direction_optimizer_iterations),
        )

    def optimize_launch_angles(
        self,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike,
        target_position: ArrayLike,
        muzzle_velocity: float,
        rifling_twist: float,
        time_of_flight: float,
        *,
        max_launch_direction_optimizer_iterations: int = 25,
    ) -> Angles:
        return self._core.optimize_launch_angles(
            np.asarray(launch_position, dtype=np.float64),
            np.asarray(platform_velocity, dtype=np.float64),
            np.asarray(target_position, dtype=np.float64),
            float(muzzle_velocity),
            float(rifling_twist),
            float(time_of_flight),
            int(max_launch_direction_optimizer_iterations),
        )

    def solve_launch_direction(
        self,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike,
        target_position: ArrayLike,
        muzzle_velocity: float,
        rifling_twist: float,
        time_of_flight: float,
        *,
        miss_distance_threshold: float = 1.0,
        max_launch_direction_optimizer_iterations: int = 25,
    ) -> _Vec3 | None:
        return self._core.solve_launch_direction(
            np.asarray(launch_position, dtype=np.float64),
            np.asarray(platform_velocity, dtype=np.float64),
            np.asarray(target_position, dtype=np.float64),
            float(muzzle_velocity),
            float(rifling_twist),
            float(time_of_flight),
            float(miss_distance_threshold),
            int(max_launch_direction_optimizer_iterations),
        )

    def solve_launch_angles(
        self,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike,
        target_position: ArrayLike,
        muzzle_velocity: float,
        rifling_twist: float,
        time_of_flight: float,
        *,
        miss_distance_threshold: float = 1.0,
        max_launch_direction_optimizer_iterations: int = 25,
    ) -> Angles | None:
        return self._core.solve_launch_angles(
            np.asarray(launch_position, dtype=np.float64),
            np.asarray(platform_velocity, dtype=np.float64),
            np.asarray(target_position, dtype=np.float64),
            float(muzzle_velocity),
            float(rifling_twist),
            float(time_of_flight),
            float(miss_distance_threshold),
            int(max_launch_direction_optimizer_iterations),
        )

    def solve_launch_direction_and_time_of_flight(
        self,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike,
        target_motion: Callable[[float], _Vec3],
        muzzle_velocity: float,
        rifling_twist: float,
        min_time_of_flight: float,
        max_time_of_flight: float,
        *,
        miss_distance_threshold: float = 1.0,
        segment_size: float = 0.5,
        max_time_of_flight_optimizer_iterations: int = 30,
        max_launch_direction_optimizer_iterations: int = 25,
    ) -> tuple[_Vec3, float] | None:
        return self._core.solve_launch_direction_and_time_of_flight(
            np.asarray(launch_position, dtype=np.float64),
            np.asarray(platform_velocity, dtype=np.float64),
            target_motion,
            float(muzzle_velocity),
            float(rifling_twist),
            float(min_time_of_flight),
            float(max_time_of_flight),
            float(miss_distance_threshold),
            float(segment_size),
            int(max_time_of_flight_optimizer_iterations),
            int(max_launch_direction_optimizer_iterations),
        )

    def solve_launch_angles_and_time_of_flight(
        self,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike,
        target_motion: Callable[[float], _Vec3],
        muzzle_velocity: float,
        rifling_twist: float,
        min_time_of_flight: float,
        max_time_of_flight: float,
        *,
        miss_distance_threshold: float = 1.0,
        segment_size: float = 0.5,
        max_time_of_flight_optimizer_iterations: int = 30,
        max_launch_direction_optimizer_iterations: int = 25,
    ) -> tuple[Angles, float] | None:
        return self._core.solve_launch_angles_and_time_of_flight(
            np.asarray(launch_position, dtype=np.float64),
            np.asarray(platform_velocity, dtype=np.float64),
            target_motion,
            float(muzzle_velocity),
            float(rifling_twist),
            float(min_time_of_flight),
            float(max_time_of_flight),
            float(miss_distance_threshold),
            float(segment_size),
            int(max_time_of_flight_optimizer_iterations),
            int(max_launch_direction_optimizer_iterations),
        )
