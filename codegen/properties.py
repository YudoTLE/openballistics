from .constants import INDENT
from .specs import Property


def property_setter(
    *,
    name: str,
    type: str,
    class_name: str,
    category: str,
    has_default: bool,
) -> list[str]:
    if category == "constant":
        return _constant_property_setter(
            name=name,
            type=type,
            has_default=has_default,
            class_name=class_name,
        )
    elif category == "curve":
        return _curve_property_setter(
            name=name,
            type=type,
            class_name=class_name,
        )
    elif category == "field":
        return _field_property_setter(
            name=name,
            type=type,
            class_name=class_name,
        )
    return []


def property_getter(
    *,
    name: str,
    type: str,
    category: str,
    has_default: bool,
) -> list[str]:
    if category == "constant":
        return _constant_property_getter(
            name=name,
            type=type,
            has_default=has_default,
        )
    elif category == "curve":
        return _curve_property_getter(name=name, type=type)
    elif category == "field":
        return _field_property_getter(name=name, type=type)
    return []


def property_member(
    *,
    name: str,
    type: str,
    category: str,
    has_default: bool,
) -> list[str]:
    if category == "constant":
        return _constant_property_member(name=name, type=type, has_default=has_default)
    elif category == "curve":
        return _curve_property_member(name=name, type=type)
    elif category == "field":
        return _field_property_member(name=name, type=type)
    return []


def property_default(
    *,
    properties: list[Property],
) -> list[str]:
    lines = [f"set_{p.name}({p.default});" for p in properties if p.default is not None]
    return lines


def _constant_property_setter(
    *,
    name: str,
    type: str,
    has_default: bool,
    class_name: str,
) -> list[str]:
    __ = INDENT
    lines = [
        f"/// @brief Sets the `{name}`",
        f"/// @param value Constant value.",
        f"/// @return Reference to the current object.",
    ]
    if has_default:
        lines += [
            f"{class_name} &set_{name}(const {type} value)",
            f"{{",
            f"{__}m_{name}_constant = value;",
            f"{__}return *this;",
            f"}}",
        ]
    else:
        lines += [
            f"{class_name} &set_{name}(const {type} value)",
            f"{{",
            f"{__}m_{name}_constant = value;",
            f"{__}m_{name}_source = 1;",
            f"{__}return *this;",
            f"}}",
        ]
    return lines


def _constant_property_getter(*, name: str, type: str, has_default: bool) -> list[str]:
    __ = INDENT
    lines = [
        f"/// @brief Gets the `{name}`.",
        f"/// @return `{name}`.",
    ]
    if has_default:
        lines += [
            f"[[nodiscard]] {type} {name}() const",
            f"{{",
            f"{__}return m_{name}_constant;",
            f"}}",
        ]
    else:
        lines += [
            f"[[nodiscard]] {type} {name}() const",
            f"{{",
            f"{__}if (m_{name}_source == 1) return m_{name}_constant;",
            f"{__}throw std::bad_optional_access{{}};",
            f"}}",
        ]
    return lines


def _constant_property_member(*, name: str, type: str, has_default: bool) -> list[str]:
    if has_default:
        lines = [
            f"{type} m_{name}_constant;",
        ]
    else:
        lines = [
            f"bool m_{name}_source = 0;",
            f"{type} m_{name}_constant;",
        ]
    return lines


def _curve_property_setter(*, name: str, type: str, class_name: str) -> list[str]:
    __ = INDENT
    lines = [
        f"/// @brief Sets the `{name}` as a constant value.",
        f"/// @param value Constant value.",
        f"/// @return Reference to the current object.",
        f"{class_name} &set_{name}(const {type} value)",
        f"{{",
        f"{__}m_{name}_constant = value;",
        f"{__}m_{name}_source = 1;",
        f"{__}return *this;",
        f"}}",
        f"/// @brief Sets the `{name}` as a function of Mach number.",
        f"/// @param curve Function of Mach number.",
        f"/// @return Reference to the current object.",
        f"{class_name} &set_{name}({type} (*curve)(scalar))",
        f"{{",
        f"{__}m_{name}_curve = curve;",
        f"{__}m_{name}_source = 2;",
        f"{__}return *this;",
        f"}}",
        f"/// @brief Sets the `{name}` as a function of Mach number.",
        f"/// @param curve Function of Mach number.",
        f"/// @return Reference to the current object.",
        f"{class_name} &set_{name}(std::function<{type}(scalar)> curve)",
        f"{{",
        f"{__}m_{name}_curve_virtual = std::move(curve);",
        f"{__}m_{name}_source = 3;",
        f"{__}return *this;",
        f"}}",
        f"/// @brief Sets the `{name}` as a linearly interpolated function of Mach number.",
        f"/// @param curve Function of Mach number.",
        f"/// @param interpolator_step Interpolation step size.",
        f"/// @return Reference to the current object.",
        f"{class_name} &set_{name}(std::function<{type}(scalar)> curve, const scalar interpolator_step)",
        f"{{",
        f"{__}m_{name}_curve_interpolator = interpolators::lazy_linear<{type}>(std::move(curve), interpolator_step);",
        f"{__}m_{name}_source = 4;",
        f"{__}return *this;",
        f"}}",
        f"/// @brief Sets the `{name}` as a linearly interpolated function of Mach number from a table.",
        f"/// @param mach_numbers Sorted list of Mach number sample points.",
        f"/// @param values Corresponding values at each Mach number sample point.",
        f"/// @return Reference to the current object.",
        f"{class_name} &set_{name}(std::vector<scalar> mach_numbers, std::vector<{type}> values)",
        f"{{",
        f"{__}m_{name}_table = interpolators::linear<{type}>(std::move(mach_numbers), std::move(values));",
        f"{__}m_{name}_source = 5;",
        f"{__}return *this;",
        f"}}",
    ]
    return lines


def _curve_property_getter(*, name: str, type: str) -> list[str]:
    __ = INDENT
    lines = [
        f"/// @brief Gets the `{name}` at a given Mach number.",
        f"/// @param mach Mach number.",
        f"/// @return `{name}` evaluated at the specified Mach number.",
        f"[[nodiscard]] {type} {name}(const scalar mach) const",
        f"{{",
        f"{__}switch (m_{name}_source)",
        f"{__}{{",
        f"{__}case 1: return m_{name}_constant;",
        f"{__}case 2: return m_{name}_curve(mach);",
        f"{__}case 3: return m_{name}_curve_virtual(mach);",
        f"{__}case 4: return m_{name}_curve_interpolator.evaluate(mach);",
        f"{__}case 5: return m_{name}_table.evaluate(mach);",
        f"{__}default: throw std::bad_optional_access{{}};",
        f"{__}}}",
        f"}}",
    ]
    return lines


def _curve_property_member(*, name: str, type: str) -> list[str]:
    lines = [
        f"uint8_t m_{name}_source = 0;",
        f"{type} m_{name}_constant;",
        f"{type} (*m_{name}_curve)(scalar);",
        f"std::function<{type}(scalar)> m_{name}_curve_virtual;",
        f"interpolators::lazy_linear<{type}> m_{name}_curve_interpolator;",
        f"interpolators::linear<{type}> m_{name}_table{{{{0.0}}, {{0.0}}}};",
    ]
    return lines


def _field_property_setter(*, name: str, type: str, class_name: str) -> list[str]:
    __ = INDENT
    lines = [
        f"/// @brief Sets the `{name}` as a constant value.",
        f"/// @param value Constant value.",
        f"/// @return Reference to the current object.",
        f"{class_name} &set_{name}({type} value)",
        f"{{",
        f"{__}m_{name}_constant = std::move(value);",
        f"{__}m_{name}_source = 1;",
        f"{__}return *this;",
        f"}}",
        f"/// @brief Sets the `{name}` as a function of altitude.",
        f"/// @param profile Function of altitude.",
        f"/// @return Reference to the current object.",
        f"{class_name} &set_{name}({type} (*profile)(scalar))",
        f"{{",
        f"{__}m_{name}_profile = profile;",
        f"{__}m_{name}_source = 2;",
        f"{__}return *this;",
        f"}}",
        f"/// @brief Sets the `{name}` as a function of position.",
        f"/// @param field Function of position.",
        f"/// @return Reference to the current object.",
        f"{class_name} &set_{name}({type} (*field)(const vector3 &))",
        f"{{",
        f"{__}m_{name}_field = field;",
        f"{__}m_{name}_source = 3;",
        f"{__}return *this;",
        f"}}",
        f"/// @brief Sets the `{name}` as a function of altitude.",
        f"/// @param profile Function of altitude.",
        f"/// @return Reference to the current object.",
        f"{class_name} &set_{name}(std::function<{type}(scalar)> profile)",
        f"{{",
        f"{__}m_{name}_profile_virtual = std::move(profile);",
        f"{__}m_{name}_source = 4;",
        f"{__}return *this;",
        f"}}",
        f"/// @brief Sets the `{name}` as a function of position.",
        f"/// @param field Function of position.",
        f"/// @return Reference to the current object.",
        f"{class_name} &set_{name}(std::function<{type}(vector3)> field)",
        f"{{",
        f"{__}m_{name}_field_property_virtual = std::move(field);",
        f"{__}m_{name}_source = 5;",
        f"{__}return *this;",
        f"}}",
        f"/// @brief Sets the `{name}` as a linearly interpolated function of altitude.",
        f"/// @param profile Function of altitude.",
        f"/// @param interpolator_step Interpolation step size.",
        f"/// @return Reference to the current object.",
        f"{class_name} &set_{name}(std::function<{type}(scalar)> profile, const scalar interpolator_step)",
        f"{{",
        f"{__}m_{name}_profile_interpolator = interpolators::lazy_linear<{type}>(std::move(profile), interpolator_step);",
        f"{__}m_{name}_source = 6;",
        f"{__}return *this;",
        f"}}",
        f"/// @brief Sets the `{name}` as a linearly interpolated function of position.",
        f"/// @param field Function of position.",
        f"/// @param interpolator_step Interpolation step size.",
        f"/// @return Reference to the current object.",
        f"{class_name} &set_{name}(std::function<{type}(vector3)> field, const scalar interpolator_step)",
        f"{{",
        f"{__}m_{name}_field_property_interpolator = interpolators::lazy_trilinear<{type}>(std::move(field), interpolator_step);",
        f"{__}m_{name}_source = 7;",
        f"{__}return *this;",
        f"}}",
    ]
    return lines


def _field_property_getter(*, name: str, type: str) -> list[str]:
    __ = INDENT
    lines = [
        f"/// @brief Gets the `{name}` at a given position.",
        f"/// @param position Position vector.",
        f"/// @return `{name}` evaluated at the specified position.",
        f"[[nodiscard]] {type} {name}(const vector3 &position) const",
        f"{{",
        f"{__}switch (m_{name}_source)",
        f"{__}{{",
        f"{__}case 1: return m_{name}_constant;",
        f"{__}case 2: return m_{name}_profile(position.z());",
        f"{__}case 3: return m_{name}_field(position);",
        f"{__}case 4: return m_{name}_profile_virtual(position.z());",
        f"{__}case 5: return m_{name}_field_property_virtual(position);",
        f"{__}case 6: return m_{name}_profile_interpolator.evaluate(position.z());",
        f"{__}case 7: return m_{name}_field_property_interpolator.evaluate(position);",
        f"{__}default: throw std::bad_optional_access{{}};",
        f"{__}}}",
        f"}}",
    ]
    return lines


def _field_property_member(*, name: str, type: str) -> list[str]:
    lines = [
        f"uint8_t m_{name}_source = 0;",
        f"{type} m_{name}_constant;",
        f"{type} (*m_{name}_profile)(scalar);",
        f"{type} (*m_{name}_field)(const vector3 &);",
        f"std::function<{type}(scalar)> m_{name}_profile_virtual;",
        f"std::function<{type}(vector3)> m_{name}_field_property_virtual;",
        f"interpolators::lazy_linear<{type}> m_{name}_profile_interpolator;",
        f"interpolators::lazy_trilinear<{type}> m_{name}_field_property_interpolator;",
    ]
    return lines
