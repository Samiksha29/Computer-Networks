<h1>File transfer between muliple machine using ADHOC network</h1>

<h3>TCP</h3>

<h3>How to connect machines<h3>
$sudo service network-manager stop (To turn off network manager)</br>
$./script</br> 

<h3>How to check machine is connected or not</h3>
let assume Ip address of</br>
machine 1->192.168.1.201</br>
machine 2->192.168.1.202</br>
$ping 192.168.1.202  (from machine 1)</br>

<h3>How to run program</h3>
<h5>(Run on first machine)</h5>
$gcc server.c -o s</br>
$./s</br>

<h5>(Run on second machine)</h5>
$gcc client.c -o c</br>
$./c</br>
