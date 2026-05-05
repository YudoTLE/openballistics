import yaml
from pathlib import Path
from dataclasses import dataclass


@dataclass
class Property:
    name: str
    type: str
    category: str
    default: str | None = None
    description: str | None = None


@dataclass
class Parameter:
    name: str
    type: str
    qualifier: str | None = None
    description: str | None = None


@dataclass(kw_only=True)
class BaseSpec:
    id: str
    class_name: str
    nb_class_name: str
    description: str | None = None


@dataclass(kw_only=True)
class ModelSpec(BaseSpec):
    weapon_parameters: list[Parameter]
    compatible_projectile_ids: list[str]


@dataclass(kw_only=True)
class IntegratorSpec(BaseSpec):
    properties: list[Property]


@dataclass(kw_only=True)
class EnvironmentSpec(BaseSpec):
    properties: list[Property]


@dataclass(kw_only=True)
class ProjectileSpec(BaseSpec):
    properties: list[Property]


def load_model_specs(dir: Path) -> list[ModelSpec]:
    specs: list[ModelSpec] = []
    if not dir.exists():
        return specs
    for yaml_file in dir.glob("*.yml"):
        with open(yaml_file, "r", encoding="utf-8") as f:
            data = yaml.safe_load(f)
        specs.append(
            ModelSpec(
                id=data["id"],
                class_name=data["class_name"],
                nb_class_name=data["nb_class_name"],
                description=data.get("description"),
                weapon_parameters=[
                    Parameter(**p) for p in data.get("weapon_parameters", [])
                ],
                compatible_projectile_ids=[
                    p["id"] for p in data.get("projectile_compatibilities", [])
                ],
            )
        )
    return specs


def load_integrator_specs(dir: Path) -> list[IntegratorSpec]:
    specs: list[IntegratorSpec] = []
    if not dir.exists():
        return specs
    for yaml_file in dir.glob("*.yml"):
        with open(yaml_file, "r", encoding="utf-8") as f:
            data = yaml.safe_load(f)
        specs.append(
            IntegratorSpec(
                id=data["id"],
                class_name=data["class_name"],
                nb_class_name=data["nb_class_name"],
                description=data.get("description"),
                properties=[Property(**prop) for prop in data.get("properties", [])],
            )
        )
    return specs


def load_environment_spec(file: Path) -> EnvironmentSpec:
    with open(file, "r", encoding="utf-8") as f:
        data = yaml.safe_load(f)
    return EnvironmentSpec(
        id=data["id"],
        class_name=data["class_name"],
        nb_class_name=data["nb_class_name"],
        description=data.get("description"),
        properties=[Property(**prop) for prop in data.get("properties", [])],
    )


def load_projectile_specs(dir: Path) -> list[ProjectileSpec]:
    specs: list[ProjectileSpec] = []
    if not dir.exists():
        return specs
    for yaml_file in dir.glob("*.yml"):
        with open(yaml_file, "r", encoding="utf-8") as f:
            data = yaml.safe_load(f)
        specs.append(
            ProjectileSpec(
                id=data["id"],
                class_name=data["class_name"],
                nb_class_name=data["nb_class_name"],
                description=data.get("description"),
                properties=[Property(**prop) for prop in data.get("properties", [])],
            )
        )
    return specs
