tr '\r' ' ' < rm.sh > rm_.sh
mv rm_.sh rm.sh
chmod +x rm.sh
 
 tr '\r' ' ' < shell/init.sh > init_.sh
mv init_.sh shell/init.sh
chmod +x shell/init.sh

 