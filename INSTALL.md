##DEPENDENCIES

### [pixkit](https://github.com/estebanrdo/pixkit)


### [OpenCV](https://github.com/opencv/opencv)

CMAKE:
- OPENCV_EXTRA_MODULES_PATH
- OPENCV_ENABLE_NONFREE (for SIFT and SURF)
- WITH_CUDA

### [Boost](https://www.boost.org)

https://sourceforge.net/projects/boost/files/boost-binaries/


## Install

```
git clone https://github.com/TIDOP-USAL/photomatch.git
```

```
cd photomatch
mkdir build
cd build
cmake ..
sudo make
sudo make install
```
