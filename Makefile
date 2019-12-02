run: compilar
	clear
	./executar

compilar: main.o operacoes.o
	gcc  main.o  operacoes.o -o executar

main.o: main.c
	gcc -c -Wall main.c 

operacoes.o: bibliotecas/estruturas.h bibliotecas/operacoes.c bibliotecas/codigo_erros.h bibliotecas/mensagens.h bibliotecas/telas.h
	gcc -c -Wall bibliotecas/estruturas.h bibliotecas/operacoes.c bibliotecas/codigo_erros.h bibliotecas/mensagens.h bibliotecas/telas.h
	
clear:
	rm -rf executar *.o  
	clear
	
