#!/bin/sh
echo "Vui lòng nhập số n: "
read n
while [ "$n" -lt 10 ];do 
    echo "Số n phải lớn hơn hoặc bằng 10. Vui lòng nhập lại: "
    read n
done
sum=0
i=1
while [ "$i" -le "$n" ];do
    sum=$(($sum + $i))
    i=$(($i + 1))
done
echo "Tổng các số từ 1 đến $n là $sum"
exit 0
