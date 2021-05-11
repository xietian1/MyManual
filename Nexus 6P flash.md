# Hints for flashing Nexus 6P with BLOD issue

## Ref Link: 
Check the [link][link1] for more information about how to modify the rom. You'll need to configure the system to use 3 CPUs.


## fastboot: error: Couldn't parse partition size '0x'

You have to manually flash each img file instead of directly using flash.bat.

1. Extract the "angler-opm7.181205.001-factory-b75ce068.zip" archive.

2. Extract the contents of the "image-angler-opm7.181205.001.zip" into the same directory it can be found in (angler-opm7.181205.001).

3. Execute the following commands:

```
fastboot flash bootloader bootloader-angler-angler-03.84.img
fastboot reboot-bootloader
fastboot flash radio radio-angler-angler-03.88.img
fastboot reboot-bootloader
fastboot flash vendor vendor.img
fastboot reboot-bootloader
fastboot flash system system.img
fastboot flash:raw boot boot.img
fastboot flash recovery recovery.img
```

[link1]: https://forum.xda-developers.com/t/guide-tutorial-fix-nexus-6p-bootloop-of-death-boot-image-patch-android-8-1-more.3716330/


