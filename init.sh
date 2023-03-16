p=test/install.log
echo Start to install tools needed
echo Install log has been written to $p
sudo apt-get install rename -y >> $p
sudo apt-get install sed -y >> $p
sudo apt-get install ack -y >> $p
sudo apt-get install vim -y >> $p
sudo apt-get install cmake -y >> $p
echo Install done!
chmod +x ./test/reset_test.sh
chmod +x ./change_r.sh
./test/reset_test.sh
./change_r.sh
sudo  chmod -R 777  test
sudo cp -f -r test ../
sudo chmod -R 777 ../test
