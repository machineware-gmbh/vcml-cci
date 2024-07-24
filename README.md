# VCML-CCI
SystemC-CCI Integration for VCML.

[![Build Status](https://github.com/machineware-gmbh/vcml-cci/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/machineware-gmbh/vcml-cci/actions/workflows/cmake.yml)
[![ASAN Status](https://github.com/machineware-gmbh/vcml-cci/actions/workflows/asan.yml/badge.svg?branch=main)](https://github.com/machineware-gmbh/vcml-cci/actions/workflows/asan.yml)
[![Lint Status](https://github.com/machineware-gmbh/vcml-cci/actions/workflows/lint.yml/badge.svg?branch=main)](https://github.com/machineware-gmbh/vcml-cci/actions/workflows/lint.yml)
[![Style Status](https://github.com/machineware-gmbh/vcml-cci/actions/workflows/style.yml/badge.svg?branch=main)](https://github.com/machineware-gmbh/vcml-cci/actions/workflows/style.yml)
[![Nightly Status](https://github.com/machineware-gmbh/vcml-cci/actions/workflows/nightly.yml/badge.svg?branch=main)](https://github.com/machineware-gmbh/vcml-cci/actions/workflows/nightly.yml)
[![Coverage Status](https://github.com/machineware-gmbh/vcml-cci/actions/workflows/coverage.yml/badge.svg?branch=main)](https://github.com/machineware-gmbh/vcml-cci/actions/workflows/coverage.yml)


----
## Installation
Clone repository and update submodules:
```
git clone git@github.com:machineware-gmbh/vcml-cci.git --recursive
```

Building `vcml-cci` requires `cmake >= 3.11`. During configuration you
must state whether to build the unit tests:
* `-DVCML_CCI_TESTS=[ON|OFF]`: build unit tests (default `OFF`)
* `-DVCML_CCI_LINTER=<string>`: linter program to use (default `<empty>`)
* `-DVCML_CCI_COVERAGE=[ON|OFF]`: generate test coverage report (default `OFF`)

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
* vcml-cci headers in `RELEASE/include/`
* vcml-cci library in `RELEASE/lib/libvcml-cci.a`

----
## License

See the [LICENSE](LICENSE) file for details.
