GENERATES = move *.o *.so
TEST_TRASH = infile* outfile err* ans*
GREEN = '\033[1;32m'

all: move test

move: move.o

protect.so: protect.c
	gcc -shared protect.c -o protect.so -ldl

infile: move
	cat move move move > infile

test: test_default test_inject test_preload
	echo ${GREEN}Tests completed!${GREEN}

test_default: move infile
	cp infile infile.tmp
	./move infile outfile
	test -f outfile
	test ! -f infile
	cmp infile.tmp outfile
	mv outfile infile
	rm -f infile.tmp

test_inject: move infile test_openin test_openout test_read test_write test_closein test_closeout

test_openin: move infile
	strace -e openat -fo /dev/null -e inject=openat:error=EPERM:when=11 ./move infile outfile 2> err0
	cat err0 | cut -d':' -f 2 | xargs > err1
	LC_ALL=en_US errno -l | grep ^EPERM | cut -d' ' -f 3- > ans1
	cmp err1 ans1
	test -f infile
	test ! -f outfile

test_openout: move infile
	strace -e openat -fo /dev/null -e inject=openat:error=ENOMEM:when=12 ./move infile outfile 2> err0
	cat err0 | cut -d':' -f 2 | xargs > err2
	LC_ALL=en_US errno -l | grep ^ENOMEM | cut -d' ' -f 3- > ans2
	cmp err2 ans2
	test -f infile
	test ! -f outfile

test_read: move infile
	strace -fo /dev/null -e inject=read:error=EAGAIN:when=3 ./move infile outfile 2> err0
	cat err0 | cut -d':' -f 2 | xargs > err3
	LC_ALL=en_US errno -l | grep ^EAGAIN | cut -d' ' -f 3- > ans3
	cmp err3 ans3
	test -f infile
	test ! -f outfile

test_write: move infile
	strace -fo /dev/null -e inject=write:error=EAGAIN:when=2 ./move infile outfile 2> err0
	cat err0 | cut -d':' -f 2 | xargs > err4
	LC_ALL=en_US errno -l | grep ^EAGAIN | cut -d' ' -f 3- > ans4
	cmp err4 ans4
	test -f infile
	test ! -f outfile

test_closein: move infile
	strace -fo /dev/null -e inject=close:error=EINTR:when=3 ./move infile outfile 2> err0
	cat err0 | cut -d':' -f 2 | xargs > err5
	LC_ALL=en_US errno -l | grep ^EINTR | cut -d' ' -f 3- > ans5
	cmp err5 ans5
	test -f infile
	test ! -f outfile

test_closeout: move infile
	strace -fo /dev/null -e inject=close:error=EINTR:when=4 ./move infile outfile 2> err0
	cat err0 | cut -d':' -f 2 | xargs > err5
	LC_ALL=en_US errno -l | grep ^EINTR | cut -d' ' -f 3- > ans5
	cmp err5 ans5
	test -f infile
	test ! -f outfile

test_preload: move infile protect.so
	cp infile infile.PROTECT
	LD_PRELOAD=`pwd`/protect.so ./move infile.PROTECT outfile
	cmp infile outfile
	test -f infile.PROTECT
	test -f outfile
	rm -f infile.PROTECT

clean:
	rm -f $(GENERATES) $(TEST_TRASH)