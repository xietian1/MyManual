# How to develop Android App with the special permission requirement

We are developing the Android Apps with the Android API [`getIccAuthentication`][link1] requiring the specific permission:

`Requires Permission: READ_PRIVILEGED_PHONE_STATE or that the calling app has carrier privileges (see hasCarrierPrivileges()).`


The second one **the calling app has carrier privileges** requires that the app has the carrier's UID. Now, I didn't figure out how to get it.

The following method gives the Apps some specific permission including *READ_PRIVILEGED_PHONE_STATE*. Note that a **rooted phone is required**.


## Install the App on Android as a system App

1. Claim the permission in the `Manifest.xml` of the project.
For instance,
```java
<?xml version="1.0" encoding="utf-8"?>
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    package="com.example.xxxxxxx">
    <uses-permission android:name="android.permission.INTERNET"/>
    <uses-permission android:name="android.permission.READ_PHONE_STATE"/>
    <uses-permission android:name="android.permission.MODIFY_PHONE_STATE"/>
    <uses-permission android:name="android.permission.READ_PRIVILEGED_PHONE_STATE"/>
```
2. Remember to grant some regular permissions on the App's MainActivity under the `onCreate()`. Since from Android 6.0, all Apps need to get the grant from the users as shown below:
```java
        if (ContextCompat.checkSelfPermission(this, android.Manifest.permission.READ_PHONE_STATE) != PackageManager.PERMISSION_GRANTED) {

            ActivityCompat.requestPermissions(this, new String[]{android.Manifest.permission.READ_PHONE_STATE}, 0);
        }
``` 
3. Generate the apk file using Android Studio. 
4. Put the apk file in the sdcard and use `Root Explore` to copy the apk into system app path `/system/priv-app/xxx/`. (xxx can be the apk's name) Change the apk permission to '0777'.
5. We next modify the whitelists on Android.
* Copy the permission whitelists in XML files out to the PC to modify, which locates at `/etc/permissions/privapp-permissions-DEVICE_NAME.xml`. E.g., DEVICE_NAME of Nexus 6P is 'angler'.
* Add the following code into the *xml* file. Change the permission as your requirement.
```java
<privapp-permissions package="com.android.xxxxxxx">
    <permission name="android.permission.MANAGE_USERS"/>
    <permission name="android.permission.MODIFY_PHONE_STATE"/>
    <permission name="android.permission.READ_PRIVILEGED_PHONE_STATE"/>
    <permission name="android.permission.RECEIVE_EMERGENCY_BROADCAST"/>
</privapp-permissions>
```
* Move the xml file back `/etc/permissions/` and overwrite the previous file.
6. Reboot the phone.
7. Now, the app with the specific permission is installed and can run correctly.
 


## Debug the system app

To be continued...


[link1]: https://developer.android.com/reference/android/telephony/TelephonyManager#getIccAuthentication(int,%20int,%20java.lang.String)
