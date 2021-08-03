# Android Netfilter Development Guide
-Update by 7/29/2021


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