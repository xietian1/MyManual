# RaspBerry Pi + 3.5 LCD = a Clock 


## 1. Prepare OS and write OS to disk

Download a system from https://downloads.raspberrypi.org/raspbian/images/

Note: Better download the OS released before 2020


## 2. Install packages and Update system

```
sudo apt-get install gedit cmake
```

Note: The following step can be done in the end. Without upgrade, the mouse point can possiblely disappear.

```
sudo apt-mark hold raspberrypi-bootloader
sudo apt-get update
sudo apt-get upgrade
```

## 3. Driver

Download and use driver
```
git clone https://github.com/waveshare/LCD-show.git
cd LCD-show/
sudo ./LCD35-show
```

Switch back to HDMI display:
```
sudo ./LCD-hdmi
```

## 4. Clock source code

```
mkdir ~/tmp
cd ~/tmp
git clone https://github.com/xietian1/pi-clock.git
cd pi-clock
sudo /usr/bash/ ./install.sh
```

## 5. Add as the startup program
```
mkdir /home/pi/.config/autostart
gedit /home/pi/.config/autostart/clock.desktop
```

What in the clock.desktop:
```
[Desktop Entry]
Type=Application
Name=Clock
Exec=chromium-browser --kiosk /home/pi/pi-clock/index.html
```

