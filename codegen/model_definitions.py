from .specs import Parameter


def model_weapon_definition(
    *, weapon_parameters: list[Parameter]
) -> list[str]:
    lines = [f"{p.type} {p.name};" for p in weapon_parameters]
    return lines
