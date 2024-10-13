# TelemetryP1 
## accounts: 
- username: admin, password: adminpwd, role:Admin
- username: marco, password: marcopsw, role:Engineer
- username: maxv, password: maxvpsw, role:Pilot

If you are logged in as Admin you can create accounts by clicking the "create account" button in the "user menu"

### Prerequisites
- git and a GitHub account
- C/C++ toolchain, with CMake
- OpenGL
- GLEW
- GLFW3

### For Debian / Ubuntu you can use:
```bash
sudo apt install build-essential cmake libglfw3-dev libglew-dev mesa-utils
```
### For macOS with homebrew:
```zsh
    brew install mesa
    brew install glew
    brew install glfw
```


### To build

```bash
    mkdir -p build
    cd build
    cmake ..
    make
    ../bin/project_1
```






