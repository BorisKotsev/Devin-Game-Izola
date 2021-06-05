# DevinGame
This is a project representing Izola. It is a custom game.

### Building and Running the project ###
To build and run this project you will need SDL2 and SDL_image, which you should download and compile. I recommend you to create new folder named "include" and place it there. Otherwise, you will have to change SDL2_DIR and SDL2_image_DIR variable in CMakeLists.cmake.

After you have installed the prerequisites for the project follow the steps below to build and run it.

**Linux**

``` shell
mkdir build && cd build
cmake ../
make -jN #where N is the number of jobs you want to use
./Izola #run the project
```

**Windows**\
It is important to note the you will need the path to the vcpkg installation from the previous steps
``` shell
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]\scripts\buildsystems\vcpkg.cmake ../
cmake --build .
cd Debug # or Release depending on the build mode
Izola.exe #run the project
```
