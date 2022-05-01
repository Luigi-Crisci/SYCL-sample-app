# SYCL Cmake sample app
A simple SYCL application using CMake building system.

## Build  

### Requirements
- Cmake 3.22 or above
- One of the following SYCL compilers
  - hipSYCL
  - DPC++
- Gcc/clang

To build it, create a `build` directory in the main folder, go inside it and type
```bash
cmake .. -DSYCL_BACKEND=[hipSYCL | DPCPP] -DSYCL_DEVICE=[gpu | cpu | host]
```
If you're using DPCPP, don't forget to set the correct triple for your device using
```bash
-DCMAKE_CXX_FLAGS=" -fsycl-targets=YOUR_TRIPLE"
```

A file called `sample_app` will be placed in the build folder
