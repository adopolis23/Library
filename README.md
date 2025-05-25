# 📦 C++ Library – Data Structures From Scratch

A modern C++ library featuring standard data structures implemented from the ground up — no shortcuts, just pure C++ fundamentals.

## 📚 What's Included

The following components have been implemented so far:

- ✅ **Vector** – Dynamic array with growth strategy  
- ✅ **Iterator** – Custom iterator class with STL-like behavior  
- ✅ **Allocator** – Memory allocator abstraction

---

## 🏗️ Project Structure

This repository contains **three main projects**, all managed via [Premake5](https://premake.github.io/). Here's a breakdown:

### 📁 `Library/`
The core library where all data structures are implemented.

> 🔧 Built as a DLL (optional), though most implementations are header-only templates and don't require linking.

---

### 🧪 `MyLibraryTests/`
Unit tests written using **Google Test** to ensure correctness and stability of each data structure.

---

### 🧪 `Application/`
A basic test application that utilizes and showcases the library's data structures in practice.

---

## ⚙️ Building the Project

This project uses **Premake5** to generate build files for different platforms. The `premake5` executable is included in the repository for convenience.


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