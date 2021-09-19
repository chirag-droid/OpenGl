# OpenGl

This is my first c++ project with OpenGl. Useful resources for learning OpenGl:

- freeCodeCamp.org's OpenGl course by [VictorGordan](https://github.com/VictorGordan) - https://www.youtube.com/watch?v=45MIykWJ-C4
- [TheCherno](https://youtube.com/c/TheChernoProject) OpenGl series on youtube - https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2
- [OpenGl docs](https://docs.gl)
- http://www.opengl-tutorial.org/

## Compiling from source

- ### Downloading the repository
  Start by cloning the repository with `git  clone --recursive https://github.com chirag-droid/OpenGl`. This will download the repository and also download the submodules glfw and glad.

  If the repository was cloned non-recursively previously, use git submodule update --init to clone the necessary submodules.

- ### Toolchain
  The project uses Cmake for build automation. Cmake generates files for other build system e.g. Ninja, make, nmake etc.

  I, use Ninja but you can use any build system you have.

  > Note that a working python installation is also required to generate glad files.

- ### Compiling
  First generate file for your build system using 
  
  `
  cmake -S . -B build/ -G (ninja | <your_build_system>)
  `

  The S flag specifies the source directory, while B flag specifies the build directory. And the G flag specifies the generator to use

  Next go to the newly generated build directory by using `cd build`. Now use the command for the generator you used. I used ninja so running `ninja` will make an executable file called `main.exe`.

If you encounter any error while doing so, feel free to open an issue
