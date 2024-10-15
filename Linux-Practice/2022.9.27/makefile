.PHONY:all
all: test proc
proc:proc.c
	gcc -o $@ $^
test:test.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -f proc test
