from __future__ import annotations

from ._core import RK4 as _RK4, RK45 as _RK45  # type: ignore


class Integrator:
    pass


class RK4(Integrator):
    def __init__(self, *, step: float = 1e-3) -> None:
        self._core = _RK4()
        self.step = step

    @property
    def step(self) -> float:
        return self._core.step()

    @step.setter
    def step(self, value: float):
        self._core.set_step(value)


class RK45(Integrator):
    def __init__(
        self,
        *,
        absolute_tolerance: float = 1e-6,
        relative_tolerance: float = 1e-6,
        max_step: float = float("inf"),
        first_step: float = 1e-3,
    ) -> None:
        self._core = _RK45()
        self.absolute_tolerance = absolute_tolerance
        self.relative_tolerance = relative_tolerance
        self.max_step = max_step
        self.first_step = first_step

    @property
    def absolute_tolerance(self) -> float:
        return self._core.absolute_tolerance()

    @property
    def relative_tolerance(self) -> float:
        return self._core.relative_tolerance()

    @property
    def max_step(self) -> float:
        return self._core.max_step()

    @property
    def first_step(self) -> float:
        return self._core.first_step()

    @absolute_tolerance.setter
    def absolute_tolerance(self, value: float):
        self._core.set_absolute_tolerance(value)

    @relative_tolerance.setter
    def relative_tolerance(self, value: float):
        self._core.set_relative_tolerance(value)

    @max_step.setter
    def max_step(self, value: float):
        self._core.set_max_step(value)

    @first_step.setter
    def first_step(self, value: float):
        self._core.set_first_step(value)
