from importlib.metadata import version

from .ballistics import Ballistics
from .integrator import RK4, RK45
from .environment import Environment
from .projectile import Projectile
from .types import Angles, Interpolator, Table
from .enums import Priority

__version__ = version("openballistics")

__all__ = [
    "Ballistics",
    "RK4",
    "RK45",
    "Environment",
    "Projectile",
    "Angles",
    "Priority",
    "Interpolator",
    "Table",
]
