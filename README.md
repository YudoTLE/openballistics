<div align="center">
   <picture>
      <img width="85%" alt="OpenBallistics" src="https://raw.githubusercontent.com/YudoTLE/openballistics/main/docs/assets/openballistics-logo-text.svg" />
   </picture>

[![Python 3.9+](https://img.shields.io/badge/python-3.9+-blue.svg)](https://www.python.org/downloads/)
[![PyPI](https://img.shields.io/pypi/v/openballistics.svg)](https://pypi.org/project/openballistics/)
[![C++](https://img.shields.io/badge/C++-17+-00599C.svg)](https://isocpp.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)

</div>

**OpenBallistics** is a lightweight, header-only C++ library with native Python bindings for high-fidelity external ballistics simulation. It is built to reliably answer two core questions: _Where will this projectile land?_ and _How do I need to aim to hit my target?_

#### Capabilities:

- **Trajectory Prediction:** Calculate the flight path and final impact point of a projectile.
- **Targeting Solver:** Determine required launch angles and time-of-flight to hit moving targets.

#### Physics Models

- **Aerodynamics:** Projectile flight involving drag, lift, and spin-induced drift.
- **Environment:** Atmospheric conditions including 3D wind, gravity, and thermodynamic profiles.

---

## Dependencies

- **Eigen3**
- **Boost**

## Contributors

<a href="https://github.com/YudoTLE/openballistics/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=YudoTLE/openballistics" />
</a>

## License

[MIT](LICENSE) © Ariyudo Pertama
