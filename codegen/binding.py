from .spec import Property, Parameter


def ballistics_bind(
    *,
    class_name: str,
    nb_class_name: str,
    weapon_parameters: list[Parameter],
    base_indent: str = "",
    indent: str = "\t",
) -> list[str]:
    __ = indent
    forward = ", ".join([f"{p.qualifier} {p.type}" for p in weapon_parameters])
    forward_named = ", ".join(
        [f"{p.qualifier} {p.type} {p.name}" for p in weapon_parameters]
    )
    forward_args = ", ".join([p.name for p in weapon_parameters])
    lines = [
        f"{{",
        f"{__}using Class = {class_name};",
        f'{__}auto nb_class = nb::class_<Class>(m, "{nb_class_name}").def(nb::init<>());',
        f"{__}nb_class",
        f'{__}{__}.def_rw("integrator", &Class::integrator)',
        f'{__}{__}.def_rw("environment", &Class::environment)',
        f'{__}{__}.def_rw("projectile", &Class::projectile);',
        f"{__}nb_class",
        f'{__}{__}.def("compute_final_position", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, {forward}, scalar>(&Class::compute_final_position, nb::const_))',
        f'{__}{__}.def("compute_final_position", nb::overload_cast<const vector3 &, const angles &, const vector3 &, {forward}, scalar>(&Class::compute_final_position, nb::const_))',
        f'{__}{__}.def("compute_trajectory", nb::overload_cast<const vector3 &, const vector3 &, const vector3 &, {forward}, scalar, scalar>(&Class::compute_trajectory, nb::const_))',
        f'{__}{__}.def("optimize_time_of_flight", [](const Class &self, const vector3 &launch_position, const vector3 &launch_direction, const vector3 &platform_velocity, const vector3 &target_position, {forward_named}, const scalar min_time_of_flight, const scalar max_time_of_flight, const priority solution_priority, const uint32_t max_iterations) {{ return self.optimize_time_of_flight(launch_position, launch_direction, platform_velocity, target_position, {forward_args}, min_time_of_flight, max_time_of_flight, solution_priority, max_iterations); }})',
        f'{__}{__}.def("solve_time_of_flight", [](const Class &self, const vector3 &launch_position, const vector3 &launch_direction, const vector3 &platform_velocity, const vector3 &target_position, {forward_named}, const scalar min_time_of_flight, const scalar max_time_of_flight, const scalar miss_distance_threshold, const priority solution_priority, const uint32_t max_iterations) {{ return self.solve_time_of_flight(launch_position, launch_direction, platform_velocity, target_position, {forward_args}, min_time_of_flight, max_time_of_flight, miss_distance_threshold, solution_priority, max_iterations); }})',
        f'{__}{__}.def("optimize_launch_direction", [](const Class &self, const vector3 &launch_position, const vector3 &platform_velocity, const vector3 &target_position, {forward_named}, const scalar time_of_flight, const uint32_t max_iterations) {{ return self.optimize_launch_direction(launch_position, platform_velocity, target_position, {forward_args}, time_of_flight, max_iterations); }})',
        f'{__}{__}.def("optimize_launch_angles", [](const Class &self, const vector3 &launch_position, const vector3 &platform_velocity, const vector3 &target_position, {forward_named}, const scalar time_of_flight, const uint32_t max_iterations) {{ return self.optimize_launch_angles(launch_position, platform_velocity, target_position, {forward_args}, time_of_flight, max_iterations); }})',
        f'{__}{__}.def("solve_launch_direction", [](const Class &self, const vector3 &launch_position, const vector3 &platform_velocity, const vector3 &target_position, {forward_named}, const scalar time_of_flight, const scalar miss_distance_threshold, const uint32_t max_iterations) {{ return self.solve_launch_direction(launch_position, platform_velocity, target_position, {forward_args}, time_of_flight, miss_distance_threshold, max_iterations); }})',
        f'{__}{__}.def("solve_launch_angles", [](const Class &self, const vector3 &launch_position, const vector3 &platform_velocity, const vector3 &target_position, {forward_named}, const scalar time_of_flight, const scalar miss_distance_threshold, const uint32_t max_iterations) {{ return self.solve_launch_angles(launch_position, platform_velocity, target_position, {forward_args}, time_of_flight, miss_distance_threshold, max_iterations); }})',
        f'{__}{__}.def("optimize_time_of_flight", [](const Class &self, const vector3 &launch_position, const vector3 &launch_direction, const vector3 &platform_velocity, const std::function<vector3(scalar)> &target_position, {forward_named}, const scalar min_time_of_flight, const scalar max_time_of_flight, const priority solution_priority, const uint32_t max_iterations) {{ return self.optimize_time_of_flight(launch_position, launch_direction, platform_velocity, target_position, {forward_args}, min_time_of_flight, max_time_of_flight, solution_priority, max_iterations); }})',
        f'{__}{__}.def("solve_time_of_flight", [](const Class &self, const vector3 &launch_position, const vector3 &launch_direction, const vector3 &platform_velocity, const std::function<vector3(scalar)> &target_position, {forward_named}, const scalar min_time_of_flight, const scalar max_time_of_flight, const scalar miss_distance_threshold, const priority solution_priority, const uint32_t max_iterations) {{ return self.solve_time_of_flight(launch_position, launch_direction, platform_velocity, target_position, {forward_args}, min_time_of_flight, max_time_of_flight, miss_distance_threshold, solution_priority, max_iterations); }})',
        f'{__}{__}.def("optimize_launch_direction", [](const Class &self, const vector3 &launch_position, const vector3 &platform_velocity, const std::function<vector3(scalar)> &target_position, {forward_named}, const scalar time_of_flight, const uint32_t max_iterations) {{ return self.optimize_launch_direction(launch_position, platform_velocity, target_position, {forward_args}, time_of_flight, max_iterations); }})',
        f'{__}{__}.def("optimize_launch_angles", [](const Class &self, const vector3 &launch_position, const vector3 &platform_velocity, const std::function<vector3(scalar)> &target_position, {forward_named}, const scalar time_of_flight, const uint32_t max_iterations) {{ return self.optimize_launch_angles(launch_position, platform_velocity, target_position, {forward_args}, time_of_flight, max_iterations); }})',
        f'{__}{__}.def("solve_launch_direction", [](const Class &self, const vector3 &launch_position, const vector3 &platform_velocity, const std::function<vector3(scalar)> &target_position, {forward_named}, const scalar time_of_flight, const scalar miss_distance_threshold, const uint32_t max_iterations) {{ return self.solve_launch_direction(launch_position, platform_velocity, target_position, {forward_args}, time_of_flight, miss_distance_threshold, max_iterations); }})',
        f'{__}{__}.def("solve_launch_angles", [](const Class &self, const vector3 &launch_position, const vector3 &platform_velocity, const std::function<vector3(scalar)> &target_position, {forward_named}, const scalar time_of_flight, const scalar miss_distance_threshold, const uint32_t max_iterations) {{ return self.solve_launch_angles(launch_position, platform_velocity, target_position, {forward_args}, time_of_flight, miss_distance_threshold, max_iterations); }})',
        f'{__}{__}.def("solve_launch_direction_and_time_of_flight", [](const Class &self, const vector3 &launch_position, const vector3 &platform_velocity, const vector3 &target_position, {forward_named}, const scalar min_time_of_flight, const scalar max_time_of_flight, const scalar miss_distance_threshold, const priority solution_priority, const scalar time_of_flight_segment_size, const uint32_t time_of_flight_max_iterations, const uint32_t launch_direction_max_iterations) {{ return self.solve_launch_direction_and_time_of_flight(launch_position, platform_velocity, target_position, {forward_args}, min_time_of_flight, max_time_of_flight, miss_distance_threshold, solution_priority, time_of_flight_segment_size, time_of_flight_max_iterations, launch_direction_max_iterations); }})',
        f'{__}{__}.def("solve_launch_angles_and_time_of_flight", [](const Class &self, const vector3 &launch_position, const vector3 &platform_velocity, const vector3 &target_position, {forward_named}, const scalar min_time_of_flight, const scalar max_time_of_flight, const scalar miss_distance_threshold, const priority solution_priority, const scalar time_of_flight_segment_size, const uint32_t time_of_flight_max_iterations, const uint32_t launch_direction_max_iterations) {{ return self.solve_launch_angles_and_time_of_flight(launch_position, platform_velocity, target_position, {forward_args}, min_time_of_flight, max_time_of_flight, miss_distance_threshold, solution_priority, time_of_flight_segment_size, time_of_flight_max_iterations, launch_direction_max_iterations); }})',
        f'{__}{__}.def("solve_launch_direction_and_time_of_flight", [](const Class &self, const vector3 &launch_position, const vector3 &platform_velocity, const std::function<vector3(scalar)> &target_position, {forward_named}, const scalar min_time_of_flight, const scalar max_time_of_flight, const scalar miss_distance_threshold, const priority solution_priority, const scalar time_of_flight_segment_size, const uint32_t time_of_flight_max_iterations, const uint32_t launch_direction_max_iterations) {{ return self.solve_launch_direction_and_time_of_flight(launch_position, platform_velocity, target_position, {forward_args}, min_time_of_flight, max_time_of_flight, miss_distance_threshold, solution_priority, time_of_flight_segment_size, time_of_flight_max_iterations, launch_direction_max_iterations); }})',
        f'{__}{__}.def("solve_launch_angles_and_time_of_flight", [](const Class &self, const vector3 &launch_position, const vector3 &platform_velocity, const std::function<vector3(scalar)> &target_position, {forward_named}, const scalar min_time_of_flight, const scalar max_time_of_flight, const scalar miss_distance_threshold, const priority solution_priority, const scalar time_of_flight_segment_size, const uint32_t time_of_flight_max_iterations, const uint32_t launch_direction_max_iterations) {{ return self.solve_launch_angles_and_time_of_flight(launch_position, platform_velocity, target_position, {forward_args}, min_time_of_flight, max_time_of_flight, miss_distance_threshold, solution_priority, time_of_flight_segment_size, time_of_flight_max_iterations, launch_direction_max_iterations); }});',
        f"}}",
    ]
    return [base_indent + line for line in lines]


def integrator_bind(
    *,
    class_name: str,
    nb_class_name: str,
    properties: list[Property],
    base_indent: str = "",
    indent: str = "\t",
) -> list[str]:
    __ = indent
    property_binds = [
        line
        for property in properties
        for line in _property_bind(
            name=property.name,
            type=property.type,
            category=property.category,
            base_indent=indent,
            indent=indent,
        )
    ]
    lines: list[str] = [
        f"{{",
        f"{__}using Class = integrator::{class_name};",
        f'{__}auto nb_class = nb::class_<Class>(m, "{nb_class_name}").def(nb::init<>());',
        *property_binds,
        f"}}",
    ]
    return [base_indent + line for line in lines]


def environment_bind(
    *,
    nb_class_name: str,
    properties: list[Property],
    base_indent: str = "",
    indent: str = "\t",
) -> list[str]:
    __ = indent
    property_binds = [
        line
        for property in properties
        for line in _property_bind(
            name=property.name,
            type=property.type,
            category=property.category,
            base_indent=indent,
            indent=indent,
        )
    ]
    lines: list[str] = [
        f"{{",
        f"{__}using Class = environment;",
        f'{__}auto nb_class = nb::class_<Class>(m, "{nb_class_name}").def(nb::init<>());',
        *property_binds,
        f"}}",
    ]
    return [base_indent + line for line in lines]


def projectile_bind(
    *,
    nb_class_name: str,
    properties: list[Property],
    base_indent: str = "",
    indent: str = "\t",
) -> list[str]:
    __ = indent
    property_binds = [
        line
        for property in properties
        for line in _property_bind(
            name=property.name,
            type=property.type,
            category=property.category,
            base_indent=indent,
            indent=indent,
        )
    ]
    lines: list[str] = [
        f"{{",
        f"{__}using Class = projectile;",
        f'{__}auto nb_class = nb::class_<Class>(m, "{nb_class_name}").def(nb::init<>());',
        *property_binds,
        f"}}",
    ]
    return [base_indent + line for line in lines]


def _property_bind(
    *,
    name: str,
    type: str,
    category: str,
    base_indent: str,
    indent: str,
) -> list[str]:
    if category == "constant":
        return _constant_property_bind(
            name=name,
            base_indent=base_indent,
            indent=indent,
        )
    dispatch = {
        "curve": _curve_property_bind,
        "field": _field_property_bind,
    }

    return dispatch[category](
        name=name,
        type=type,
        base_indent=base_indent,
        indent=indent,
    )


def _constant_property_bind(*, name: str, base_indent: str, indent: str) -> list[str]:
    __ = indent
    lines: list[str] = [
        f"nb_class",
        f'{__}.def("set_{name}", &Class::set_{name})',
        f'{__}.def("{name}", &Class::{name});',
    ]
    return [base_indent + line for line in lines]


def _curve_property_bind(
    *, name: str, type: str, base_indent: str, indent: str
) -> list[str]:
    __ = indent
    lines: list[str] = [
        f"nb_class",
        f'{__}.def("set_{name}", nb::overload_cast<{type}>(&Class::set_{name}))',
        f'{__}.def("set_{name}", [](Class &self, std::function<{type}(scalar)> curve) -> Class & {{ return self.set_{name}(std::move(curve)); }})',
        f'{__}.def("set_{name}", [](Class &self, std::function<{type}(scalar)> curve, scalar interpolator_step) -> Class & {{ return self.set_{name}(std::move(curve), interpolator_step); }})',
        f'{__}.def("set_{name}", [](Class &self, std::vector<scalar> keys, std::vector<{type}> values) -> Class & {{ return self.set_{name}(std::move(keys), std::move(values)); }})',
        f'{__}.def("{name}", &Class::{name});',
    ]
    return [base_indent + line for line in lines]


def _field_property_bind(
    *, name: str, type: str, base_indent: str, indent: str
) -> list[str]:
    __ = indent
    lines: list[str] = [
        f"nb_class",
        f'{__}.def("set_{name}", nb::overload_cast<{type}>(&Class::set_{name}))',
        f'{__}.def("set_{name}", [](Class &self, std::function<{type}(scalar)> profile) -> Class & {{ return self.set_{name}(std::move(profile)); }})',
        f'{__}.def("set_{name}", [](Class &self, std::function<{type}(vector3)> field) -> Class & {{ return self.set_{name}(std::move(field)); }})',
        f'{__}.def("set_{name}", [](Class &self, std::function<{type}(scalar)> profile, scalar interpolator_step) -> Class & {{ return self.set_{name}(std::move(profile), interpolator_step); }})',
        f'{__}.def("set_{name}", [](Class &self, std::function<{type}(vector3)> field, scalar interpolator_step) -> Class & {{ return self.set_{name}(std::move(field), interpolator_step); }})',
        f'{__}.def("{name}", &Class::{name});',
    ]
    return [base_indent + line for line in lines]
