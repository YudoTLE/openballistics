import re
from pathlib import Path


def patch_codegen_blocks(dir: Path, patches: list[tuple[str, str]]) -> None:
    cpp_source_files: list[Path] = [
        path for path in dir.rglob("*") if path.suffix in {".cpp", ".hpp"}
    ]

    py_source_files: list[Path] = [
        path for path in dir.rglob("*") if path.suffix in {".py", ".pyi"}
    ]

    for source_file in cpp_source_files:
        content = source_file.read_text(encoding="utf-8")
        original = content

        for code, block in patches:
            content = re.sub(
                rf"[ \t]*#\s*pragma\s+region\s+\"CODEGEN {re.escape(code)}\"[\s\S]*?#\s*pragma\s+endregion\s+\"CODEGEN {re.escape(code)}\"",
                lambda _: (
                    f'#pragma region "CODEGEN {code}" // AUTO-GENERATED - DO NOT EDIT MANUALLY\n'
                    f"{block}\n"
                    f'#pragma endregion "CODEGEN {code}"'
                ),
                content,
                flags=re.DOTALL,
            )

        if content != original:
            source_file.write_text(content, encoding="utf-8")
            print(f"updated: {source_file.relative_to(dir)}")

    for source_file in py_source_files:
        content = source_file.read_text(encoding="utf-8")
        original = content

        for code, block in patches:
            content = re.sub(
                rf'[ \t]*#\s*region\s+"CODEGEN {re.escape(code)}"[\s\S]*?#\s*#\s*endregion\s+"CODEGEN {re.escape(code)}"',
                lambda _: (
                    f'# region "CODEGEN {code}"  # AUTO-GENERATED - DO NOT EDIT MANUALLY\n'
                    f"{block}\n"
                    f'# endregion "CODEGEN {code}"'
                ),
                content,
                flags=re.DOTALL,
            )

        if content != original:
            source_file.write_text(content, encoding="utf-8")
            print(f"updated: {source_file.relative_to(dir)}")
