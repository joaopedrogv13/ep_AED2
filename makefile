ep1_matriz_13731070.exe: grafo_matrizadj.o main.o 
	gcc -o ep1_matriz_13731070.exe grafo_matrizadj.o main.o 

ep1_lista_13731070.exe: grafo_listaadj.o main.o
	gcc -o ep1_lista_13731070.exe grafo_listaadj.o main.o 

grafo_matrizadj.o: grafo_matrizadj.c grafo_matrizadj.h
	gcc -c grafo_matrizadj.c

grafo_listaadj.o: grafo_listaadj.c grafo_listaadj.h
	gcc -c grafo_listaadj.c

main.o: #aqui vao as dependencias do seu main.o
	gcc -c main.c

clean:
	rm -f *.o *.exe