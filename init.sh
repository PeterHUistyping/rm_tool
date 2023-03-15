echo Start to install tools needed
sudo apt install rename -y
sudo apt install sed -y
sudo apt install ack -y
sudo apt install vim -y
echo Install done!
./test/reset_test.sh
./change_r.sh