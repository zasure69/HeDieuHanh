#!/bin/sh
echo "Vui lòng nhập tên: "
read name
echo "Vui lòng nhập MSSV:"
read mssv
while [ "$mssv" != "22520410" ];do 
    echo "MSSV không đúng với MSSV của sinh viên $name. Vui lòng nhập lại: "
    read mssv
done
echo "MSSV của sinh viên $name là $mssv."
exit 0
