tr '\r' '\n' < rm.sh > rm_.sh
mv rm_.sh rm.sh
chmod +x rm.sh
 
 tr '\r' '\n' < init.sh > init_.sh
mv init_.sh init.sh
chmod +x init.sh

tr '\r' '\n' < test/reset_test.sh > test/reset_test_.sh
mv test/reset_test_.sh test/reset_test.sh
chmod +x test/reset_test.sh