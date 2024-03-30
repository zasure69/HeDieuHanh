#!/bin/sh
echo "Vui lòng nhập họ và tên (viết liền không dấu):"
read name

#kiểm tra thư mục tồn tại chưa
#nếu chưa thì tạo
if [ ! -d "./$name" ];then
    mkdir ./$name
fi

#đọc file
file=`cat ./monhoc.txt`
for i in $file;
do  
    #kiểm tra thư mục tồn tại chưa
    #nếu chưa thì tạo
    if [ ! -d "./$name/$i" ];then
        mkdir -p ./$name/$i
    fi
done
