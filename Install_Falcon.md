# Steps to Install Falcon

**Original**: 
https://github.com/falkenber9/falcon

**Fork**:

## **Ubuntu**

* Installation System: Ubuntu 18.04

## **Installation**

(1) Install libs

* srsLTE libs

```
sudo apt-get install build-essential git cmake libfftw3-dev libmbedtls-dev libboost-program-options-dev libconfig++-dev libsctp-dev
```

* srsGUI
```
sudo apt-get install libboost-system-dev libboost-test-dev libboost-thread-dev libqwt-qt5-dev qtbase5-dev
git clone https://github.com/srsLTE/srsGUI.git
cd srsgui
mkdir build
cd build
cmake ../
make
sudo make install
```


* USRP support
```
sudo add-apt-repository ppa:ettusresearch/uhd
sudo apt-get update
sudo apt-get install libuhd-dev uhd-host
```

* FALCON
```
sudo apt-get install libglib2.0-dev libudev-dev libcurl4-gnutls-dev libboost-all-dev qtdeclarative5-dev libqt5charts5-dev
```

(2) Connect B210 and set up the image downloader first

```
uhd_usrp_probe
```

If FPGA build has any error, run the `uhd_image_downloader.py` as the error ouput.


(3) FALCON
```
git clone https://github.com/falkenber9/falcon.git
cd falcon
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr ../
make

# Install (optional)
sudo make install

# Uninstall (use carefully!)
sudo xargs rm < install_manifest.txt
```


## **Search Cell and Run**
```
cd /falcon/build/srsLTE-build/lib/examples/
./cell_search -b 2


FalconGUI
```

