from __future__ import annotations

from collections.abc import Callable
from typing import Generic, overload, Literal, TypeVar, SupportsFloat, SupportsInt

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

T_Integrator = TypeVar("T_Integrator", RK4, RK45)
T_Model = TypeVar("T_Model", Literal["pm"], Literal["mpm"])


class Ballistics(Generic[T_Model, T_Integrator]):

    @overload
    def __init__(
        self: Ballistics[Literal["pm"], RK4],
        *,
        model: Literal["pm"],
        integrator: Literal["rk4"] | RK4 | None = ...,
        environment: Environment | Literal["isa"] | None = ...,
        projectile: Projectile | None = ...,
    ) -> None: ...

    @overload
    def __init__(
        self: Ballistics[Literal["pm"], RK45],
        *,
        model: Literal["pm"],
        integrator: Literal["rk45"] | RK45 | None = ...,
        environment: Environment | Literal["isa"] | None = ...,
        projectile: Projectile | None = ...,
    ) -> None: ...

    @overload
    def __init__(
        self: Ballistics[Literal["mpm"], RK4],
        *,
        model: Literal["mpm"],
        integrator: Literal["rk4"] | RK4 | None = ...,
        environment: Environment | Literal["isa"] | None = ...,
        projectile: Projectile | None = ...,
    ) -> None: ...

    @overload
    def __init__(
        self: Ballistics[Literal["mpm"], RK45],
        *,
        model: Literal["mpm"],
        integrator: Literal["rk45"] | RK45 | None = ...,
        environment: Environment | Literal["isa"] | None = ...,
        projectile: Projectile | None = ...,
    ) -> None: ...

    def __init__(
        self,
        *,
        model: Literal["pm", "mpm"],
        integrator: RK4 | RK45 | Literal["rk4", "rk45"] | None = "rk45",
        environment: Environment | Literal["isa"] | None = None,
        projectile: Projectile | None = None,
    ) -> None:
        if integrator is None or integrator == "rk45":
            integrator = RK45()
        elif integrator == "rk4":
            integrator = RK4()
        if environment is None:
            environment = Environment()
        elif environment == "isa":
            environment = Environment.isa()
        if projectile is None:
            projectile = Projectile()
        if model == "pm":
            if isinstance(integrator, RK4):
                self._core = _PMRK4()
            elif isinstance(integrator, RK45):  # type: ignore
                self._core = _PMRK45()
        elif model == "mpm":
            if isinstance(integrator, RK4):
                self._core = _MPMRK4()
            elif isinstance(integrator, RK45):  # type: ignore
                self._core = _MPMRK45()

        self._core.integrator = integrator._core  # type: ignore
        self._core.environment = environment._core  # type: ignore
        self._core.projectile = projectile._core  # type: ignore

        self._model = model
        self._integrator = integrator
        self._environment = environment
        self._projectile = projectile

        self._integrator._core = self._core.integrator  # type: ignore
        self._environment._core = self._core.environment  # type: ignore
        self._projectile._core = self._core.projectile  # type: ignore

    @property
    def integrator(self) -> T_Integrator:
        return self._integrator  # type: ignore

    @property
    def environment(self) -> Environment:
        return self._environment

    @property
    def projectile(self) -> Projectile:
        return self._projectile

    @integrator.setter
    def integrator(self, value: T_Integrator) -> None:
        self._core.integrator = value._core  # type: ignore
        self._integrator = value
        self._integrator._core = self._core.integrator  # type: ignore

    @environment.setter
    def environment(self, value: Environment) -> None:
        self._core.environment = value._core  # type: ignore
        self._environment = value
        self._environment._core = self._core.environment  # type: ignore

    @projectile.setter
    def projectile(self, value: Projectile) -> None:
        self._core.projectile = value._core  # type: ignore
        self._projectile = value
        self._projectile._core = self._core.projectile  # type: ignore

    @overload
    def compute_final_position(
        self: Ballistics[Literal["pm"], T_Integrator],
        *,
        launch_position: ArrayLike,
        launch_direction: ArrayLike,
        platform_velocity: ArrayLike = ...,
        muzzle_velocity: SupportsFloat,
        time_of_flight: SupportsFloat,
    ) -> _Vec3: ...

    @overload
    def compute_final_position(
        self: Ballistics[Literal["pm"], T_Integrator],
        *,
        launch_position: ArrayLike,
        launch_angles: ArrayLike | Angles,
        platform_velocity: ArrayLike = ...,
        muzzle_velocity: SupportsFloat,
        time_of_flight: SupportsFloat,
    ) -> _Vec3: ...

    @overload
    def compute_final_position(
        self: Ballistics[Literal["mpm"], T_Integrator],
        *,
        launch_position: ArrayLike,
        launch_direction: ArrayLike,
        platform_velocity: ArrayLike = ...,
        muzzle_velocity: SupportsFloat,
        twist_of_rifling: SupportsFloat,
        time_of_flight: SupportsFloat,
    ) -> _Vec3: ...
    @overload
    def compute_final_position(
        self: Ballistics[Literal["mpm"], T_Integrator],
        *,
        launch_position: ArrayLike,
        launch_angles: ArrayLike | Angles,
        platform_velocity: ArrayLike = ...,
        muzzle_velocity: SupportsFloat,
        twist_of_rifling: SupportsFloat,
        time_of_flight: SupportsFloat,
    ) -> _Vec3: ...

    def compute_final_position(
        self,
        *,
        launch_position: ArrayLike,
        launch_direction: ArrayLike | None = None,
        launch_angles: ArrayLike | Angles | None = None,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        muzzle_velocity: SupportsFloat,
        twist_of_rifling: SupportsFloat | None = None,
        time_of_flight: SupportsFloat,
    ) -> _Vec3:
        if isinstance(self._core, _PMRK4 | _PMRK45):
            return self._core.compute_final_position(
                _validate_vector3(launch_position),
                _validate_launch_direction(launch_direction, launch_angles),
                _validate_vector3(platform_velocity),
                _validate_scalar(muzzle_velocity),
                _validate_scalar(time_of_flight),
            )
        if isinstance(self._core, _MPMRK4 | _MPMRK45):  # type: ignore
            return self._core.compute_final_position(
                _validate_vector3(launch_position),
                _validate_launch_direction(launch_direction, launch_angles),
                _validate_vector3(platform_velocity),
                _validate_scalar(muzzle_velocity),
                _validate_scalar(twist_of_rifling),
                _validate_scalar(time_of_flight),
            )
        raise TypeError

    @overload
    def compute_trajectory(
        self: Ballistics[Literal["pm"], T_Integrator],
        *,
        launch_position: ArrayLike,
        launch_direction: ArrayLike,
        platform_velocity: ArrayLike = ...,
        muzzle_velocity: SupportsFloat,
        start_time: SupportsFloat = ...,
        end_time: SupportsFloat,
        sample_interval: SupportsFloat = ...,
    ) -> list[_Vec3]: ...
    @overload
    def compute_trajectory(
        self: Ballistics[Literal["pm"], T_Integrator],
        *,
        launch_position: ArrayLike,
        launch_angles: ArrayLike | Angles,
        platform_velocity: ArrayLike = ...,
        muzzle_velocity: SupportsFloat,
        start_time: SupportsFloat = ...,
        end_time: SupportsFloat,
        sample_interval: SupportsFloat = ...,
    ) -> list[_Vec3]: ...
    @overload
    def compute_trajectory(
        self: Ballistics[Literal["mpm"], T_Integrator],
        *,
        launch_position: ArrayLike,
        launch_direction: ArrayLike,
        platform_velocity: ArrayLike = ...,
        muzzle_velocity: SupportsFloat,
        twist_of_rifling: SupportsFloat,
        start_time: SupportsFloat = ...,
        end_time: SupportsFloat,
        sample_interval: SupportsFloat = ...,
    ) -> list[_Vec3]: ...
    @overload
    def compute_trajectory(
        self: Ballistics[Literal["mpm"], T_Integrator],
        *,
        launch_position: ArrayLike,
        launch_angles: ArrayLike | Angles,
        platform_velocity: ArrayLike = ...,
        muzzle_velocity: SupportsFloat,
        twist_of_rifling: SupportsFloat,
        start_time: SupportsFloat = ...,
        end_time: SupportsFloat,
        sample_interval: SupportsFloat = ...,
    ) -> list[_Vec3]: ...
    def compute_trajectory(
        self,
        *,
        launch_position: ArrayLike,
        launch_direction: ArrayLike | None = None,
        launch_angles: ArrayLike | Angles | None = None,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        muzzle_velocity: SupportsFloat,
        twist_of_rifling: SupportsFloat | None = None,
        start_time: SupportsFloat = 0.0,
        end_time: SupportsFloat,
        sample_interval: SupportsFloat = 0.2,
    ) -> list[_Vec3]:
        if isinstance(self._core, _PMRK4 | _PMRK45):
            return self._core.compute_trajectory(
                _validate_vector3(launch_position),
                _validate_launch_direction(launch_direction, launch_angles),
                _validate_vector3(platform_velocity),
                _validate_scalar(muzzle_velocity),
                _validate_scalar(start_time),
                _validate_scalar(end_time),
                _validate_scalar(sample_interval),
            )
        if isinstance(self._core, _MPMRK4 | _MPMRK45):  # type: ignore
            return self._core.compute_trajectory(
                _validate_vector3(launch_position),
                _validate_launch_direction(launch_direction, launch_angles),
                _validate_vector3(platform_velocity),
                _validate_scalar(muzzle_velocity),
                _validate_scalar(twist_of_rifling),
                _validate_scalar(start_time),
                _validate_scalar(end_time),
                _validate_scalar(sample_interval),
            )
        raise TypeError

    @overload
    def optimize_launch_direction(
        self: Ballistics[Literal["pm"], T_Integrator],
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = ...,
        target_position: ArrayLike,
        muzzle_velocity: SupportsFloat,
        time_of_flight: SupportsFloat,
        max_iterations: SupportsInt = ...,
    ) -> _Vec3: ...
    @overload
    def optimize_launch_direction(
        self: Ballistics[Literal["mpm"], T_Integrator],
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = ...,
        target_position: ArrayLike,
        muzzle_velocity: SupportsFloat,
        twist_of_rifling: SupportsFloat,
        time_of_flight: SupportsFloat,
        max_iterations: SupportsInt = ...,
    ) -> _Vec3: ...
    def optimize_launch_direction(
        self,
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        target_position: ArrayLike,
        muzzle_velocity: SupportsFloat,
        twist_of_rifling: SupportsFloat | None = None,
        time_of_flight: SupportsFloat,
        max_iterations: SupportsInt = 25,
    ) -> _Vec3:
        if isinstance(self._core, _PMRK4 | _PMRK45):
            return self._core.optimize_launch_direction(
                _validate_vector3(launch_position),
                _validate_vector3(platform_velocity),
                _validate_vector3(target_position),
                _validate_scalar(muzzle_velocity),
                _validate_scalar(time_of_flight),
                _validate_integer(max_iterations),
            )
        if isinstance(self._core, _MPMRK4 | _MPMRK45):  # type: ignore
            return self._core.optimize_launch_direction(
                _validate_vector3(launch_position),
                _validate_vector3(platform_velocity),
                _validate_vector3(target_position),
                _validate_scalar(muzzle_velocity),
                _validate_scalar(twist_of_rifling),
                _validate_scalar(time_of_flight),
                _validate_integer(max_iterations),
            )
        raise TypeError

    @overload
    def optimize_launch_angles(
        self: Ballistics[Literal["pm"], T_Integrator],
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = ...,
        target_position: ArrayLike,
        muzzle_velocity: SupportsFloat,
        time_of_flight: SupportsFloat,
        max_iterations: SupportsInt = ...,
    ) -> Angles: ...

    @overload
    def optimize_launch_angles(
        self: Ballistics[Literal["mpm"], T_Integrator],
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = ...,
        target_position: ArrayLike,
        muzzle_velocity: SupportsFloat,
        twist_of_rifling: SupportsFloat,
        time_of_flight: SupportsFloat,
        max_iterations: SupportsInt = ...,
    ) -> Angles: ...

    def optimize_launch_angles(
        self,
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        target_position: ArrayLike,
        muzzle_velocity: SupportsFloat,
        twist_of_rifling: SupportsFloat | None = None,
        time_of_flight: SupportsFloat,
        max_iterations: SupportsInt = 25,
    ) -> Angles:
        if isinstance(self._core, _PMRK4 | _PMRK45):
            return self._core.optimize_launch_angles(
                _validate_vector3(launch_position),
                _validate_vector3(platform_velocity),
                _validate_vector3(target_position),
                _validate_scalar(muzzle_velocity),
                _validate_scalar(time_of_flight),
                _validate_integer(max_iterations),
            )
        if isinstance(self._core, _MPMRK4 | _MPMRK45):  # type: ignore
            return self._core.optimize_launch_angles(
                _validate_vector3(launch_position),
                _validate_vector3(platform_velocity),
                _validate_vector3(target_position),
                _validate_scalar(muzzle_velocity),
                _validate_scalar(twist_of_rifling),
                _validate_scalar(time_of_flight),
                _validate_integer(max_iterations),
            )
        raise TypeError

    @overload
    def solve_launch_direction(
        self: Ballistics[Literal["pm"], T_Integrator],
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = ...,
        target_position: ArrayLike,
        muzzle_velocity: SupportsFloat,
        time_of_flight: SupportsFloat,
        miss_distance_threshold: SupportsFloat = ...,
        max_iterations: SupportsInt = ...,
    ) -> _Vec3 | None: ...

    @overload
    def solve_launch_direction(
        self: Ballistics[Literal["mpm"], T_Integrator],
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = ...,
        target_position: ArrayLike,
        muzzle_velocity: SupportsFloat,
        twist_of_rifling: SupportsFloat,
        time_of_flight: SupportsFloat,
        miss_distance_threshold: SupportsFloat = ...,
        max_iterations: SupportsInt = ...,
    ) -> _Vec3 | None: ...

    def solve_launch_direction(
        self,
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        target_position: ArrayLike,
        muzzle_velocity: SupportsFloat,
        twist_of_rifling: SupportsFloat | None = None,
        time_of_flight: SupportsFloat,
        miss_distance_threshold: SupportsFloat = 1.0,
        max_iterations: SupportsInt = 25,
    ) -> _Vec3 | None:
        if isinstance(self._core, _PMRK4 | _PMRK45):
            return self._core.solve_launch_direction(
                _validate_vector3(launch_position),
                _validate_vector3(platform_velocity),
                _validate_vector3(target_position),
                _validate_scalar(muzzle_velocity),
                _validate_scalar(time_of_flight),
                _validate_scalar(miss_distance_threshold),
                _validate_integer(max_iterations),
            )
        if isinstance(self._core, _MPMRK4 | _MPMRK45):  # type: ignore
            return self._core.solve_launch_direction(
                _validate_vector3(launch_position),
                _validate_vector3(platform_velocity),
                _validate_vector3(target_position),
                _validate_scalar(muzzle_velocity),
                _validate_scalar(twist_of_rifling),
                _validate_scalar(time_of_flight),
                _validate_scalar(miss_distance_threshold),
                _validate_integer(max_iterations),
            )
        raise TypeError

    @overload
    def solve_launch_angles(
        self: Ballistics[Literal["pm"], T_Integrator],
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = ...,
        target_position: ArrayLike,
        muzzle_velocity: SupportsFloat,
        time_of_flight: SupportsFloat,
        miss_distance_threshold: SupportsFloat = ...,
        max_iterations: SupportsInt = ...,
    ) -> Angles | None: ...

    @overload
    def solve_launch_angles(
        self: Ballistics[Literal["mpm"], T_Integrator],
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = ...,
        target_position: ArrayLike,
        muzzle_velocity: SupportsFloat,
        twist_of_rifling: SupportsFloat,
        time_of_flight: SupportsFloat,
        miss_distance_threshold: SupportsFloat = ...,
        max_iterations: SupportsInt = ...,
    ) -> Angles | None: ...

    def solve_launch_angles(
        self,
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        target_position: ArrayLike,
        muzzle_velocity: SupportsFloat,
        twist_of_rifling: SupportsFloat | None = None,
        time_of_flight: SupportsFloat,
        miss_distance_threshold: SupportsFloat = 1.0,
        max_iterations: SupportsInt = 25,
    ) -> Angles | None:
        if isinstance(self._core, _PMRK4 | _PMRK45):
            return self._core.solve_launch_angles(
                _validate_vector3(launch_position),
                _validate_vector3(platform_velocity),
                _validate_vector3(target_position),
                _validate_scalar(muzzle_velocity),
                _validate_scalar(time_of_flight),
                _validate_scalar(miss_distance_threshold),
                _validate_integer(max_iterations),
            )
        if isinstance(self._core, _MPMRK4 | _MPMRK45):  # type: ignore
            return self._core.solve_launch_angles(
                _validate_vector3(launch_position),
                _validate_vector3(platform_velocity),
                _validate_vector3(target_position),
                _validate_scalar(muzzle_velocity),
                _validate_scalar(twist_of_rifling),
                _validate_scalar(time_of_flight),
                _validate_scalar(miss_distance_threshold),
                _validate_integer(max_iterations),
            )
        raise TypeError

    @overload
    def solve_launch_direction_and_time_of_flight(
        self: Ballistics[Literal["pm"], T_Integrator],
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = ...,
        target_motion: Callable[[float], ArrayLike],
        muzzle_velocity: SupportsFloat,
        min_time_of_flight: SupportsFloat = ...,
        max_time_of_flight: SupportsFloat,
        miss_distance_threshold: SupportsFloat = ...,
        time_of_flight_segment_size: SupportsFloat = ...,
        time_of_flight_max_iterations: SupportsInt = ...,
        launch_direction_max_iterations: SupportsInt = ...,
    ) -> tuple[_Vec3, float] | None: ...

    @overload
    def solve_launch_direction_and_time_of_flight(
        self: Ballistics[Literal["mpm"], T_Integrator],
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = ...,
        target_motion: Callable[[float], ArrayLike],
        muzzle_velocity: SupportsFloat,
        twist_of_rifling: SupportsFloat,
        min_time_of_flight: SupportsFloat = ...,
        max_time_of_flight: SupportsFloat,
        miss_distance_threshold: SupportsFloat = ...,
        time_of_flight_segment_size: SupportsFloat = ...,
        time_of_flight_max_iterations: SupportsInt = ...,
        launch_direction_max_iterations: SupportsInt = ...,
    ) -> tuple[_Vec3, float] | None: ...

    def solve_launch_direction_and_time_of_flight(
        self,
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        target_motion: Callable[[float], ArrayLike],
        muzzle_velocity: SupportsFloat,
        twist_of_rifling: SupportsFloat | None = None,
        min_time_of_flight: SupportsFloat = 0.0,
        max_time_of_flight: SupportsFloat,
        miss_distance_threshold: SupportsFloat = 1.0,
        time_of_flight_segment_size: SupportsFloat = 0.5,
        time_of_flight_max_iterations: SupportsInt = 30,
        launch_direction_max_iterations: SupportsInt = 25,
    ) -> tuple[_Vec3, float] | None:
        if isinstance(self._core, _PMRK4 | _PMRK45):
            return self._core.solve_launch_direction_and_time_of_flight(
                _validate_vector3(launch_position),
                _validate_vector3(platform_velocity),
                _validate_motion(target_motion),
                _validate_scalar(muzzle_velocity),
                _validate_scalar(min_time_of_flight),
                _validate_scalar(max_time_of_flight),
                _validate_scalar(miss_distance_threshold),
                _validate_scalar(time_of_flight_segment_size),
                _validate_integer(time_of_flight_max_iterations),
                _validate_integer(launch_direction_max_iterations),
            )

        if isinstance(self._core, _MPMRK4 | _MPMRK45):  # type: ignore
            return self._core.solve_launch_direction_and_time_of_flight(
                _validate_vector3(launch_position),
                _validate_vector3(platform_velocity),
                _validate_motion(target_motion),
                _validate_scalar(muzzle_velocity),
                _validate_scalar(twist_of_rifling),
                _validate_scalar(min_time_of_flight),
                _validate_scalar(max_time_of_flight),
                _validate_scalar(miss_distance_threshold),
                _validate_scalar(time_of_flight_segment_size),
                _validate_integer(time_of_flight_max_iterations),
                _validate_integer(launch_direction_max_iterations),
            )

        raise TypeError

    @overload
    def solve_launch_angles_and_time_of_flight(
        self: Ballistics[Literal["pm"], T_Integrator],
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = ...,
        target_motion: Callable[[float], ArrayLike],
        muzzle_velocity: SupportsFloat,
        min_time_of_flight: SupportsFloat = ...,
        max_time_of_flight: SupportsFloat,
        miss_distance_threshold: SupportsFloat = ...,
        time_of_flight_segment_size: SupportsFloat = ...,
        time_of_flight_max_iterations: SupportsInt = ...,
        launch_direction_max_iterations: SupportsInt = ...,
    ) -> tuple[Angles, float] | None: ...

    @overload
    def solve_launch_angles_and_time_of_flight(
        self: Ballistics[Literal["mpm"], T_Integrator],
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = ...,
        target_motion: Callable[[float], ArrayLike],
        muzzle_velocity: SupportsFloat,
        twist_of_rifling: SupportsFloat,
        min_time_of_flight: SupportsFloat = ...,
        max_time_of_flight: SupportsFloat,
        miss_distance_threshold: SupportsFloat = ...,
        time_of_flight_segment_size: SupportsFloat = ...,
        time_of_flight_max_iterations: SupportsInt = ...,
        launch_direction_max_iterations: SupportsInt = ...,
    ) -> tuple[Angles, float] | None: ...

    def solve_launch_angles_and_time_of_flight(
        self,
        *,
        launch_position: ArrayLike,
        platform_velocity: ArrayLike = np.array([0.0, 0.0, 0.0]),
        target_motion: Callable[[float], ArrayLike],
        muzzle_velocity: SupportsFloat,
        twist_of_rifling: SupportsFloat | None = None,
        min_time_of_flight: SupportsFloat = 0.0,
        max_time_of_flight: SupportsFloat,
        miss_distance_threshold: SupportsFloat = 1.0,
        time_of_flight_segment_size: SupportsFloat = 0.5,
        time_of_flight_max_iterations: SupportsInt = 30,
        launch_direction_max_iterations: SupportsInt = 25,
    ) -> tuple[Angles, float] | None:
        if isinstance(self._core, _PMRK4 | _PMRK45):
            return self._core.solve_launch_angles_and_time_of_flight(
                _validate_vector3(launch_position),
                _validate_vector3(platform_velocity),
                _validate_motion(target_motion),
                _validate_scalar(muzzle_velocity),
                _validate_scalar(min_time_of_flight),
                _validate_scalar(max_time_of_flight),
                _validate_scalar(miss_distance_threshold),
                _validate_scalar(time_of_flight_segment_size),
                _validate_integer(time_of_flight_max_iterations),
                _validate_integer(launch_direction_max_iterations),
            )

        if isinstance(self._core, _MPMRK4 | _MPMRK45):  # type: ignore
            return self._core.solve_launch_angles_and_time_of_flight(
                _validate_vector3(launch_position),
                _validate_vector3(platform_velocity),
                _validate_motion(target_motion),
                _validate_scalar(muzzle_velocity),
                _validate_scalar(twist_of_rifling),
                _validate_scalar(min_time_of_flight),
                _validate_scalar(max_time_of_flight),
                _validate_scalar(miss_distance_threshold),
                _validate_scalar(time_of_flight_segment_size),
                _validate_integer(time_of_flight_max_iterations),
                _validate_integer(launch_direction_max_iterations),
            )

        raise TypeError


def _validate_integer(integer: SupportsInt | None) -> int:
    if integer is None:
        raise TypeError
    return int(integer)


def _validate_scalar(scalar: SupportsFloat | None) -> float:
    if scalar is None:
        raise TypeError
    return float(scalar)


def _validate_vector3(vector3: ArrayLike | None) -> _Vec3:
    if vector3 is None:
        raise TypeError
    vector3 = np.asarray(vector3, dtype=np.float64)
    if vector3.size != 3:
        raise TypeError
    return vector3


def _validate_motion(
    motion: Callable[[float], ArrayLike] | None,
) -> Callable[[float], _Vec3]:
    if motion is None:
        raise TypeError

    def _motion(time: float) -> _Vec3:
        return _validate_vector3(motion(time))

    return _motion


def _validate_launch_direction(
    launch_direction: ArrayLike | None, launch_angles: ArrayLike | Angles | None
) -> _Vec3:
    if launch_direction is not None:
        return np.asarray(launch_direction, dtype=np.float64)
    elif launch_angles is not None:
        if isinstance(launch_angles, Angles):
            return launch_angles.to_direction()
        return Angles(*np.asarray(launch_angles, dtype=np.float64)).to_direction()
    raise TypeError
