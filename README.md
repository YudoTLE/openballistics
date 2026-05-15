<div align="center">
   <picture>
      <img width="85%" alt="OpenBallistics" src="https://raw.githubusercontent.com/YudoTLE/openballistics/main/docs/assets/openballistics-logo-text.png" />
   </picture>

[![Python 3.9+](https://img.shields.io/badge/python-3.9+-blue.svg)](https://www.python.org/downloads/)
[![PyPI](https://img.shields.io/pypi/v/openballistics.svg)](https://pypi.org/project/openballistics/)
[![PyPI Downloads](https://img.shields.io/pepy/dt/openballistics?label=pypi%20downloads)](https://pepy.tech/project/openballistics)
[![C++](https://img.shields.io/badge/C++-17+-00599C.svg)](https://isocpp.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)

</div>

**OpenBallistics** is a lightweight, header-only C++ library with native Python bindings for high-fidelity external ballistics simulation. It is built to reliably answer two core questions: _Where will this projectile land?_ and _How do I need to aim to hit my target?_

### Capabilities

- **Trajectory Prediction:** Compute a projectile's final impact position or full sampled flight path over a given time of flight.
- **Direction Optimizer:** Find the best-effort launch direction or angles toward a stationary target at a known time of flight.
- **Direction Solver:** Find the required launch direction or angles to hit a stationary target, returning no solution if miss distance exceeds a threshold.
- **Time-of-Flight Optimizer:** Find the time of flight that brings the projectile closest to a stationary target, given a fixed launch direction.
- **Time-of-Flight Solver:** Find the time of flight that hits a stationary target within a miss distance threshold, given a fixed launch direction.
- **Intercept Solver:** Jointly solve launch direction and time of flight to intercept a moving target given its position as a function of time.

All solvers accept an optional platform velocity to account for a moving launcher, and support `earliest` or `latest` solution priority where applicable.

### Physics Models

- **Aerodynamics:** Mach-dependent drag, yaw drag, lift, Magnus force, overturning and spin damping moments — configurable as a constant, curve function, or lookup table.
- **Environment:** Temperature, pressure, gravity, and 3D wind — configurable as a constant, altitude profile, or spatial field.
- **Frame of Reference:** Local Cartesian, X-east, Y-north, Z-up.

> The trajectory model closely follows **STANAG 4355** and **McCoy's _Modern Exterior Ballistics_** as primary technical references.

---

## Python

### Install

```bash
pip install openballistics
```

### Example

```python
import numpy as np
import openballistics as ob

solver = ob.Ballistics(
    model="pm",
    integrator="rk45",
    environment="isa",
    projectile=ob.Projectile(mass=0.1, diameter=0.02, drag_force_coefficient=0.2),
)

def jet(t: float):
    return np.array([
        69.0 + 340.0 * t,
        420.0 + 1000.0 * np.sin(0.5 * t),
        1000.0 + 200.0 * np.cos(0.5 * t),
    ])

solution = solver.solve_launch_direction_and_time_of_flight(
    launch_position=[0.0, 0.0, 0.0], # z is up
    max_time_of_flight=67.0,
    muzzle_velocity=900.0,
    target_position=jet,
)

if not solution:
    print("No valid firing solution found.")
    exit(1)

direction, tof = solution
impact_pos = solver.compute_final_position(
    launch_position=[0.0, 0.0, 0.0],
    launch_direction=direction,
    muzzle_velocity=900.0,
    time_of_flight=tof,
)

np.set_printoptions(precision=3, suppress=True)
print(f"Launch Direction: {direction}")
print(f"Time of Flight  : {tof:.3f} s")
print(f"Bullet Intercept: {impact_pos} m")
print(f"Miss Distance   : {np.linalg.norm(impact_pos - jet(tof)):.3f} m")
```

<details>
<summary>Output</summary>

<pre>
Launch Direction: [0.61  0.643 0.464]
Time of Flight  : 3.666 s
Bullet Intercept: [1315.367 1385.849  948.179] m
Miss Distance   : 0.000 m
</pre>

</details>

---

## Contributors

<a href="https://github.com/YudoTLE/openballistics/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=YudoTLE/openballistics" />
</a>

## License

[MIT](LICENSE) © Ariyudo Pertama
