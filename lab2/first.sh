#!/bin/sh
# first.sh
# Script này sẽ tìm trong các file ở thư mục hiện hành
# có chứa main( ) hay không, nội dung của file sẽ được
# hiển thị ra màn hình nếu tìm thấy.
for file in *
do
if grep -l 'main( )' $file
then
more $file
fi
done
exit 0