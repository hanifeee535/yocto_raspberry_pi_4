# Custom Linux Distribution for Raspberry Pi 4 with Integrated Qt/QML Application

This repository provides all the necessary layers and configurations to build a custom Linux image for the Raspberry Pi 4 using the **Yocto Project**.  
The final image will include a fully integrated **Qt/QML application**, allowing for a polished and purpose-built embedded system.

The setup includes:

- Poky build system 
- meta-openembedded 
- meta-qt6 
- meta-raspberrypi 

---

## Prerequisites

Before you begin, make sure your build host is a **Linux environment** with the necessary Yocto dependencies.  

On **Ubuntu/Debian-based systems**, install the required packages with:

```bash
sudo apt-get install gawk wget git diffstat unzip texinfo gcc-multilib build-essential \
chrpath socat cpio python3 python3-pip python3-pexpect xz-utils debianutils \
iputils-ping libsdl1.2-dev xterm
```

---

##  Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/hanifeee535/yocto_raspberry_pi_4.git
cd yocto_raspberry_pi_4
```

### 2. Integrate the Submodules

```bash
git submodule init
git submodule update --recursive
```

### 3. Create Build Directory

Create a new `build` directory in the root folder:

```bash
mkdir build
```

### 4. Set Up the Build Environment

Run the Poky environment setup script:

```bash
source poky/oe-init-build-env ../build
```

---

### 5. Configure Your Build

Modify the `bblayers.conf` and `local.conf` files in the `build/conf/` directory.

Example `bblayers.conf`:

```conf
# POKY_BBLAYERS_CONF_VERSION is increased each time build/conf/bblayers.conf
# changes incompatibly
POKY_BBLAYERS_CONF_VERSION = "2"

BBPATH = "${TOPDIR}"
BBFILES ?= ""

BBLAYERS ?= " \
  /home/hanif/Desktop/yocto_rp4/yocto_raspberry_pi_4/poky/meta \
  /home/hanif/Desktop/yocto_rp4/yocto_raspberry_pi_4/poky/meta-poky \
  /home/hanif/Desktop/yocto_rp4/yocto_raspberry_pi_4/poky/meta-yocto-bsp \
  /home/hanif/Desktop/yocto_rp4/yocto_raspberry_pi_4/meta-raspberrypi \
  /home/hanif/Desktop/yocto_rp4/yocto_raspberry_pi_4/meta-openembedded/meta-oe \
  /home/hanif/Desktop/yocto_rp4/yocto_raspberry_pi_4/meta-openembedded/meta-python \
  /home/hanif/Desktop/yocto_rp4/yocto_raspberry_pi_4/meta-openembedded/meta-multimedia \
  /home/hanif/Desktop/yocto_rp4/yocto_raspberry_pi_4/meta-openembedded/meta-networking \
  /home/hanif/Desktop/yocto_rp4/yocto_raspberry_pi_4/meta-my_custom_layer \
  /home/hanif/Desktop/yocto_rp4/yocto_raspberry_pi_4/meta-qt6 \
  "
```

---

### 6. Build the Image

Run the following command to build a **test image** for Raspberry Pi 4:

```bash
bitbake rpi-test-image
```

---

### 7. Flashing the Image to SD Card

After the build completes, navigate to the deploy directory:

```bash
cd build/tmp/deploy/images/raspberrypi4-64/
```

Flash the image to an SD card:

```bash
bzcat rpi-test-image-raspberrypi4-64.wic.bz2 | sudo dd of=/dev/sdX bs=4M status=progress conv=fsync
```

*(Replace `/dev/sdX` with your actual SD card device path.)*

---

