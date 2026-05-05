from __future__ import annotations

from ._core import RK4 as _RK4, RKDP5 as _RKDP5# type: ignore


class Integrator:
    pass


class RK4(Integrator):
    def __init__(self, *, step: float = 1e-3) -> None:
        self._core = _RK4()
        self._core.set_step(step)

    def set_step(self, value: float, /) -> RK4:
        self._core.set_step(value)
        return self

    def step(self) -> float:
        return self._core.step()


class RKDP5(Integrator):
    def __init__(
        self,
        *,
        absolute_tolerance: float = 1e-6,
        relative_tolerance: float = 1e-6,
        max_step: float = float("inf"),
        first_step: float = 1e-3,
    ) -> None:
        self._core = _RKDP5()
        self._core.set_absolute_tolerance(absolute_tolerance)
        self._core.set_relative_tolerance(relative_tolerance)
        self._core.set_max_step(max_step)
        self._core.set_first_step(first_step)

    def set_absolute_tolerance(self, value: float, /) -> RKDP5:
        self._core.set_absolute_tolerance(value)
        return self

    def set_relative_tolerance(self, value: float, /) -> RKDP5:
        self._core.set_relative_tolerance(value)
        return self

    def set_max_step(self, value: float, /) -> RKDP5:
        self._core.set_max_step(value)
        return self

    def set_first_step(self, value: float, /) -> RKDP5:
        self._core.set_first_step(value)
        return self
