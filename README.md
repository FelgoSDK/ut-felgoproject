# ut-felgoproject
Proof of concept / Example project for Qt, Felgo and Ubuntu Touch.

The example contained in this repository is based on Felgo's Flappy Bird game demo: <https://felgo.com/doc/felgo-demos-flappybird-example/>

![img](https://felgo.com/doc/images/flappy-ready.png)


## Notes
Prequestite: Clickable installed and basic knowledge of development for Ubuntu Touch

Example commands to build, install and run app on a device:
```
export CLICKABLE_SSH=10.0.0.15   # Required for devices without adb, i.e. PinePhone ---> Use SSH for transfer
export CLICK_ARCH=arm64 && export CLICKABLE_ARCH=$CLICK_ARCH  # Set architecture (amd64|arm64|armhf)
clickable
```
