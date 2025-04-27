# FLAPPY_BIRD

A simple C/C++ game built using raylib and Visual Studio.

## Getting Started

Follow these steps to set up the development environment and run the project.

### Prerequisites

- Git installed.

- Visual Studio with C++ development workload.

- (Optional) CMake if the project uses it, but maybe not needed here.

But since the user didn't include prerequisites, maybe skip. Proceed with the steps as given.

Convert each step into markdown. For example:

1. **Clone vcpkg**

```bash

git clone https://github.com/Microsoft/vcpkg.git

cd vcpkg

bootstrap-vcpkg.bat

```
2. **Integrate vcpkg with Visual Studio**
```bash
.\vcpkg integrate install
```
This makes vcpkg packages automatically available in Visual Studio projects.

3. **Install raylib**
For x64 builds (recommended):

```bash
.\vcpkg install raylib:x64-windows
```
For 32-bit (x86) builds:

```bash
.\vcpkg install raylib:x86-windows
```
4. ***Open the Project in Visual Studio***

*Launch Visual Studio.*

*Open the project folder containing your .sln or .vcxproj file.*

*Set the Solution Platform to x64 (via the dropdown at the top).*

5.****Build and Run****
Debug Mode: Press F5 to build and debug.

Run Without Debugging: Press Ctrl + F5.

Troubleshooting
Headers Not Found

### Ensure 
```
vcpkg install raylib:x64-windows 
```
completed successfully.

Rebuild the project after installation.

Linker Errors
Confirm the Solution Platform is set to x64.

Re-run:

```bash

.\vcpkg integrate install
```
