import yaml
from pathlib import Path
from dataclasses import dataclass, field


@dataclass
class DocParameter:
    name: str
    description: str | None = None
    type: str | None = None
    required_tag: str | None = None
    overload_name: str | None = None
    overload_description: str | None = None


@dataclass
class DocMethod:
    name: str
    brief: str
    details: str | None = None
    returns: str | None = None
    params: list[DocParameter] = field(default_factory=lambda: [])


@dataclass
class ApiDocs:
    parameters: dict[str, DocParameter]
    methods: dict[str, DocMethod]


def load_api_docs(path: Path) -> ApiDocs:
    with open(path, "r", encoding="utf-8") as f:
        data = yaml.safe_load(f)

    parameters: dict[str, DocParameter] = {}
    for p in data.get("params", []):
        param = DocParameter(
            name=p["name"],
            description=p.get("description"),
            type=p.get("type"),
            required_tag=p.get("required_tag"),
            overload_name=p.get("overload_name"),
            overload_description=p.get("overload_description"),
        )
        parameters[param.name] = param

    methods: dict[str, DocMethod] = {}
    for m in data.get("methods", []):
        method_params: list[DocParameter] = []
        for p in m.get("params", []):
            method_params.append(
                DocParameter(
                    name=p["name"],
                    description=p.get("description"),
                    type=p.get("type"),
                    required_tag=p.get("required_tag"),
                    overload_name=p.get("overload_name"),
                    overload_description=p.get("overload_description"),
                )
            )
        method = DocMethod(
            name=m["name"],
            brief=m.get("brief", ""),
            details=m.get("details"),
            returns=m.get("returns"),
            params=method_params,
        )
        methods[method.name] = method

    return ApiDocs(parameters=parameters, methods=methods)
