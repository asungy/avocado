# Installation requirements
- [CMake](https://cmake.org/download/) (version 3.19 or greater)
- [g++](https://gcc.gnu.org/releases.html) (version 9.3 or greater)
    - (For Ubuntu):
      ```bash
      sudo add-apt-repository ppa:ubuntu-toolchain-r/test 
      sudo apt update
      sudo apt install g++-9
      ```
- python3.8 (or greater)
- [libpython](https://pkgs.org/download/libpython3.8-dev) (version 3.8 or greater)
- [InfluxDB](https://www.influxdata.com/products/influxdb/) (v2.0.2 or greater)
- GLFW: depends on X11
  - `sudo apt install xorg-dev` (try this one first)
  - `sudo apt install libx11-dev libxrandr-dev libxinerama-dev \
     libxcursor-dev libxi-dev libxext-dev libglfw3-dev`
- ncurses: `sudo apt install libncursesw5-dev`

# Optional
- [Ninja](https://ninja-build.org/)
    ```bash
    sudo apt install ninja-build
    # To use in CMake
    cd build/ && cmake -GNinja ..
    ninja
    ```
