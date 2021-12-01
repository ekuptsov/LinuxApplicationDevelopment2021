GENERATES = out* ans* range
GREEN = '\033[1;32m'

all: test

range:	range.c
	gcc -O0 -g range.c -o range

test:	test1 test2
	echo ${GREEN}Tests completed!${GREEN}

test1:	range
	gdb -x test1 -batch range | grep = | cut -d'=' -f2 | tr -d ' ' > out1
	python3 -c "print(1, 12, 1, *[i for i in range(1, 12) if i%5 == 0], sep='\n')" > ans1
	cmp out1 ans1

test2:	range
	gdb -x test2 -batch range | grep = | cut -d'=' -f2 | tr -d ' ' > out2
	python3 -c "print(-100, 100, 3, *list(range(-100, 100, 3))[27:35], sep='\n')" > ans2
	cmp out2 ans2

clean:
	rm -f $(GENERATES)
