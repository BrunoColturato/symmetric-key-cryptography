all: Lista_Criptografia.o minhasFuncoes.o Lista_Criptografia.h main.o
	@gcc Lista_Criptografia.o minhasFuncoes.o main.o -o Projeto

Lista_Criptografia.o:
	@gcc -c Lista_Criptografia.c

minhasFuncoes.o:
	@gcc -c minhasFuncoes.c

main.o:
	@gcc -c main.c

run:
	@./Projeto
