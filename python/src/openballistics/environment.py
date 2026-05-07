from __future__ import annotations

from collections.abc import Callable
from typing import cast

import numpy as np
from numpy.typing import ArrayLike, NDArray

from ._core import Environment as _Environment  # type: ignore
from .types import Interpolator

_Vec3 = NDArray[np.float64]
_ScalarProfile = Callable[[float], float]
_ScalarField = Callable[[_Vec3], float]
_Vec3Profile = Callable[[float], _Vec3]
_Vec3Field = Callable[[_Vec3], _Vec3]


class Environment:
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
        self._core = _Environment()
        if adiabatic_index is not None:
            self.adiabatic_index = adiabatic_index
        if specific_gas_constant is not None:
            self.specific_gas_constant = specific_gas_constant
        if temperature is not None:
            self.temperature = temperature
        if pressure is not None:
            self.pressure = pressure
        if gravity is not None:
            self.gravity = gravity
        if wind_velocity is not None:
            self.wind_velocity = wind_velocity

    @staticmethod
    def isa() -> Environment:
        environment = Environment.__new__(Environment)
        environment._core = _Environment.isa()
        return environment

    @property
    def adiabatic_index(self) -> float:
        return self._core.adiabatic_index()

    @property
    def specific_gas_constant(self) -> float:
        return self._core.specific_gas_constant()

    @property
    def temperature(self):
        return self._temperature

    @property
    def pressure(self):
        return self._pressure

    @property
    def gravity(self):
        return self._gravity

    @property
    def wind_velocity(self):
        return self._wind_velocity

    @adiabatic_index.setter
    def adiabatic_index(self, value: float):
        self._core.set_adiabatic_index(value)
        return self

    @specific_gas_constant.setter
    def specific_gas_constant(self, value: float):
        self._core.set_specific_gas_constant(value)

    @temperature.setter
    def temperature(self, value: float | _ScalarProfile | _ScalarField | Interpolator):
        if isinstance(value, Interpolator):
            self._core.set_temperature(
                cast(_ScalarProfile | _ScalarField, value.fn), value.step
            )
        elif isinstance(value, (int, float)):
            self._core.set_temperature(float(value))
        elif callable(value):
            self._core.set_temperature(value)

    @pressure.setter
    def pressure(
        self,
        value: float | _ScalarProfile | _ScalarField | Interpolator,
    ):
        if isinstance(value, Interpolator):
            self._core.set_pressure(
                cast(_ScalarProfile | _ScalarField, value.fn), value.step
            )
        elif isinstance(value, (int, float)):
            self._core.set_pressure(float(value))
        elif callable(value):
            self._core.set_pressure(value)

    @gravity.setter
    def gravity(
        self,
        value: ArrayLike | _Vec3Profile | _Vec3Field | Interpolator,
    ):
        if isinstance(value, Interpolator):
            self._core.set_gravity(
                cast(_Vec3Profile | _Vec3Field, value.fn), value.step
            )
        elif callable(value):
            self._core.set_gravity(value)
        else:
            self._core.set_gravity(np.asarray(value, dtype=np.float64))

    @wind_velocity.setter
    def wind_velocity(
        self,
        value: ArrayLike | _Vec3Profile | _Vec3Field | Interpolator,
    ):
        if isinstance(value, Interpolator):
            self._core.set_wind_velocity(
                cast(_Vec3Profile | _Vec3Field, value.fn), value.step
            )
        elif callable(value):
            self._core.set_wind_velocity(value)
        else:
            self._core.set_wind_velocity(np.asarray(value, dtype=np.float64))

    def _temperature(self, position: ArrayLike) -> float:
        return self._core.temperature(np.asarray(position, dtype=np.float64))

    def _pressure(self, position: ArrayLike) -> float:
        return self._core.pressure(np.asarray(position, dtype=np.float64))

    def _gravity(self, position: ArrayLike) -> _Vec3:
        return self._core.gravity(np.asarray(position, dtype=np.float64))

    def _wind_velocity(self, position: ArrayLike) -> _Vec3:
        return self._core.wind_velocity(np.asarray(position, dtype=np.float64))
