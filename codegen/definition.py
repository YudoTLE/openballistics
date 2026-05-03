from .spec import Parameter


def model_weapon_definition(
    *, weapon_parameters: list[Parameter], base_indent: str
) -> list[str]:
    lines = [f"{p.type} {p.name};" for p in weapon_parameters]
    return [base_indent + line for line in lines]
