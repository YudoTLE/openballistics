from pathlib import Path
from itertools import product

from .constants import *
from .utils import *
from .properties import *
from .specs import *
from .patcher import *
from .ballistics_api import *
from .model_definitions import *
from .bindings import *

ROOT = Path(__file__).parent.parent
SPEC = ROOT / "codegen" / "specs"

model_specs = load_model_specs(SPEC / "models")
integrator_specs = load_integrator_specs(SPEC / "integrators")
environment_spec = load_environment_spec(SPEC / "environment.yml")
projectile_spec = load_projectile_spec(SPEC / "projectile.yml")

patches: list[tuple[str, str]] = []


def generate_binding():
    global patches

    BASE_INDENT = "\t"
    BIND_CODE = "BIND"

    bind_patch: list[str] = []

    for model_spec, integrator_spec in product(model_specs, integrator_specs):
        bind_patch.append(
            "\n".join(
                format_lines(
                    ballistics_bind(
                        class_name=f"ballistics<models::{model_spec.class_name}, integrators::{integrator_spec.class_name}>",
                        nb_class_name=f"{model_spec.nb_class_name}{integrator_spec.nb_class_name}",
                        weapon_parameters=model_spec.weapon_parameters,
                    ),
                    prefix=BASE_INDENT,
                )
            )
        )

    for integrator_spec in integrator_specs:
        bind_patch.append(
            "\n".join(
                format_lines(
                    integrator_bind(
                        class_name=integrator_spec.class_name,
                        nb_class_name=integrator_spec.nb_class_name,
                        properties=integrator_spec.properties,
                    ),
                    prefix=BASE_INDENT,
                )
            )
        )

    bind_patch.append(
        "\n".join(
            format_lines(
                environment_bind(
                    nb_class_name=environment_spec.nb_class_name,
                    properties=environment_spec.properties,
                ),
                prefix=BASE_INDENT,
            )
        )
    )

    bind_patch.append(
        "\n".join(
            format_lines(
                projectile_bind(
                    nb_class_name=projectile_spec.nb_class_name,
                    properties=projectile_spec.properties,
                ),
                prefix=BASE_INDENT,
            )
        )
    )

    patches.append((BIND_CODE, "\n".join(bind_patch)))


def generate_model_core():
    global patches

    BASE_INDENT = "\t\t\t"

    for model_spec in model_specs:

        DEFINITION_CODE = model_spec.id + "-DEF"

        definition_patch = "\n".join(
            format_lines(
                model_weapon_definition(
                    weapon_parameters=model_spec.weapon_parameters,
                ),
                prefix=BASE_INDENT,
            )
        )

        patches.append((DEFINITION_CODE, definition_patch))


def generate_integrator_core():
    global patches

    BASE_INDENT = "\t\t"

    for integrator_spec in integrator_specs:
        DEFAULT_CODE = integrator_spec.id + "-DEF"
        SETTER_CODE = integrator_spec.id + "-SET"
        GETTER_CODE = integrator_spec.id + "-GET"
        MEMBER_CODE = integrator_spec.id + "-MEM"

        setter_patch: list[str] = []
        getter_patch: list[str] = []
        member_patch: list[str] = []

        default_patch = "\n".join(
            format_lines(
                property_default(properties=integrator_spec.properties),
                prefix=BASE_INDENT + INDENT,
            )
        )
        for property in integrator_spec.properties:
            setter_patch.append(
                "\n".join(
                    format_lines(
                        property_setter(
                            name=property.name,
                            type=property.type,
                            category=property.category,
                            has_default=property.default is not None,
                            class_name=integrator_spec.class_name,
                        ),
                        prefix=BASE_INDENT,
                    )
                )
            )
            getter_patch.append(
                "\n".join(
                    format_lines(
                        property_getter(
                            name=property.name,
                            type=property.type,
                            category=property.category,
                            has_default=property.default is not None,
                        ),
                        prefix=BASE_INDENT,
                    )
                )
            )
            member_patch.append(
                "\n".join(
                    format_lines(
                        property_member(
                            name=property.name,
                            type=property.type,
                            category=property.category,
                            has_default=property.default is not None,
                        ),
                        prefix=BASE_INDENT,
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

    DEFAULT_CODE = environment_spec.id + "-DEF"
    SETTER_CODE = environment_spec.id + "-SET"
    GETTER_CODE = environment_spec.id + "-GET"
    MEMBER_CODE = environment_spec.id + "-MEM"

    setter_patch: list[str] = []
    getter_patch: list[str] = []
    member_patch: list[str] = []

    default_patch = "\n".join(
        format_lines(
            property_default(properties=environment_spec.properties),
            prefix=BASE_INDENT + INDENT,
        )
    )
    for property in environment_spec.properties:
        setter_patch.append(
            "\n".join(
                format_lines(
                    property_setter(
                        name=property.name,
                        type=property.type,
                        category=property.category,
                        has_default=property.default is not None,
                        class_name="environment",
                    ),
                    prefix=BASE_INDENT,
                )
            )
        )
        getter_patch.append(
            "\n".join(
                format_lines(
                    property_getter(
                        name=property.name,
                        type=property.type,
                        category=property.category,
                        has_default=property.default is not None,
                    ),
                    prefix=BASE_INDENT,
                )
            )
        )
        member_patch.append(
            "\n".join(
                format_lines(
                    property_member(
                        name=property.name,
                        type=property.type,
                        category=property.category,
                        has_default=property.default is not None,
                    ),
                    prefix=BASE_INDENT,
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

    DEFAULT_CODE = projectile_spec.id + "-DEF"
    SETTER_CODE = projectile_spec.id + "-SET"
    GETTER_CODE = projectile_spec.id + "-GET"
    MEMBER_CODE = projectile_spec.id + "-MEM"

    setter_patch: list[str] = []
    getter_patch: list[str] = []
    member_patch: list[str] = []

    default_patch = "\n".join(
        format_lines(
            property_default(properties=projectile_spec.properties),
            prefix=BASE_INDENT + INDENT,
        )
    )
    for property in projectile_spec.properties:
        setter_patch.append(
            "\n".join(
                format_lines(
                    property_setter(
                        name=property.name,
                        type=property.type,
                        category=property.category,
                        has_default=property.default is not None,
                        class_name="projectile",
                    ),
                    prefix=BASE_INDENT,
                )
            )
        )
        getter_patch.append(
            "\n".join(
                format_lines(
                    property_getter(
                        name=property.name,
                        type=property.type,
                        category=property.category,
                        has_default=property.default is not None,
                    ),
                    prefix=BASE_INDENT,
                )
            )
        )
        member_patch.append(
            "\n".join(
                format_lines(
                    property_member(
                        name=property.name,
                        type=property.type,
                        category=property.category,
                        has_default=property.default is not None,
                    ),
                    prefix=BASE_INDENT,
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

    for model_spec in model_specs:
        api_code = model_spec.id + "-API"

        api_patch = "\n".join(
            format_lines(
                ballistics_api(
                    weapon_parameters=model_spec.weapon_parameters,
                    class_name=model_spec.class_name,
                ),
                prefix=BASE_INDENT,
            )
        )

        patches += [
            (api_code, api_patch),
        ]


generate_binding()
generate_model_core()
generate_integrator_core()
generate_environemnt_core()
generate_projectile_core()
generate_api_core()

patch_codegen_blocks(ROOT, patches)
