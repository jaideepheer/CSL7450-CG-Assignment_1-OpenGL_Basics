# CSL7450-CG-Assignment_1-OpenGL_Basics

## Controls
- Click and drag any labled point to move it.

## Running

- Download any of the executables from the releases page here.
- Run it.

## Development/Compiling

### Native
The project requires the following apt-get libraries.
- `freeglut3-dev`
- [`meson`](https://mesonbuild.com/Quick-guide.html)
- `mingw64` to cross compile for windows-64bit.
And all their dependencies.

It is recommended to use the docker image provided for compiling the code.

### VSCode
- Make sure [Docker](https://www.docker.com/products/docker-desktop) is installed on your system.
- **[Optional]** If you plan to use WSL2 for Docker for Windows then make sure [GWSL](https://www.microsoft.com/store/productId/9NL6KD1H33V3) is installed and is running, to run WSL2 GUI apps in windows.
- Clone this repo and open in [VSCode](https://code.visualstudio.com/).
- In VSCode press `Ctrl+Shift+P` and type `Reopen in Container` to open folder in container.
- In VSCode open a new terminal and run `meson setup builddir`.
- Development environment is now ready.
- Make sure both `asabil.meson` and `mrmomo.meson-build` extensions are installed in VSCode.
- To compile press `Ctrl+Shift+P` > `Run Tasks` > `Meson` > `Compile Q1`(or any Q. you like).
- To run press `Ctrl+Shift+P` > `Run Tasks` > `Meson` > `Run Q1`(or any Q. you like).

To compile code for all platforms run `bash ./compile_all.sh` in the working directory.

To manually compile run `meson setup builddir` in root of project. Then run `cd builddir`, then run `ninja`. The compiled files will be under `builddir/src` folder.

### Docker
The dev environment docker image can be found at [this page](https://github.com/users/jaideepheer/packages/container/package/csl7450-cg-assignment_1-opengl_basics%2Fdevenv).

Use the link on the above page to pull the development environment that contains all the dependencies to build the software. The see steps in VSCode setup above to get commands to setup the dev. environment.
