# Android Netfilter Development Guide
-Update by 7/29/2021

**APP Usage**

```
Please use the following commands
Get help: ./block -h
Block IPV6 packet by protocol: ./block -p [Protocol]
    Protocl List: TCP, UDP, ESP
Block IPV6 packet by packet length: ./block -l [Length]

E.g., Block IPV6 packet by TCP with packet with a size over 900 (start from IP layer):
./block -p TCP -l 900
```

**Tool Usage**
1. Push block to Android
```
adb push block /data/local/tmp/
```

2. Change its mode
```
adb shell
su
chmod +x /data/local/tmp/block
./block -p ESP -l 900 //Block IPV6 packet by TCP with packet with a size over 900 (start from IP layer)
```

3. Set iptables
```
//insert
ip6tables -I OUTPUT -j NFQUEUE --queue-num 0
//check
ip6tables -L OUTPUT
```

4. Make a VoLTE/VoWiFi phone call.



5. Reset iptables
```
//remove
ip6tables -D OUTPUT -j NFQUEUE --queue-num 0
//check
ip6tables -L OUTPUT
```

6. Ctrl+C to terminate block app
