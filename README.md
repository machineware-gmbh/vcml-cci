# Template Model
This a template model repository to be used when setting up repositories for
new TLM models that live outside VCML itself. Search for `template-model` as
well as `TEMPLATE_MODEL` and rename accordingly. You also might want to move
your model out of the `vcml::generic` namespace into something more specific,
such as `vcml::<vendor-name>`. If you introduce or rename `cmake` build
options, or if you need extra dependencies, do not forget to update everything
in `.github/workflows`.

[![Build Status](https://github.com/machineware-gmbh/template-model/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/machineware-gmbh/template-model/actions/workflows/cmake.yml)
[![ASAN Status](https://github.com/machineware-gmbh/template-model/actions/workflows/asan.yml/badge.svg?branch=main)](https://github.com/machineware-gmbh/template-model/actions/workflows/asan.yml)
[![Lint Status](https://github.com/machineware-gmbh/template-model/actions/workflows/lint.yml/badge.svg?branch=main)](https://github.com/machineware-gmbh/template-model/actions/workflows/lint.yml)
[![Style Status](https://github.com/machineware-gmbh/template-model/actions/workflows/style.yml/badge.svg?branch=main)](https://github.com/machineware-gmbh/template-model/actions/workflows/style.yml)
[![Nightly Status](https://github.com/machineware-gmbh/template-model/actions/workflows/nightly.yml/badge.svg?branch=main)](https://github.com/machineware-gmbh/template-model/actions/workflows/nightly.yml)
[![Coverage Status](https://github.com/machineware-gmbh/template-model/actions/workflows/coverage.yml/badge.svg?branch=main)](https://github.com/machineware-gmbh/template-model/actions/workflows/coverage.yml)


----
## Installation
Most dependencies will be automatically downloaded during configuration, such
as `vcml` and `systemc`. However, if you need extra dependencies, you must
install them manually:
```
sudo apt-get install <list your dependencies here> # Ubuntu
```

Clone repository and update submodules:
```
git clone git@github.com:machineware-gmbh/template-model.git --recursive
```

Building `template-model` requires `cmake >= 3.11`. During configuration you
must state whether to build the unit tests:
* `-DTEMPLATE_MODEL_TESTS=[ON|OFF]`: build unit tests (default `OFF`)
* `-DTEMPLATE_MODEL_LINTER=<string>`: linter program to use (default `<empty>`)
* `-DTEMPLATE_MODEL_COVERAGE=[ON|OFF]`: generate test coverage report (default `OFF`)

Note that when building this as a cmake submodule, unit tests will always be
disabled and the respective build option setting is ignored.
```
cmake -B RELEASE/BUILD           \
      -DCMAKE_BUILD_TYPE=RELEASE \
      -DCMAKE_INSTALL_PREFIX=..  \
      -DTEMPLATE_MODEL_TESTS=ON .
cmake --build RELEASE/BUILD -- install
```
If everything went well, the following artifacts will have been installed:
* template-model headers in `RELEASE/include/`
* template-model library in `RELEASE/lib/libtemplate-model.a`

----
## License

This project is proprietary and confidential work and requires a seperate
license agreement to use - see the [LICENSE](LICENSE) file for details.
