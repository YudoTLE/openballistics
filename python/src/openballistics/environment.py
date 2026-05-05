from __future__ import annotations

from collections.abc import Callable
from typing import cast

import numpy as np
from numpy.typing import ArrayLike, NDArray

from ._core import RealisticEnvironment as _RealisticEnvironment  # type: ignore
from .types import Interpolator

_Vec3 = NDArray[np.float64]
_ScalarProfile = Callable[[float], float]
_ScalarField = Callable[[_Vec3], float]
_Vec3Profile = Callable[[float], _Vec3]
_Vec3Field = Callable[[_Vec3], _Vec3]


class Environment:
    pass


class RealisticEnvironment(Environment):
    def __init__(
        self,
        *,
        adiabatic_index: float | None = None,
        specific_gas_constant: float | None = None,
        temperature: float | _ScalarProfile | _ScalarField | Interpolator | None = None,
        pressure: float | _ScalarProfile | _ScalarField | Interpolator | None = None,
        gravity: ArrayLike | _Vec3Profile | _Vec3Field | Interpolator | None = None,
        wind_velocity: (
            ArrayLike | _Vec3Profile | _Vec3Field | Interpolator | None
        ) = None,
    ) -> None:
        self._core = _RealisticEnvironment()
        if adiabatic_index is not None:
            self.set_adiabatic_index(adiabatic_index)
        if specific_gas_constant is not None:
            self.set_specific_gas_constant(specific_gas_constant)
        if temperature is not None:
            self.set_temperature(temperature)
        if pressure is not None:
            self.set_pressure(pressure)
        if gravity is not None:
            self.set_gravity(gravity)
        if wind_velocity is not None:
            self.set_wind_velocity(wind_velocity)

    def set_adiabatic_index(self, value: float, /) -> RealisticEnvironment:
        self._core.set_adiabatic_index(value)
        return self

    def set_specific_gas_constant(self, value: float, /) -> RealisticEnvironment:
        self._core.set_specific_gas_constant(value)
        return self

    def set_temperature(
        self,
        value: float | _ScalarProfile | _ScalarField | Interpolator,
        /,
    ) -> RealisticEnvironment:
        if isinstance(value, Interpolator):
            self._core.set_temperature(
                cast(_ScalarProfile | _ScalarField, value.fn), value.step
            )
        elif isinstance(value, (int, float)):
            self._core.set_temperature(float(value))
        elif callable(value):
            self._core.set_temperature(value)
        return self

    def set_pressure(
        self,
        value: float | _ScalarProfile | _ScalarField | Interpolator,
        /,
    ) -> RealisticEnvironment:
        if isinstance(value, Interpolator):
            self._core.set_pressure(
                cast(_ScalarProfile | _ScalarField, value.fn), value.step
            )
        elif isinstance(value, (int, float)):
            self._core.set_pressure(float(value))
        elif callable(value):
            self._core.set_pressure(value)
        return self

    def set_gravity(
        self,
        value: ArrayLike | _Vec3Profile | _Vec3Field | Interpolator,
        /,
    ) -> RealisticEnvironment:
        if isinstance(value, Interpolator):
            self._core.set_gravity(
                cast(_Vec3Profile | _Vec3Field, value.fn), value.step
            )
        elif callable(value):
            self._core.set_gravity(value)
        else:
            self._core.set_gravity(np.asarray(value, dtype=np.float64))
        return self

    def set_wind_velocity(
        self,
        value: ArrayLike | _Vec3Profile | _Vec3Field | Interpolator,
        /,
    ) -> RealisticEnvironment:
        if isinstance(value, Interpolator):
            self._core.set_wind_velocity(
                cast(_Vec3Profile | _Vec3Field, value.fn), value.step
            )
        elif callable(value):
            self._core.set_wind_velocity(value)
        else:
            self._core.set_wind_velocity(np.asarray(value, dtype=np.float64))
        return self

    def adiabatic_index(self) -> float:
        return self._core.adiabatic_index()

    def specific_gas_constant(self) -> float:
        return self._core.specific_gas_constant()

    def temperature(self, position: ArrayLike, /) -> float:
        return self._core.temperature(np.asarray(position, dtype=np.float64))

    def pressure(self, position: ArrayLike, /) -> float:
        return self._core.pressure(np.asarray(position, dtype=np.float64))

    def gravity(self, position: ArrayLike, /) -> _Vec3:
        return self._core.gravity(np.asarray(position, dtype=np.float64))

    def wind_velocity(self, position: ArrayLike, /) -> _Vec3:
        return self._core.wind_velocity(np.asarray(position, dtype=np.float64))

    @staticmethod
    def isa() -> RealisticEnvironment:
        environment = RealisticEnvironment.__new__(RealisticEnvironment)
        environment._core = _RealisticEnvironment.isa()
        return environment
