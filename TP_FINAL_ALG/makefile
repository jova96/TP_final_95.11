OBJETOS = Tipos/Cadenas.o Tipos/Structs_Simpletron.o Estados/estados_programa.o Tipos/Lista_IF.o  ejecutar.o entrada.o argumentos.o main.o
ESTADOS = Estados/
TIPOS = Tipos/

CC = gcc
CFLAGS = -Wall -pedantic -ansi -g


programa : $(OBJETOS)
	gcc -Wall -g -o programa $(OBJETOS)
	-rm -f $(OBJETOS)

$(TIPOS)Cadenas.o : $(TIPOS)
$(TIPOS)Structs_Simpletron.o :  $(TIPOS)
$(TIPOS)Lista_IF.o : $(TIPOS)
$(ESTADOS)estados_programa.o: $(ESTADOS)
argumentos.o : $(TIPOS) $(ESTADOS)
entrada.o : $(TIPOS) $(ESTADOS)
ejecutar.o : $(TIPOS) $(ESTADOS)
main.o :
