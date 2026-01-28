# PFC-C

A Personal Finance Control application created with C and my onw C-Utils header.

## Dependencies

- `GCC` (or `Mingw GCC` for **Windows**).
- `CMake` to **build the project**.
- `Ninja` (or `Mingw Ninja` for **Windows**) to help `CMake` to **make the executable file**.

### Dependencies install process

**Windows**:

1. Press `Windows + R`, type `cmd` and press `Ctrl + Shift + Enter`, then open it in administrator mode.
2. Type into **cmd** `winget install --id="Kitware.CMake" && winget install --id="MSYS2.MSYS2"`.
3. Now after install **CMake** and **MSYS2** press `Windows + R` and type `mingw64` or `mingw32` for 32 bits, then press `Ctrl + Shift + Enter` to open it as an administrator.
4. Now on Mingw Shell type `pacman -Syyu && pacman -S mingw-w64-x86_64-gcc && pacman -S mingw-w64-x86_64-ninja`.
5. Now you just need to **build** the project.

**Linux**:

1. Install `GCC`, `CMake`, `Ninja` with the **Package Manager of the Distribution**.
2. **Build** the project.

**macOS**:

1. Install a **[MacPort](https://www.macports.org/install.php)** for your **current macOS** distro.
2. Enter in **terminal** and type `sudo port selfupdate && sudo port install cmake gcc ninja`.

#### Build process

1. Create a directory named `./build` with terminal.
2. Enter into the `./build` directory.
3. Type `cmake .. -G Ninja` in `./build` directory to make the `./build/build.ninja` file.
4. Type `ninja` in `./build` to run `./build/build.ninja` and create the compiled file named `./build/bin/Executable.exe`.

##### Credits

**Created by: @paulao255**.
