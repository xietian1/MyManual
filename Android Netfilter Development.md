# Android Netfilter Development Guide
-Update by 4/22/2021

Use iptables to forward packets to the netfilter_queue
```
//Insert the forward command to OUTPUT
iptables -I OUTPUT -j NFQUEUE --queue-num 0

//Delete the rule we just add
iptables -D OUTPUT -j NFQUEUE --queue-num 0
```
