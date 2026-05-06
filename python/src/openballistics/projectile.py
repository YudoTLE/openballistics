from __future__ import annotations

from collections.abc import Callable
from typing import cast

from ._core import Projectile as _Projectile  # type: ignore
from .types import Interpolator, Table

_ScalarCurve = Callable[[float], float]


class Projectile:
    _core: _Projectile

    def __init__(
        self,
        *,
        mass: float | None = None,
        diameter: float | None = None,
        axial_moment_of_inertia: float | None = None,
        form_factor: float | None = None,
        drag_factor: float | None = None,
        lift_factor: float | None = None,
        yaw_drag_factor: float | None = None,
        magnus_force_factor: float | None = None,
        drag_force_coefficient: (
            float | _ScalarCurve | Interpolator | Table | None
        ) = None,
        quadratic_yaw_drag_force_coefficient: (
            float | _ScalarCurve | Interpolator | Table | None
        ) = None,
        quartic_yaw_drag_force_coefficient: (
            float | _ScalarCurve | Interpolator | Table | None
        ) = None,
        lift_force_coefficient: (
            float | _ScalarCurve | Interpolator | Table | None
        ) = None,
        cubic_lift_force_coefficient: (
            float | _ScalarCurve | Interpolator | Table | None
        ) = None,
        quintic_lift_force_coefficient: (
            float | _ScalarCurve | Interpolator | Table | None
        ) = None,
        magnus_force_coefficient: (
            float | _ScalarCurve | Interpolator | Table | None
        ) = None,
        overturning_moment_coefficient: (
            float | _ScalarCurve | Interpolator | Table | None
        ) = None,
        cubic_overturning_moment_coefficient: (
            float | _ScalarCurve | Interpolator | Table | None
        ) = None,
        spin_damping_moment_coefficient: (
            float | _ScalarCurve | Interpolator | Table | None
        ) = None,
    ) -> None:
        self._core = _Projectile()
        if mass is not None:
            self.set_mass(mass)
        if diameter is not None:
            self.set_diameter(diameter)
        if axial_moment_of_inertia is not None:
            self.set_axial_moment_of_inertia(axial_moment_of_inertia)
        if form_factor is not None:
            self.set_form_factor(form_factor)
        if drag_factor is not None:
            self.set_drag_factor(drag_factor)
        if lift_factor is not None:
            self.set_lift_factor(lift_factor)
        if yaw_drag_factor is not None:
            self.set_yaw_drag_factor(yaw_drag_factor)
        if magnus_force_factor is not None:
            self.set_magnus_force_factor(magnus_force_factor)
        if drag_force_coefficient is not None:
            self.set_drag_force_coefficient(drag_force_coefficient)
        if quadratic_yaw_drag_force_coefficient is not None:
            self.set_quadratic_yaw_drag_force_coefficient(
                quadratic_yaw_drag_force_coefficient
            )
        if quartic_yaw_drag_force_coefficient is not None:
            self.set_quartic_yaw_drag_force_coefficient(
                quartic_yaw_drag_force_coefficient
            )
        if lift_force_coefficient is not None:
            self.set_lift_force_coefficient(lift_force_coefficient)
        if cubic_lift_force_coefficient is not None:
            self.set_cubic_lift_force_coefficient(cubic_lift_force_coefficient)
        if quintic_lift_force_coefficient is not None:
            self.set_quintic_lift_force_coefficient(quintic_lift_force_coefficient)
        if magnus_force_coefficient is not None:
            self.set_magnus_force_coefficient(magnus_force_coefficient)
        if overturning_moment_coefficient is not None:
            self.set_overturning_moment_coefficient(overturning_moment_coefficient)
        if cubic_overturning_moment_coefficient is not None:
            self.set_cubic_overturning_moment_coefficient(
                cubic_overturning_moment_coefficient
            )
        if spin_damping_moment_coefficient is not None:
            self.set_spin_damping_moment_coefficient(spin_damping_moment_coefficient)

    def set_mass(self, value: float, /) -> Projectile:
        self._core.set_mass(value)
        return self

    def set_diameter(self, value: float, /) -> Projectile:
        self._core.set_diameter(value)
        return self

    def set_axial_moment_of_inertia(self, value: float, /) -> Projectile:
        self._core.set_axial_moment_of_inertia(value)
        return self

    def set_form_factor(self, value: float, /) -> Projectile:
        self._core.set_form_factor(value)
        return self

    def set_drag_factor(self, value: float, /) -> Projectile:
        self._core.set_drag_factor(value)
        return self

    def set_lift_factor(self, value: float, /) -> Projectile:
        self._core.set_lift_factor(value)
        return self

    def set_yaw_drag_factor(self, value: float, /) -> Projectile:
        self._core.set_yaw_drag_factor(value)
        return self

    def set_magnus_force_factor(self, value: float, /) -> Projectile:
        self._core.set_magnus_force_factor(value)
        return self

    def _set_scalar_coefficient(
        self,
        setter: str,
        value: float | _ScalarCurve | Interpolator | Table,
    ) -> None:
        fn = getattr(self._core, setter)
        if isinstance(value, Table):
            fn(value.keys, value.values)
        elif isinstance(value, Interpolator):
            fn(cast(_ScalarCurve, value.fn), value.step)
        elif isinstance(value, (int, float)):
            fn(float(value))
        elif callable(value):
            fn(value)

    def set_drag_force_coefficient(
        self,
        value: float | _ScalarCurve | Interpolator | Table,
        /,
    ) -> Projectile:
        self._set_scalar_coefficient("set_drag_force_coefficient", value)
        return self

    def set_quadratic_yaw_drag_force_coefficient(
        self,
        value: float | _ScalarCurve | Interpolator | Table,
        /,
    ) -> Projectile:
        self._set_scalar_coefficient("set_quadratic_yaw_drag_force_coefficient", value)
        return self

    def set_quartic_yaw_drag_force_coefficient(
        self,
        value: float | _ScalarCurve | Interpolator | Table,
        /,
    ) -> Projectile:
        self._set_scalar_coefficient("set_quartic_yaw_drag_force_coefficient", value)
        return self

    def set_lift_force_coefficient(
        self,
        value: float | _ScalarCurve | Interpolator | Table,
        /,
    ) -> Projectile:
        self._set_scalar_coefficient("set_lift_force_coefficient", value)
        return self

    def set_cubic_lift_force_coefficient(
        self,
        value: float | _ScalarCurve | Interpolator | Table,
        /,
    ) -> Projectile:
        self._set_scalar_coefficient("set_cubic_lift_force_coefficient", value)
        return self

    def set_quintic_lift_force_coefficient(
        self,
        value: float | _ScalarCurve | Interpolator | Table,
        /,
    ) -> Projectile:
        self._set_scalar_coefficient("set_quintic_lift_force_coefficient", value)
        return self

    def set_magnus_force_coefficient(
        self,
        value: float | _ScalarCurve | Interpolator | Table,
        /,
    ) -> Projectile:
        self._set_scalar_coefficient("set_magnus_force_coefficient", value)
        return self

    def set_overturning_moment_coefficient(
        self,
        value: float | _ScalarCurve | Interpolator | Table,
        /,
    ) -> Projectile:
        self._set_scalar_coefficient("set_overturning_moment_coefficient", value)
        return self

    def set_cubic_overturning_moment_coefficient(
        self,
        value: float | _ScalarCurve | Interpolator | Table,
        /,
    ) -> Projectile:
        self._set_scalar_coefficient("set_cubic_overturning_moment_coefficient", value)
        return self

    def set_spin_damping_moment_coefficient(
        self,
        value: float | _ScalarCurve | Interpolator | Table,
        /,
    ) -> Projectile:
        self._set_scalar_coefficient("set_spin_damping_moment_coefficient", value)
        return self

    def mass(self) -> float:
        return self._core.mass()

    def diameter(self) -> float:
        return self._core.diameter()

    def axial_moment_of_inertia(self) -> float:
        return self._core.axial_moment_of_inertia()

    def form_factor(self) -> float:
        return self._core.form_factor()

    def drag_factor(self) -> float:
        return self._core.drag_factor()

    def lift_factor(self) -> float:
        return self._core.lift_factor()

    def yaw_drag_factor(self) -> float:
        return self._core.yaw_drag_factor()

    def magnus_force_factor(self) -> float:
        return self._core.magnus_force_factor()

    def drag_force_coefficient(self, mach: float, /) -> float:
        return self._core.drag_force_coefficient(mach)

    def quadratic_yaw_drag_force_coefficient(self, mach: float, /) -> float:
        return self._core.quadratic_yaw_drag_force_coefficient(mach)

    def quartic_yaw_drag_force_coefficient(self, mach: float, /) -> float:
        return self._core.quartic_yaw_drag_force_coefficient(mach)

    def lift_force_coefficient(self, mach: float, /) -> float:
        return self._core.lift_force_coefficient(mach)

    def cubic_lift_force_coefficient(self, mach: float, /) -> float:
        return self._core.cubic_lift_force_coefficient(mach)

    def quintic_lift_force_coefficient(self, mach: float, /) -> float:
        return self._core.quintic_lift_force_coefficient(mach)

    def magnus_force_coefficient(self, mach: float, /) -> float:
        return self._core.magnus_force_coefficient(mach)

    def overturning_moment_coefficient(self, mach: float, /) -> float:
        return self._core.overturning_moment_coefficient(mach)

    def cubic_overturning_moment_coefficient(self, mach: float, /) -> float:
        return self._core.cubic_overturning_moment_coefficient(mach)

    def spin_damping_moment_coefficient(self, mach: float, /) -> float:
        return self._core.spin_damping_moment_coefficient(mach)
