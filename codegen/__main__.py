from .property import *
from .spec import *
from .patcher import *
from .api import *
from .definition import *
from .binding import *
from pathlib import Path

ROOT = Path(__file__).parent.parent
SPEC = ROOT / "codegen" / "spec"

model_specs = load_model_specs(SPEC / "model")
integrator_specs = load_integrator_specs(SPEC / "integrator")
environment_specs = load_environment_specs(SPEC / "environment")
projectile_specs = load_projectile_specs(SPEC / "projectile")

patches: list[tuple[str, str]] = []


def generate_binding():
    global patches

    BASE_INDENT = "\t"
    BIND_CODE = "BIND"

    bind_patch: list[str] = []

    for model_spec in model_specs:
        for integrator_spec in integrator_specs:
            for environment_spec in environment_specs:
                if environment_spec.id not in model_spec.compatible_environment_ids:
                    continue

                for projectile_spec in projectile_specs:
                    if projectile_spec.id not in model_spec.compatible_projectile_ids:
                        continue

                    bind_patch.append(
                        "\n".join(
                            ballistics_bind(
                                class_name=f"ballistics<model::{model_spec.class_name}, integrator::{integrator_spec.class_name}, environment::{environment_spec.class_name}, projectile::{projectile_spec.class_name}>",
                                nb_class_name=f"{model_spec.nb_class_name}{integrator_spec.nb_class_name}{environment_spec.nb_class_name}{projectile_spec.nb_class_name}",
                                weapon_parameters=model_spec.weapon_parameters,
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

    for environment_spec in environment_specs:
        bind_patch.append(
            "\n".join(
                environment_bind(
                    class_name=environment_spec.class_name,
                    nb_class_name=environment_spec.nb_class_name,
                    properties=environment_spec.properties,
                    base_indent=BASE_INDENT,
                )
            )
        )

    for projectile_spec in projectile_specs:
        bind_patch.append(
            "\n".join(
                projectile_bind(
                    class_name=projectile_spec.class_name,
                    nb_class_name=projectile_spec.nb_class_name,
                    properties=projectile_spec.properties,
                    base_indent=BASE_INDENT,
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
            model_weapon_definition(
                weapon_parameters=model_spec.weapon_parameters, base_indent=BASE_INDENT
            )
        )

        patches.append((DEFINITION_CODE, definition_patch))


def generate_integrator_core():
    global patches

    BASE_INDENT = "\t\t"

    for integrator_spec in integrator_specs:
        SETTER_CODE = integrator_spec.id + "-SET"
        GETTER_CODE = integrator_spec.id + "-GET"
        MEMBER_CODE = integrator_spec.id + "-MEM"

        setter_patch: list[str] = []
        getter_patch: list[str] = []
        member_patch: list[str] = []

        for property in integrator_spec.properties:
            setter_patch.append(
                "\n".join(
                    property_setter(
                        name=property.name,
                        type=property.type,
                        category=property.category,
                        class_name=integrator_spec.class_name,
                        base_indent=BASE_INDENT,
                    )
                )
            )
            getter_patch.append(
                "\n".join(
                    property_getter(
                        name=property.name,
                        type=property.type,
                        category=property.category,
                        base_indent=BASE_INDENT,
                    )
                )
            )
            member_patch.append(
                "\n".join(
                    property_member(
                        name=property.name,
                        type=property.type,
                        category=property.category,
                        base_indent=BASE_INDENT,
                    )
                )
            )

        patches += [
            (SETTER_CODE, "\n\n".join(setter_patch)),
            (GETTER_CODE, "\n\n".join(getter_patch)),
            (MEMBER_CODE, "\n\n".join(member_patch)),
        ]


def generate_environemnt_core():
    global patches

    BASE_INDENT = "\t\t"

    for environment_spec in environment_specs:
        SETTER_CODE = environment_spec.id + "-SET"
        GETTER_CODE = environment_spec.id + "-GET"
        MEMBER_CODE = environment_spec.id + "-MEM"

        setter_patch: list[str] = []
        getter_patch: list[str] = []
        member_patch: list[str] = []

        for property in environment_spec.properties:
            setter_patch.append(
                "\n".join(
                    property_setter(
                        name=property.name,
                        type=property.type,
                        category=property.category,
                        class_name=environment_spec.class_name,
                        base_indent=BASE_INDENT,
                    )
                )
            )
            getter_patch.append(
                "\n".join(
                    property_getter(
                        name=property.name,
                        type=property.type,
                        category=property.category,
                        base_indent=BASE_INDENT,
                    )
                )
            )
            member_patch.append(
                "\n".join(
                    property_member(
                        name=property.name,
                        type=property.type,
                        category=property.category,
                        base_indent=BASE_INDENT,
                    )
                )
            )

        patches += [
            (SETTER_CODE, "\n\n".join(setter_patch)),
            (GETTER_CODE, "\n\n".join(getter_patch)),
            (MEMBER_CODE, "\n\n".join(member_patch)),
        ]


def generate_projectile_core():
    global patches

    BASE_INDENT = "\t\t"

    for projectile_spec in projectile_specs:

        SETTER_CODE = projectile_spec.id + "-SET"
        GETTER_CODE = projectile_spec.id + "-GET"
        MEMBER_CODE = projectile_spec.id + "-MEM"

        setter_patch: list[str] = []
        getter_patch: list[str] = []
        member_patch: list[str] = []

        for property in projectile_spec.properties:
            setter_patch.append(
                "\n".join(
                    property_setter(
                        name=property.name,
                        type=property.type,
                        category=property.category,
                        class_name=projectile_spec.class_name,
                        base_indent=BASE_INDENT,
                    )
                )
            )
            getter_patch.append(
                "\n".join(
                    property_getter(
                        name=property.name,
                        type=property.type,
                        category=property.category,
                        base_indent=BASE_INDENT,
                    )
                )
            )
            member_patch.append(
                "\n".join(
                    property_member(
                        name=property.name,
                        type=property.type,
                        category=property.category,
                        base_indent=BASE_INDENT,
                    )
                )
            )

        patches += [
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
            api(
                weapon_parameters=model_spec.weapon_parameters,
                class_name=model_spec.class_name,
                base_indent=BASE_INDENT,
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
