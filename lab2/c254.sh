#!/bin/sh
echo "Vui lòng nhập 1 chuỗi: "
read string
check=0
if grep -l "$string" *.txt
then
    check=1
fi
if [ "$check" -eq 0 ] 
then
    echo "Chuỗi \"$string\" không tồn tại trong file text nào trong thư mục hiện tại."
fi
exit 0
