mylib1:mymath.o myprint.o
	ar -rc lib$@.a $^
mymath.o:mymath.c
	gcc -c $^ -o $@
myprint.o:myprint.c
	gcc -c $^ -o $@
.PHONY:lib1
lib1:
	mkdir -p lib1/include
	mkdir -p lib1/lib
	cp *.h lib1/include
	cp libmylib1.a lib1/lib
.PHONY:clean
clean:
	rm -f *.o libmylib1.a
	rm -rf lib1

