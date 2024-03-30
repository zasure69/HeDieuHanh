#!/bin/bash

#kiểm tra thư mục có tồn tại không
if [ ! -d ~/PNG ]
then 
    mkdir ~/PNG
fi

if [ ! -d ~/JPG ]
then 
    mkdir ~/JPG
fi
#kiểm tra xem có còn file png trong thư mục OS_LAB2_IMG/ không 
#nếu còn thì di chuyển sang thư mục PNG
if [ "$(find ~/OS_LAB2_IMG/  -name  "*.png" | wc -l)" != 0 ];
then
    mv ~/OS_LAB2_IMG/*.png ~/PNG
fi
#đếm file png
echo "Số lượng ảnh PNG:"
echo $(ls -l ~/PNG| wc -l)

#kiểm tra xem có còn file jpg trong thư mục OS_LAB2_IMG/ không 
#nếu còn thì di chuyển sang thư mục JPG
if [ "$(find ~/OS_LAB2_IMG/  -name  "*.jpg" | wc -l)" != 0 ];
then
    mv ~/OS_LAB2_IMG/*.jpg ~/JPG
fi
#đếm file jpg
echo "Số lượng ảnh JPG:"
echo $(ls -l ~/JPG| wc -l)
