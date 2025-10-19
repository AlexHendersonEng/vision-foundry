# ✈️ Vision Foundry

![C++](https://img.shields.io/badge/C++-%2300599C.svg?style=Plastic&logo=c%2B%2B&logoColor=white)
![Python](https://img.shields.io/badge/Python-3670A0?style=Plastic&logo=python&logoColor=ffdd54)
![TypeScript](https://img.shields.io/badge/TypeScript-%23007ACC.svg?style=Plastic&logo=typescript&logoColor=white)

![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=Plastic&logo=cmake&logoColor=white)
![Django](https://img.shields.io/badge/Django-%23092E20.svg?style=Plastic&logo=django&logoColor=white)
![React](https://img.shields.io/badge/React-%2320232a.svg?style=Plastic&logo=react&logoColor=%2361DAFB)
![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-%23313131.svg?style=Plastic&logo=unrealengine&logoColor=white)

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](#license)

Vision Foundry is a cross-platform project for image detection and segmentation of military aircraft. It features a C++ core, Python API, web application for viewing results and training and Unreal Engine based visualisation environment.

## Table of contents

- [Repository layout](#repository-layout)
- [Pre-commit hooks](#pre-commit-hooks)
- [Contributing](#contributing)
- [Roadmap](#roadmap--future-development)
- [License](#license)

## Repository layout

```bash
vision-foundry/
├─ 📂 cpp/                      # C++ core
├─ 📂 data/                     # Data
├─ 📂 python/                   # Python API
├─ 📂 third-party/              # Third party tools (doxygen, vcpkg, ...)
├─ 📂 unreal-engine/            # Unreal Engine visualisation playground
├─ 📂 web/                      # Web application
├─ 📄 .gitignore                # Top level git ignore
├─ 📄 .gitmodules               # Git module tracking for third-party/
├─ 📄 .pre-commit-config.yaml   # Pre-commit configuration
├─ 📄 LICENSE                   # License
└─ 📄 README.md                 # This file
```

## Pre-commit hooks

We recommend using `pre-commit` to run linters and formatters before committing.

Install:

```bash
uv tool install pre-commit
pre-commit install
```

Run on all files:

```bash
pre-commit run --all-files
```

## Contributing

Small guidelines to make contributions smooth:

1. Create an issue describing the change you propose.
2. Branch from `main` (e.g. `feature/your-feature`).
3. Add tests and run them locally.
4. Run `pre-commit` and format your code.
5. Open a pull request with a clear description and test instructions.

Developer tips

- Prefer small, focused changes and clear commit messages.
- Use the vcpkg instance configured for C++ core in the repo to avoid dependency drift.

## Roadmap — future development

Short-term

- Dataset loaders and pre-processing utilities
- Minimal C++ inference pipeline and image IO utilities
- Python bindings via pybind11
- CI workflow (GitHub Actions) for cross-platform build + tests

Longer-term

- Model zoo and serialized model management
- Docker images for reproducible training/inference
- Performance benchmarks and robustness tests

## License

See `LICENSE` in the repository root for license details.
