#make cacu
cacu:add_int.o add_float.o sub_int.o sub_float.o main.o
	gcc -o cacu add/add_int.o add/add_float.o \
		sub/sub_int.o sub/sub_float.o main.o
#make add_int.o
add_int.o:add/add_int.c add/add.h
	gcc -c -o add/add_int.o add/add_int.c

#make add_float.o
add_float.o:add/add_float.c add/add.h
	gcc -c -o add/add_float.o add/add_float.c

#make sub/sub_int.o
sub_int.o:sub/sub_int.c sub/sub.h
	gcc -c -o sub/sub_int.o sub/sub_int.c

#make sub/sub_float.o
sub_float.o:sub/sub_float.c sub/sub.h
	gcc -c -o sub/sub_float.o sub/sub_float.c

#make main.o
main.o:main.c add/add.h sub/sub.h
	gcc -c -o main.o main.c -Iadd -Isub

clean:
	rm -f cacu add/add_int.o add/add_float.o \
		sub/sub_int.o sub/sub_float.o main.o
hello:
	echo "this is a test for 'make hello'"
