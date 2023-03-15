echo ----reset_test----
rm -rf deletedLog
rm -rf searchLog
cp -r backup_test/* test
cp -r backup_test/* ../test
echo ----reset_test Done!----