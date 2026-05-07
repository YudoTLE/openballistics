from .property import *
from .spec import *
from .patcher import *
from .api import *
from .definition import *
from .binding import *
from pathlib import Path

ROOT = Path(__file__).parent.parent
SPEC = ROOT / "codegen" / "spec"

trajectory_model_specs = load_trajectory_model_specs(SPEC / "trajectory_model")
integrator_specs = load_integrator_specs(SPEC / "integrator")
environment_spec = load_environment_spec(SPEC / "environment.yml")
projectile_spec = load_projectile_spec(SPEC / "projectile.yml")

patches: list[tuple[str, str]] = []


def generate_binding():
    global patches

    BASE_INDENT = "\t"
    BIND_CODE = "BIND"

    bind_patch: list[str] = []

    for trajectory_model_spec in trajectory_model_specs:
        for integrator_spec in integrator_specs:
            bind_patch.append(
                "\n".join(
                    ballistics_bind(
                        class_name=f"ballistics<trajectory_model::{trajectory_model_spec.class_name}, integrator::{integrator_spec.class_name}>",
                        nb_class_name=f"{trajectory_model_spec.nb_class_name}{integrator_spec.nb_class_name}",
                        weapon_parameters=trajectory_model_spec.weapon_parameters,
                        base_indent=BASE_INDENT,
                    )
                )
            )

    for integrator_spec in integrator_specs:
        bind_patch.append(
            "\n".join(
                integrator_bind(
                    class_name=integrator_spec.class_name,
                    nb_class_name=integrator_spec.nb_class_name,
                    properties=integrator_spec.properties,
                    base_indent=BASE_INDENT,
                )
            )
        )

    bind_patch.append(
        "\n".join(
            environment_bind(
                nb_class_name=environment_spec.nb_class_name,
                properties=environment_spec.properties,
                base_indent=BASE_INDENT,
            )
        )
    )

    bind_patch.append(
        "\n".join(
            projectile_bind(
                nb_class_name=projectile_spec.nb_class_name,
                properties=projectile_spec.properties,
                base_indent=BASE_INDENT,
            )
        )
    )

    patches.append((BIND_CODE, "\n".join(bind_patch)))


def generate_trajectory_model_core():
    global patches

    BASE_INDENT = "\t\t\t"

    for trajectory_model_spec in trajectory_model_specs:

        DEFINITION_CODE = trajectory_model_spec.id + "-DEF"

        definition_patch = "\n".join(
            model_weapon_definition(
                weapon_parameters=trajectory_model_spec.weapon_parameters,
                base_indent=BASE_INDENT,
            )
        )

        patches.append((DEFINITION_CODE, definition_patch))


def generate_integrator_core():
    global patches

    BASE_INDENT = "\t\t"
    INDENT = "\t"

    for integrator_spec in integrator_specs:
        DEFAULT_CODE = integrator_spec.id + "-DEF"
        SETTER_CODE = integrator_spec.id + "-SET"
        GETTER_CODE = integrator_spec.id + "-GET"
        MEMBER_CODE = integrator_spec.id + "-MEM"

        setter_patch: list[str] = []
        getter_patch: list[str] = []
        member_patch: list[str] = []

        default_patch = "\n".join(
            property_default(
                properties=integrator_spec.properties, base_indent=BASE_INDENT + INDENT
            )
        )
        for property in integrator_spec.properties:
            setter_patch.append(
                "\n".join(
                    property_setter(
                        name=property.name,
                        type=property.type,
                        category=property.category,
                        has_default=property.default is not None,
                        class_name=integrator_spec.class_name,
                        base_indent=BASE_INDENT,
                        indent=INDENT,
                    )
                )
            )
            getter_patch.append(
                "\n".join(
                    property_getter(
                        name=property.name,
                        type=property.type,
                        category=property.category,
                        has_default=property.default is not None,
                        base_indent=BASE_INDENT,
                        indent=INDENT,
                    )
                )
            )
            member_patch.append(
                "\n".join(
                    property_member(
                        name=property.name,
                        type=property.type,
                        category=property.category,
                        has_default=property.default is not None,
                        base_indent=BASE_INDENT,
                    )
                )
            )

        patches += [
            (DEFAULT_CODE, default_patch),
            (SETTER_CODE, "\n\n".join(setter_patch)),
            (GETTER_CODE, "\n\n".join(getter_patch)),
            (MEMBER_CODE, "\n\n".join(member_patch)),
        ]


def generate_environemnt_core():
    global patches

    BASE_INDENT = "\t\t"
    INDENT = "\t"

    DEFAULT_CODE = environment_spec.id + "-DEF"
    SETTER_CODE = environment_spec.id + "-SET"
    GETTER_CODE = environment_spec.id + "-GET"
    MEMBER_CODE = environment_spec.id + "-MEM"

    setter_patch: list[str] = []
    getter_patch: list[str] = []
    member_patch: list[str] = []

    default_patch = "\n".join(
        property_default(
            properties=environment_spec.properties, base_indent=BASE_INDENT + INDENT
        )
    )
    for property in environment_spec.properties:
        setter_patch.append(
            "\n".join(
                property_setter(
                    name=property.name,
                    type=property.type,
                    category=property.category,
                    has_default=property.default is not None,
                    class_name="environment",
                    base_indent=BASE_INDENT,
                    indent=INDENT,
                )
            )
        )
        getter_patch.append(
            "\n".join(
                property_getter(
                    name=property.name,
                    type=property.type,
                    category=property.category,
                    has_default=property.default is not None,
                    base_indent=BASE_INDENT,
                    indent=INDENT,
                )
            )
        )
        member_patch.append(
            "\n".join(
                property_member(
                    name=property.name,
                    type=property.type,
                    category=property.category,
                    has_default=property.default is not None,
                    base_indent=BASE_INDENT,
                )
            )
        )

    patches += [
        (DEFAULT_CODE, default_patch),
        (SETTER_CODE, "\n\n".join(setter_patch)),
        (GETTER_CODE, "\n\n".join(getter_patch)),
        (MEMBER_CODE, "\n\n".join(member_patch)),
    ]


def generate_projectile_core():
    global patches

    BASE_INDENT = "\t\t"
    INDENT = "\t"

    DEFAULT_CODE = projectile_spec.id + "-DEF"
    SETTER_CODE = projectile_spec.id + "-SET"
    GETTER_CODE = projectile_spec.id + "-GET"
    MEMBER_CODE = projectile_spec.id + "-MEM"

    setter_patch: list[str] = []
    getter_patch: list[str] = []
    member_patch: list[str] = []

    default_patch = "\n".join(
        property_default(
            properties=projectile_spec.properties, base_indent=BASE_INDENT + INDENT
        )
    )
    for property in projectile_spec.properties:
        setter_patch.append(
            "\n".join(
                property_setter(
                    name=property.name,
                    type=property.type,
                    category=property.category,
                    has_default=property.default is not None,
                    class_name="projectile",
                    base_indent=BASE_INDENT,
                    indent=INDENT,
                )
            )
        )
        getter_patch.append(
            "\n".join(
                property_getter(
                    name=property.name,
                    type=property.type,
                    category=property.category,
                    has_default=property.default is not None,
                    base_indent=BASE_INDENT,
                    indent=INDENT,
                )
            )
        )
        member_patch.append(
            "\n".join(
                property_member(
                    name=property.name,
                    type=property.type,
                    category=property.category,
                    has_default=property.default is not None,
                    base_indent=BASE_INDENT,
                )
            )
        )

    patches += [
        (DEFAULT_CODE, default_patch),
        (SETTER_CODE, "\n\n".join(setter_patch)),
        (GETTER_CODE, "\n\n".join(getter_patch)),
        (MEMBER_CODE, "\n\n".join(member_patch)),
    ]


def generate_api_core():
    global patches

    BASE_INDENT = "\t"

    for trajectory_model_spec in trajectory_model_specs:
        api_code = trajectory_model_spec.id + "-API"

        api_patch = "\n".join(
            ballistics_api(
                weapon_parameters=trajectory_model_spec.weapon_parameters,
                class_name=trajectory_model_spec.class_name,
                base_indent=BASE_INDENT,
            )
        )

        patches += [
            (api_code, api_patch),
        ]


generate_binding()
generate_trajectory_model_core()
generate_integrator_core()
generate_environemnt_core()
generate_projectile_core()
generate_api_core()

patch_codegen_blocks(ROOT, patches)
