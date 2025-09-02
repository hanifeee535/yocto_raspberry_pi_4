
# Custom Linux Distribution for Raspberry Pi 4 with Integrated Qt/QML Application

This repository provides all the necessary layers and configurations to build a custom Linux image for the Raspberry Pi 4 using the Yocto Project. The final image will include a fully integrated Qt/QML application, allowing for a polished and purpose-built embedded system.

The setup includes the Poky build system, meta-openembedded, meta-qt6, and meta-raspberrypi layers.

## Prerequisites

Before you begin, make sure your build host is a Linux environment with the necessary Yocto dependencies. On Ubuntu/Debian-based systems, you can install the required packages with the following command:

sudo apt-get install gawk wget git diffstat unzip texinfo gcc-multilib build-essential \
chrpath socat cpio python3 python3-pip python3-pexpect xz-utils debianutils \
iputils-ping libsdl1.2-dev xterm

##Getting started: 
Clone the repository: 
git clone https://github.com/hanifeee535/yocto_raspberry_pi_4.git
cd yocto_raspberry_pi_4

Integrate the submodules: 
git submodule init
git submodule update --recursive


Set up the build environment: 
source poky/oe-init-build-env ../build

configure your build by modifying the bblayers.conf file and local.conf file

Run the following command to build a test image for rasperry pi: 
bitbake rpi-test-image


Flashing the image to sd card: 
cd build/tmp/deploy/images/raspberrypi4-64/
bzcat rpi-test-image-raspberrypi4-64.wic.bz2 | sudo dd of=/dev/sdb bs=4M status=progress conv=fsync

