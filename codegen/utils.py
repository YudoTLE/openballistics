def format_lines(lines: list[str], *, prefix: str = "") -> list[str]:
    return [f"{prefix}{line}" for line in lines if "__SKIP__" not in line]
