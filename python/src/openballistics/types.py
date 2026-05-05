from __future__ import annotations

from collections.abc import Callable
from typing import Union

import numpy as np
from numpy.typing import NDArray

_Vec3 = NDArray[np.float64]
_ScalarCurve = Callable[[float], float]
_ScalarField = Callable[[_Vec3], float]
_Vec3Curve = Callable[[float], _Vec3]
_Vec3Field = Callable[[_Vec3], _Vec3]


class Interpolator:
    def __init__(
        self, fn: Union[_ScalarCurve, _ScalarField, _Vec3Curve, _Vec3Field], step: float
    ) -> None:
        self.fn = fn
        self.step = step


class Table:
    def __init__(self, keys: list[float], values: list[float]) -> None:
        self.keys = keys
        self.values = values

    @classmethod
    def from_pairs(cls, data: list[tuple[float, float]]) -> Table:
        return cls([p[0] for p in data], [p[1] for p in data])
