from __future__ import annotations

from collections.abc import Callable
from typing import overload, Literal

import numpy as np
from numpy.typing import ArrayLike, NDArray

from .integrator import RK4, RK45
from .environment import Environment
from .projectile import Projectile
from ._core import (  # type: ignore
    Angles,
    PMRK4 as _PMRK4,
    PMRK45 as _PMRK45,
    MPMRK4 as _MPMRK4,
    MPMRK45 as _MPMRK45,
)

_Vec3 = NDArray[np.float64]


class PointMassBallistics:
    def __init__(
        self,
        *,
        integrator: RK4 | RK45 | Literal["rk4", "rk45"] = "rk45",
        environment: Environment | Literal["isa"] | None = None,
        projectile: Projectile | None = None,
    ) -> None:
        if integrator == "rk4":
            integrator = RK4()
        elif integrator == "rk45":
            integrator = RK45()
        if environment == None:
            environment = Environment()
        elif environment == "isa":
            environment = Environment.isa()
        if projectile == None:
            projectile = Projectile()

        if isinstance(integrator, RK4):
            self._core = _PMRK4()
        elif isinstance(integrator, RK45):  # type: ignore
            self._core = _PMRK45()

        self._core.integrator = integrator._core  # type: ignore
        self._core.environment = environment._core  # type: ignore
        self._core.projectile = projectile._core  # type: ignore

        self._integrator = integrator
        self._environment = environment
        self._projectile = projectile

        self._integrator._core = self._core.integrator  # type: ignore
        self._environment._core = self._core.environment  # type: ignore
        self._projectile._core = self._core.projectile  # type: ignore

    @property
    def integrator(self):
        return self._integrator

    @property
    def environment(self):
        return self._environment

    @property
    def projectile(self):
        return self._projectile

    @integrator.setter
    def integrator(self, value: RK4 | RK45):
        if isinstance(value, RK4):
            new_core = _PMRK4()
        elif isinstance(value, RK45):  # type: ignore
            new_core = _PMRK45()

        new_core.integrator = value._core  # type: ignore
        new_core.environment = self._environment._core  # type: ignore
        new_core.projectile = self._projectile._core  # type: ignore

        self._core = new_core
        self._integrator = value

        self._integrator._core = self._core.integrator  # type: ignore
        self._environment._core = self._core.environment  # type: ignore
        self._projectile._core = self._core.projectile  # type: ignore

    @environment.setter
    def environment(self, value: Environment):
        self._core.environment = value._core  # type: ignore
        self._environment = value
        self._environment._core = self._core.environment  # type: ignore

    @projectile.setter
    def projectile(self, value: Projectile):
        self._core.projectile = value._core  # type: ignore
        self._projectile = value
        self._projectile._core = self._core.projectile  # type: ignore

    @overload
    def compute_final_position(
        self,
        *,
        launch_position: ArrayLike,
        launch_direction: ArrayLike,
        platform_velocity: ArrayLike = ...,
        muzzle_velocity: float,
        time_of_flight: float,
    ) -> _Vec3: ...

    @overload
    def compute_final_position(
        self,
        *,
        launch_position: ArrayLike,
        launch_angles: ArrayLike | Angles,
        platform_velocity: ArrayLike = ...,
        muzzle_velocity: float,
        time_of_flight: float,
    ) -> _Vec3: ...

    def compute_final_position(
        self,
        *,
        launch_position: ArrayLike,
        launch_direction: ArrayLike | None = None,
        launch_angles: ArrayLike | Angles | None = None,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        muzzle_velocity: float,
        time_of_flight: float,
    ) -> _Vec3:
        _launch_position = np.asarray(launch_position, dtype=np.float64)
        _platform_velocity = np.asarray(platform_velocity, dtype=np.float64)
        if launch_direction is not None:
            _direction = np.asarray(launch_direction, dtype=np.float64)
        if launch_angles is not None:
            if isinstance(launch_angles, Angles):
                _direction = launch_angles
            else:
                _launch_angles = np.asarray(launch_angles, dtype=np.float64)
                _direction = Angles(*_launch_angles)

        return self._core.compute_final_position(
            _launch_position,
            _direction,  # type: ignore
            _platform_velocity,
            float(muzzle_velocity),
            float(time_of_flight),
        )

    @overload
    def compute_trajectory(
        self,
        *,
        launch_position: ArrayLike,
        launch_direction: ArrayLike,
        platform_velocity: ArrayLike = ...,
        muzzle_velocity: float,
        start_time: float = ...,
        end_time: float,
        sample_interval: float,
    ) -> list[_Vec3]: ...
    @overload
    def compute_trajectory(
        self,
        *,
        launch_position: ArrayLike,
        launch_angles: ArrayLike | Angles,
        platform_velocity: ArrayLike = ...,
        muzzle_velocity: float,
        start_time: float = ...,
        end_time: float,
        sample_interval: float,
    ) -> list[_Vec3]: ...
    def compute_trajectory(
        self,
        *,
        launch_position: ArrayLike,
        launch_direction: ArrayLike | None = None,
        launch_angles: ArrayLike | Angles | None = None,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        muzzle_velocity: float,
        start_time: float = 0.0,
        end_time: float,
        sample_interval: float = 0.2,
    ) -> list[_Vec3]:
        _launch_position = np.asarray(launch_position, dtype=np.float64)
        _platform_velocity = np.asarray(platform_velocity, dtype=np.float64)
        if launch_direction is not None:
            _direction = np.asarray(launch_direction, dtype=np.float64)
        if launch_angles is not None:
            if isinstance(launch_angles, Angles):
                _direction = launch_angles
            else:
                _launch_angles = np.asarray(launch_angles, dtype=np.float64)
                _direction = Angles(*_launch_angles)

        return self._core.compute_trajectory(
            _launch_position,
            _direction,  # type: ignore
            _platform_velocity,
            float(muzzle_velocity),
            float(start_time),
            float(end_time),
            float(sample_interval),
        )

    def optimize_launch_direction(
        self,
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        target_position: ArrayLike,
        muzzle_velocity: float,
        time_of_flight: float,
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
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        target_position: ArrayLike,
        muzzle_velocity: float,
        time_of_flight: float,
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
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        target_position: ArrayLike,
        muzzle_velocity: float,
        time_of_flight: float,
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
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        target_position: ArrayLike,
        muzzle_velocity: float,
        time_of_flight: float,
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
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        target_motion: Callable[[float], ArrayLike],
        muzzle_velocity: float,
        min_time_of_flight: float = 0.0,
        max_time_of_flight: float,
        miss_distance_threshold: float = 1.0,
        segment_size: float = 0.5,
        max_time_of_flight_optimizer_iterations: int = 30,
        max_launch_direction_optimizer_iterations: int = 25,
    ) -> tuple[_Vec3, float] | None:
        def _target_motion(t: float) -> np.ndarray:
            return np.asarray(target_motion(t), dtype=np.float64)

        return self._core.solve_launch_direction_and_time_of_flight(
            np.asarray(launch_position, dtype=np.float64),
            np.asarray(platform_velocity, dtype=np.float64),
            _target_motion,
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
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        target_motion: Callable[[float], ArrayLike],
        muzzle_velocity: float,
        min_time_of_flight: float = 0.0,
        max_time_of_flight: float,
        miss_distance_threshold: float = 1.0,
        segment_size: float = 0.5,
        max_time_of_flight_optimizer_iterations: int = 30,
        max_launch_direction_optimizer_iterations: int = 25,
    ) -> tuple[Angles, float] | None:
        def _target_motion(t: float) -> np.ndarray:
            return np.asarray(target_motion(t), dtype=np.float64)

        return self._core.solve_launch_angles_and_time_of_flight(
            np.asarray(launch_position, dtype=np.float64),
            np.asarray(platform_velocity, dtype=np.float64),
            _target_motion,
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
        integrator: RK4 | RK45 | Literal["rk4", "rk45"] = "rk45",
        environment: Environment | Literal["isa"] | None = None,
        projectile: Projectile | None = None,
    ) -> None:
        if integrator == "rk4":
            integrator = RK4()
        elif integrator == "rk45":
            integrator = RK45()
        if environment == None:
            environment = Environment()
        elif environment == "isa":
            environment = Environment.isa()
        if projectile == None:
            projectile = Projectile()

        if isinstance(integrator, RK4):
            self._core = _MPMRK4()
        elif isinstance(integrator, RK45):  # type: ignore
            self._core = _MPMRK45()

        self._core.integrator = integrator._core  # type: ignore
        self._core.environment = environment._core  # type: ignore
        self._core.projectile = projectile._core  # type: ignore

        self._integrator = integrator
        self._environment = environment
        self._projectile = projectile

        self._integrator._core = self._core.integrator  # type: ignore
        self._environment._core = self._core.environment  # type: ignore
        self._projectile._core = self._core.projectile  # type: ignore

    @property
    def integrator(self):
        return self._integrator

    @property
    def environment(self):
        return self._environment

    @property
    def projectile(self):
        return self._projectile

    @integrator.setter
    def integrator(self, value: RK4 | RK45):
        if isinstance(value, RK4):
            new_core = _MPMRK4()
        elif isinstance(value, RK45):  # type: ignore
            new_core = _MPMRK45()

        new_core.integrator = value._core  # type: ignore
        new_core.environment = self._environment._core  # type: ignore
        new_core.projectile = self._projectile._core  # type: ignore

        self._core = new_core
        self._integrator = value

        self._integrator._core = self._core.integrator  # type: ignore
        self._environment._core = self._core.environment  # type: ignore
        self._projectile._core = self._core.projectile  # type: ignore

    @environment.setter
    def environment(self, value: Environment):
        self._core.environment = value._core  # type: ignore
        self._environment = value
        self._environment._core = self._core.environment  # type: ignore

    @projectile.setter
    def projectile(self, value: Projectile):
        self._core.projectile = value._core  # type: ignore
        self._projectile = value
        self._projectile._core = self._core.projectile  # type: ignore

    @overload
    def compute_final_position(
        self,
        *,
        launch_position: ArrayLike,
        launch_direction: ArrayLike,
        platform_velocity: ArrayLike = ...,
        muzzle_velocity: float,
        twist_of_rifling: float,
        time_of_flight: float,
    ) -> _Vec3: ...

    @overload
    def compute_final_position(
        self,
        *,
        launch_position: ArrayLike,
        launch_angles: ArrayLike | Angles,
        platform_velocity: ArrayLike = ...,
        muzzle_velocity: float,
        twist_of_rifling: float,
        time_of_flight: float,
    ) -> _Vec3: ...

    def compute_final_position(
        self,
        *,
        launch_position: ArrayLike,
        launch_direction: ArrayLike | None = None,
        launch_angles: ArrayLike | Angles | None = None,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        muzzle_velocity: float,
        twist_of_rifling: float,
        time_of_flight: float,
    ) -> _Vec3:
        _launch_position = np.asarray(launch_position, dtype=np.float64)
        _platform_velocity = np.asarray(platform_velocity, dtype=np.float64)
        if launch_direction is not None:
            _direction = np.asarray(launch_direction, dtype=np.float64)
        if launch_angles is not None:
            if isinstance(launch_angles, Angles):
                _direction = launch_angles
            else:
                _launch_angles = np.asarray(launch_angles, dtype=np.float64)
                _direction = Angles(*_launch_angles)

        return self._core.compute_final_position(
            _launch_position,
            _direction,  # type: ignore
            _platform_velocity,
            float(muzzle_velocity),
            float(twist_of_rifling),
            float(time_of_flight),
        )

    @overload
    def compute_trajectory(
        self,
        *,
        launch_position: ArrayLike,
        launch_direction: ArrayLike,
        platform_velocity: ArrayLike = ...,
        muzzle_velocity: float,
        twist_of_rifling: float,
        start_time: float = ...,
        end_time: float,
        sample_interval: float,
    ) -> list[_Vec3]: ...
    @overload
    def compute_trajectory(
        self,
        *,
        launch_position: ArrayLike,
        launch_angles: ArrayLike | Angles,
        platform_velocity: ArrayLike = ...,
        muzzle_velocity: float,
        twist_of_rifling: float,
        start_time: float = ...,
        end_time: float,
        sample_interval: float,
    ) -> list[_Vec3]: ...
    def compute_trajectory(
        self,
        *,
        launch_position: ArrayLike,
        launch_direction: ArrayLike | None = None,
        launch_angles: ArrayLike | Angles | None = None,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        muzzle_velocity: float,
        twist_of_rifling: float,
        start_time: float = 0.0,
        end_time: float,
        sample_interval: float = 0.2,
    ) -> list[_Vec3]:
        _launch_position = np.asarray(launch_position, dtype=np.float64)
        _platform_velocity = np.asarray(platform_velocity, dtype=np.float64)
        if launch_direction is not None:
            _direction = np.asarray(launch_direction, dtype=np.float64)
        if launch_angles is not None:
            if isinstance(launch_angles, Angles):
                _direction = launch_angles
            else:
                _launch_angles = np.asarray(launch_angles, dtype=np.float64)
                _direction = Angles(*_launch_angles)

        return self._core.compute_trajectory(
            _launch_position,
            _direction,  # type: ignore
            _platform_velocity,
            float(muzzle_velocity),
            float(twist_of_rifling),
            float(start_time),
            float(end_time),
            float(sample_interval),
        )

    def optimize_launch_direction(
        self,
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        target_position: ArrayLike,
        muzzle_velocity: float,
        twist_of_rifling: float,
        time_of_flight: float,
        max_launch_direction_optimizer_iterations: int = 25,
    ) -> _Vec3:
        return self._core.optimize_launch_direction(
            np.asarray(launch_position, dtype=np.float64),
            np.asarray(platform_velocity, dtype=np.float64),
            np.asarray(target_position, dtype=np.float64),
            float(muzzle_velocity),
            float(twist_of_rifling),
            float(time_of_flight),
            int(max_launch_direction_optimizer_iterations),
        )

    def optimize_launch_angles(
        self,
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        target_position: ArrayLike,
        muzzle_velocity: float,
        twist_of_rifling: float,
        time_of_flight: float,
        max_launch_direction_optimizer_iterations: int = 25,
    ) -> Angles:
        return self._core.optimize_launch_angles(
            np.asarray(launch_position, dtype=np.float64),
            np.asarray(platform_velocity, dtype=np.float64),
            np.asarray(target_position, dtype=np.float64),
            float(muzzle_velocity),
            float(twist_of_rifling),
            float(time_of_flight),
            int(max_launch_direction_optimizer_iterations),
        )

    def solve_launch_direction(
        self,
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        target_position: ArrayLike,
        muzzle_velocity: float,
        twist_of_rifling: float,
        time_of_flight: float,
        miss_distance_threshold: float = 1.0,
        max_launch_direction_optimizer_iterations: int = 25,
    ) -> _Vec3 | None:
        return self._core.solve_launch_direction(
            np.asarray(launch_position, dtype=np.float64),
            np.asarray(platform_velocity, dtype=np.float64),
            np.asarray(target_position, dtype=np.float64),
            float(muzzle_velocity),
            float(twist_of_rifling),
            float(time_of_flight),
            float(miss_distance_threshold),
            int(max_launch_direction_optimizer_iterations),
        )

    def solve_launch_angles(
        self,
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        target_position: ArrayLike,
        muzzle_velocity: float,
        twist_of_rifling: float,
        time_of_flight: float,
        miss_distance_threshold: float = 1.0,
        max_launch_direction_optimizer_iterations: int = 25,
    ) -> Angles | None:
        return self._core.solve_launch_angles(
            np.asarray(launch_position, dtype=np.float64),
            np.asarray(platform_velocity, dtype=np.float64),
            np.asarray(target_position, dtype=np.float64),
            float(muzzle_velocity),
            float(twist_of_rifling),
            float(time_of_flight),
            float(miss_distance_threshold),
            int(max_launch_direction_optimizer_iterations),
        )

    def solve_launch_direction_and_time_of_flight(
        self,
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        target_motion: Callable[[float], ArrayLike],
        muzzle_velocity: float,
        twist_of_rifling: float,
        min_time_of_flight: float = 0.0,
        max_time_of_flight: float,
        miss_distance_threshold: float = 1.0,
        segment_size: float = 0.5,
        max_time_of_flight_optimizer_iterations: int = 30,
        max_launch_direction_optimizer_iterations: int = 25,
    ) -> tuple[_Vec3, float] | None:
        def _target_motion(t: float) -> np.ndarray:
            return np.asarray(target_motion(t), dtype=np.float64)

        return self._core.solve_launch_direction_and_time_of_flight(
            np.asarray(launch_position, dtype=np.float64),
            np.asarray(platform_velocity, dtype=np.float64),
            _target_motion,
            float(muzzle_velocity),
            float(twist_of_rifling),
            float(min_time_of_flight),
            float(max_time_of_flight),
            float(miss_distance_threshold),
            float(segment_size),
            int(max_time_of_flight_optimizer_iterations),
            int(max_launch_direction_optimizer_iterations),
        )

    def solve_launch_angles_and_time_of_flight(
        self,
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        target_motion: Callable[[float], ArrayLike],
        muzzle_velocity: float,
        twist_of_rifling: float,
        min_time_of_flight: float = 0.0,
        max_time_of_flight: float,
        miss_distance_threshold: float = 1.0,
        segment_size: float = 0.5,
        max_time_of_flight_optimizer_iterations: int = 30,
        max_launch_direction_optimizer_iterations: int = 25,
    ) -> tuple[Angles, float] | None:
        def _target_motion(t: float) -> np.ndarray:
            return np.asarray(target_motion(t), dtype=np.float64)

        return self._core.solve_launch_angles_and_time_of_flight(
            np.asarray(launch_position, dtype=np.float64),
            np.asarray(platform_velocity, dtype=np.float64),
            _target_motion,
            float(muzzle_velocity),
            float(twist_of_rifling),
            float(min_time_of_flight),
            float(max_time_of_flight),
            float(miss_distance_threshold),
            float(segment_size),
            int(max_time_of_flight_optimizer_iterations),
            int(max_launch_direction_optimizer_iterations),
        )
