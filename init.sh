echo Start to install tools needed
sudo apt install rename -y
sudo apt install sed -y
sudo apt install ack -y
sudo apt install vim -y
sudo apt install cmake -y
echo Install done!
chmod +x ./test/reset_test.sh
chmod +x ./change_r.sh
./test/reset_test.sh
./change_r.sh
cp -r test ../
