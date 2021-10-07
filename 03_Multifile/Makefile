OUTPUT = README file1 file2 file3
GENERATES = prog prog-a prog-so *.so $(OUTPUT)
TRASH = *.o *~ o.* *.a
CFLAGS = -Wall -fPIC
GREEN = '\033[1;32m'

ARG1 = LNX1LOVE
ARG3 = MAMA MYLA RAMU

all:	README prog prog-a prog-so

test:	test0 test1 test3
	echo ${GREEN}Test completed!${GREEN}

test0:	prog prog-a prog-so
	./prog 2> file1 && vim '+%s/\<prog\>//g' +wq file1
	./prog-a 2> file2 && vim '+%s/\<prog-a\>//g' +wq file2
	./prog-so 2> file3 && vim '+%s/\<prog-so\>//g' +wq file3
	cmp file1 file2
	cmp file1 file3
	cmp file2 file3

test1:	prog prog-a prog-so
	./prog $(ARG1) > file1
	./prog-a $(ARG1) > file2
	./prog-so $(ARG1) > file3
	cmp file1 file2
	cmp file1 file3
	cmp file2 file3

test3:	prog prog-a prog-so
	./prog $(ARG3) > file1
	./prog-a $(ARG3) > file2
	./prog-so $(ARG3) > file3
	cmp file1 file2
	cmp file1 file3
	cmp file2 file3

fun.o:	outlib.h

prog:	const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
	gcc -L. prog.o -loutput_static -o prog-a

prog-so:prog.o liboutput.so
	gcc -L. prog.o -loutput -o prog-so

README: prog
	./$< 2 > $@

liboutput_static.a: fun.o const.o
	ar -rcs liboutput_static.a fun.o const.o

liboutput.so: fun.o const.o
	gcc -shared fun.o const.o -o liboutput.so

clean:
	rm -rf $(TRASH)

distclean: clean
	rm -rf $(GENERATES)
