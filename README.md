# C++ Library
Standard C++ data structures implemented by me from scatch.
Items implemented so far:

* Vector
* Iterator
* Allocator

This repository has 3 main projects within it that get build with premake (instructions on building below) these projects are:

* Library
    Where the main data structures are implemented. Configured to build a DLL however at the time of writing this all implementations are templates in header files so no DLL is necessesary.
<br>
* Application
    A test application that used the library data structures.
<br>
* MyLibraryTests
    Unit tests of the data structures implemented with Google Test.

## Building The Project
This project uses the premake build system. This can be used to either generate the full Visual Studio project on windows or the necessary Make files on linux. The premake executable is included in this repo.

To build on windows (for visual studio 2022):
```
./premake5 vs2022
```

To build on Linux (not tested):
```
./premake5 gmake2
make
```

### Author
* **Brandon Weinhofer** - *Initial work* - [adopolis23](https://github.com/adopolis23)

### License

This project is licensed under the Apache 2.0 License - see the [LICENSE.md](LICENSE.md) file for details