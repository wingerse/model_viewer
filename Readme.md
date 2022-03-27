# Model Viewer  
Loads and displays models with at least a mesh, diffuse and specular maps.  
The material paths should be relative to the model file.  
Requires OpenGL 4.6  

# Setup
- Install cmake and g++

      sudo apt install cmake g++

- Install glfw (for windowing) and assimp (for model loading):

      sudo apt install libglfw3-dev libassimp-dev

- Create build directory:  

      cmake -S . -B cmake-build-release -DCMAKE_BUILD_TYPE=Release

- Build the executable:

      cmake --build cmake-build-release

- Executable can be found in `cmake-build-release/model_viewer`

## Usage  

    model_viewer [model_path]  

If no path is given, it is assumed to be `assets/pudge/pudge.obj`

![](https://i.imgur.com/k9YglnZ.png)