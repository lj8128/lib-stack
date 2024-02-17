lib_options = -I../lib-hash-table/src -I../lib-test-framework/src -I./src -L../lib-test-framework/build -L../lib-hash-table/build -L./build -Wl,--no-as-needed,-rpath=../lib-test-framework/build -Wl,--no-as-needed,-rpath=../lib-hash-table/build -Wl,--no-as-needed,-rpath=./build -ltest_framework -lhash_table -lstack

all: ./build/libstack.so ./bin/tester.bin

./bin/tester.bin: ./test/test_stack.c
	gcc ./test/test_stack.c $(lib_options) -g -Wall -o ./bin/tester.bin

./build/libstack.so: ./build/stack.o
	gcc -shared ./build/stack.o -o ./build/libstack.so

./build/stack.o: ./src/stack.c
	gcc -fPIC -c -g -Wall ./src/stack.c -o ./build/stack.o

clean:
	rm -f ./build/*.o
	rm -f ./build/*.so

