.PHONY:all
all:libmydynamic_lib1.so libmystatic_lib1.a

libmydynamic_lib1.so:mymath_d.o myprint_d.o
	gcc -shared $^ -o $@
mymath_d.o:mymath.c
	gcc -fPIC -c $^ -o $@
myprint_d.o:myprint.c
	gcc -fPIC -c $^ -o $@

libmystatic_lib1.a:mymath.o myprint.o
	ar -rc $@ $^
mymath.o:mymath.c
	gcc -c $^ -o $@
myprint.o:myprint.c
	gcc -c $^ -o $@

.PHONY:lib1
lib1:
	mkdir -p lib1/include
	mkdir -p lib1/lib
	cp *.h lib1/include
	cp libmystatic_lib1.a lib1/lib
	cp libmydynamic_lib1.so lib1/lib
.PHONY:clean
clean:
	rm -rf *.o *.a *.so lib1

