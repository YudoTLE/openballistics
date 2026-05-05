from __future__ import annotations

from collections.abc import Callable
from typing import cast

from ._core import RealisticProjectile as _RealisticProjectile  # type: ignore
from .types import Interpolated, Table

_ScalarCurve = Callable[[float], float]


class Projectile:
    pass


class RealisticProjectile(Projectile):
    _core: _RealisticProjectile

    def __init__(
        self,
        *,
        mass: float | None = None,
        diameter: float | None = None,
        reference_area: float | None = None,
        axial_moment_of_inertia: float | None = None,
        drag_force_coefficient: (
            float | _ScalarCurve | Interpolated | Table | None
        ) = None,
        lift_force_coefficient: (
            float | _ScalarCurve | Interpolated | Table | None
        ) = None,
        overturning_moment_coefficient: (
            float | _ScalarCurve | Interpolated | Table | None
        ) = None,
        spin_damping_moment_coefficient: (
            float | _ScalarCurve | Interpolated | Table | None
        ) = None,
        magnus_force_coefficient: (
            float | _ScalarCurve | Interpolated | Table | None
        ) = None,
    ) -> None:
        self._core = _RealisticProjectile()
        if mass is not None:
            self.set_mass(mass)
        if diameter is not None:
            self.set_diameter(diameter)
        if reference_area is not None:
            self.set_reference_area(reference_area)
        if axial_moment_of_inertia is not None:
            self.set_axial_moment_of_inertia(axial_moment_of_inertia)
        if drag_force_coefficient is not None:
            self.set_drag_force_coefficient(drag_force_coefficient)
        if lift_force_coefficient is not None:
            self.set_lift_force_coefficient(lift_force_coefficient)
        if overturning_moment_coefficient is not None:
            self.set_overturning_moment_coefficient(overturning_moment_coefficient)
        if spin_damping_moment_coefficient is not None:
            self.set_spin_damping_moment_coefficient(spin_damping_moment_coefficient)
        if magnus_force_coefficient is not None:
            self.set_magnus_force_coefficient(magnus_force_coefficient)

    def set_mass(self, value: float, /) -> RealisticProjectile:
        self._core.set_mass(value)
        return self

    def set_diameter(self, value: float, /) -> RealisticProjectile:
        self._core.set_diameter(value)
        return self

    def set_reference_area(self, value: float, /) -> RealisticProjectile:
        self._core.set_reference_area(value)
        return self

    def set_axial_moment_of_inertia(self, value: float, /) -> RealisticProjectile:
        self._core.set_axial_moment_of_inertia(value)
        return self

    def _set_scalar_coefficient(
        self,
        setter: str,
        value: float | _ScalarCurve | Interpolated | Table,
    ) -> None:
        fn = getattr(self._core, setter)
        if isinstance(value, Table):
            fn(value.keys, value.values)
        elif isinstance(value, Interpolated):
            fn(cast(_ScalarCurve, value.fn), value.step)
        elif isinstance(value, (int, float)):
            fn(float(value))
        elif callable(value):
            fn(value)

    def set_drag_force_coefficient(
        self,
        value: float | _ScalarCurve | Interpolated | Table,
        /,
    ) -> RealisticProjectile:
        self._set_scalar_coefficient("set_drag_force_coefficient", value)
        return self

    def set_lift_force_coefficient(
        self,
        value: float | _ScalarCurve | Interpolated | Table,
        /,
    ) -> RealisticProjectile:
        self._set_scalar_coefficient("set_lift_force_coefficient", value)
        return self

    def set_overturning_moment_coefficient(
        self,
        value: float | _ScalarCurve | Interpolated | Table,
        /,
    ) -> RealisticProjectile:
        self._set_scalar_coefficient("set_overturning_moment_coefficient", value)
        return self

    def set_spin_damping_moment_coefficient(
        self,
        value: float | _ScalarCurve | Interpolated | Table,
        /,
    ) -> RealisticProjectile:
        self._set_scalar_coefficient("set_spin_damping_moment_coefficient", value)
        return self

    def set_magnus_force_coefficient(
        self,
        value: float | _ScalarCurve | Interpolated | Table,
        /,
    ) -> RealisticProjectile:
        self._set_scalar_coefficient("set_magnus_force_coefficient", value)
        return self

    def mass(self) -> float:
        return self._core.mass()

    def diameter(self) -> float:
        return self._core.diameter()

    def reference_area(self) -> float:
        return self._core.reference_area()

    def axial_moment_of_inertia(self) -> float:
        return self._core.axial_moment_of_inertia()

    def drag_force_coefficient(self, mach: float, /) -> float:
        return self._core.drag_force_coefficient(mach)

    def lift_force_coefficient(self, mach: float, /) -> float:
        return self._core.lift_force_coefficient(mach)

    def overturning_moment_coefficient(self, mach: float, /) -> float:
        return self._core.overturning_moment_coefficient(mach)

    def spin_damping_moment_coefficient(self, mach: float, /) -> float:
        return self._core.spin_damping_moment_coefficient(mach)

    def magnus_force_coefficient(self, mach: float, /) -> float:
        return self._core.magnus_force_coefficient(mach)

    @staticmethod
    def m56a3() -> RealisticProjectile:
        projectile = RealisticProjectile.__new__(RealisticProjectile)
        projectile._core = _RealisticProjectile.m56a3()
        return projectile
