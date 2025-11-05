# ACADSoft
This is a passion project where a CAD software design is made using core OpenGL system

>Core idea 

```
-> Design a basic opengl window 
-> Give ability to design shapes and line
-> Allow a 2D map world space
```

>Target 
```
-> Learn Basics of **OpenGl**
-> Use it to create a demo CAD Software
-> Time Limit one Month
```





> Note
```
Repository contains the launch configs for VScode to run/compile using NVCC to speed up the development process
```

> Compile setup instruction

1. Download glad.h from the official glad download source

2. Downlad the glfw and compile it using cmake

3. Add the the files into include folder in the workspace

4. Add the glad.c in the src folder in the workspace

> **Note**

The launch is configured to run nvcc based on Archlinux based distribution
For any other distribution change the launch.json as following
-> change the path of nvcc from /opt/cuda/bin/nvcc to path_to_nvcc/nvcc
-> or change it to your desired compiler 