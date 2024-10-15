,PHONY:all
all: myfile mybit
myfile:file_test.c
	gcc -o $@ $^
mybit:bitset.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -f myfile mybit
