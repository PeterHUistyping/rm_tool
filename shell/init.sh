p=test/install.log
test=../test
echo Start to install tools needed
echo Install log has been written to $p
sudo apt-get install rename -y >$p
sudo apt-get install sed -y >> $p
sudo apt-get install ack -y >> $p
sudo apt-get install vim -y >> $p
sudo apt-get install cmake -y >> $p
echo Installation done!

if ! [ -d "$test" ]; then 
    mkdir ../test
fi

chmod +x ./test/reset_test.sh
chmod +x shell/change_r.sh
./test/reset_test.sh
./shell/change_r.sh
sudo chmod -R 777  test
sudo chmod -R 777  backup_test
sudo cp -f backup_test/* ../test
sudo cp -f backup_test/* test/
sudo chmod -R 777 ../test
