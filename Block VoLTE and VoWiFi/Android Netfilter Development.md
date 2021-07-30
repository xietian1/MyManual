# Android Netfilter Development Guide
-Update by 7/29/2021


**Tool Usage**
1. Push blockipv6esp to Android
```
adb push blockipv6esp /data/local/tmp/
```

2. Change its mode
```
adb shell
su
chmod +x /data/local/tmp/blockipv6esp
./blockipv6esp
```

3. Forward packet to our app
```
//insert
ip6tables -I OUTPUT -j NFQUEUE --queue-num 0
//remove
ip6tables -D OUTPUT -j NFQUEUE --queue-num 0
//check
ip6tables -L OUTPUT
```

4. Make a VoLTE/VoWiFi phone call.

**Development Guide**

Use iptables to forward packets to the netfilter_queue
```
//Insert the forward command to OUTPUT
iptables -I OUTPUT -j NFQUEUE --queue-num 0

//Delete the rule we just add
iptables -D OUTPUT -j NFQUEUE --queue-num 0

//For ipv6 (VoLTE, VoWiFi are both IPV6 based)
ip6tables -L OUTPUT
ip6tables -I OUTPUT -j NFQUEUE --queue-num 0
ip6tables -D OUTPUT -j NFQUEUE --queue-num 0
```


Rules Example:
https://www.linux.com/topic/networking/iptables-rules-ipv6/