# OpenWRT Kernel Module Development Guide
-Update by 4/22/2021

It is a simple document to help develop simple kernel module on openWRT. Different from the common package/app, with a kernel module, we can set a hook function using netfilter to intercept packets from the kernel layer. *Note that openWRT has frequent updates and the following information is only up-to-date on the specified date.* 

## Setting 
* A PC (better with a Internet interface) with ubuntu 16.04 (Any linux system may work. Feel free to check out openWRT [website][link2].)
* A Wi-Fi router that is supported by openWRT. The tested router on this document is [TP-Link Archer C7 AC 1750 V3][link1]. 

Hint: If you want to connect the openWRT router to the existing router, you can use a Internet cable to connect a LAN port of the existing router (denoted as A) to the WAN port of the openWRT router (denoted as B). Make sure the IP address of the LAN port of the A router is different from the LAN port of the B router. E.g., if the IP address of the LAN port of A router is 192.168.1.1, the IP address of the LAN port of B router can be changed to 192.168.2.1 or 192.168.10.1. 


## A. Configure SDK environment for building your own image/package/kernel module.
1. Refer the [OpenWRT instruction][link2] to install the required dependencies.
2. Use the **Model** and **Version** of the router to find **firmware**. 
   
   E.g., The firmware of [TP-Link Archer C7 AC 1750 V3][link1] is shown as
``http://downloads.openwrt.org/releases/19.07.7/targets/ath79/generic/openwrt-19.07.7-ath79-generic-tplink_archer-c7-v2-squashfs-factory.bin''. So we can use openWRT version **19.07** with the target **ath79 generic**. 

	Note: *Don't download the firmware here. You need to build the image anyway to ensure you have the correct linux kernel version for creating kernel module.*
1. Download the source code. 
```
git clone https://git.openwrt.org/openwrt/openwrt.git
cd openwrt
git branch
git checkout <branch/tag name> // here we select v19.07.7
./scripts/feeds update -a
./scripts/feeds install -a
```
4. Configure the SDK
```
make menuconfig
```
This opens the OpenWrt configuration menu for setting target and options.

E.g. for target [TP-Link Archer C7 AC 1750 V3][link1] Wi-Fi router do following:

“Target System” ⇒ “Select” ⇒ “Atheros ATH79 (DTS)” ⇒ “Select” 

“Subtarget” ⇒ “Select” ⇒ “Generic” ⇒ “Select” 

“Target Profile” ⇒ “Select” ⇒ "TP-Link Archer C7 v2" ⇒ “Select”

5. Build image
```
make
```
Completion can take time.If successful, the images are in directory ./bin/targets/ath79/generic/

* The *-factory.bin image file is for the first installation of OpenWrt on the target.
* The *-sysupgrade.bin image file is for updating an existing OpenWrt installation.

Then, flash the system to the router.


## B. Create your own module
1. Create a folder in (path to SDK)/package/kernel/. 
 
This document provides an example kernel module `mydrv`. You can directly copy the folder "mydrv" to `(path to SDK)/package/kernel/`. 

The structure of the kernel module is the same as the structure of the package/app on openWRT.

```bash
--mydrv
  |
  |--Makefile
  |--src
	 |--Makefile
	 |--mydrv.c
	 |--Kconfig
```

The example kernel module can print all TCP packets source port and dest port. 

Before moving to the next step, make sure you understand the Makefile in the main folder `mydrv`. 

2. Configure the SDK to build this kernel module  

cd to the `<path to SDK>`
```
make configure
```

Select 'Kernel modules' -> select 'Other modules' -> select 'kmod-mydrv'.

Save.


3. `make` will cost too much time since it will re-compile the whole SDK. We then use `make package/mydrv/compile V=s` to compile the kernel module itself.
   
4. If it compiles successfully, the package can be found in the path  `/bin/targets/ath79/generic/packages/xxx.ipk`

5. Copy the file xxx.ipk to the router. 

```
scp kmod-mydrv_4.14.221-1_mips_24kc.ipk root@192.168.10.1:~/
```

## C. Install the kernel module 

1. Connect to the router with ssh
```
ssh root@192.168.10.1
```
   
2. Use `opkg install xxx.ipk` or `opkg remove xxx` to install and remove the package. 
```
opkg install xxx.ipk
```

*If you didn't build the image by yourself, you may find that you can't install the package due to the incompatible kernel version.* 


3. Enable the module
   
```
insmod /libs/modules/<kernel version>/kmod-mydrv
```

4. Open some websites and then check the debug messages.

```
dmesg
```

5. Disable the module
```
rmmod kmod-mydrv
```

6. Remove the package
```
opkg remove kmod-mydrv
```



[link1]: https://openwrt.org/toh/tp-link/archer-c5-c7-wdr7500
[link2]: https://openwrt.org/docs/guide-developer/build-system/install-buildsystem#examples_of_package_installations
[link2]: https://openwrt.org/docs/guide-developer/quickstart-build-images