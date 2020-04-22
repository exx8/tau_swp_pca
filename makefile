FLAGS =  -Wall -Wextra -Werror -pedantic-errors
LIBS = -lm

all: cov eigen
clean:
	rm -rf *.o cov eigen

cov: cov.o
	gcc cov.o -o cov $(LIBS)
cov.o: cov.c
	gcc $(FLAGS) -c cov.c

eigen: eigen.o
	gcc eigen.o -o eigen $(LIBS)
eigen.o: eigen.c
	gcc $(FLAGS) -c eigen.c

