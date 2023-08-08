obj= manage.o user.o fly.o main.o
fly:${obj}
	gcc -o fly ${obj}
main.o:main.c main.h
	gcc -c main.c -o main.o
manage.o:manage.c main.h
	gcc -c manage.c -o manage.o
user.o:user.c main.h
	gcc -c user.c -o user.o
fly.o:fly.c main.h
	gcc -c fly.c -o fly.o
clear:
	rm *.o
