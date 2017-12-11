build :
	gcc -o main.out -Wall main.c 

run : build
	./main.out

clean :
	rm *.out
