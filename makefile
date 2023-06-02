# Les librairies que l'on va utiliser
LIBS= -lm

# Les endroits où on peut trouver des librairies
LIBS_PATH= \
	-L/lib \
	-L/usr/lib \
	-L/usr/local/lib

# Le compilateur que nous utiliserons
COMPILO=g++

# Les options de compilation des sources
#    -c    : Ne fait pas un exécutable, mais seulement un .o
#    -g    : Fait un objet débuggable
#    -Wall : Affiche un maximum de warnings si le code C++ est douteux
#    -ansi : Assure que le code C++ suit la norme ANSI, et est donc portable.
FLAGS= -c -g -Wall -ansi

# Liste des objets que l'on va obtenir, et qu'il faudra linker.
OBJ= main.o \
	functions.o \
	mission.o \
	centre.o \
	employe.o \
	instances/data.o \
	part1/group.o \
	part1/group_maker.o \
	genetique/ag.o \
	genetique/population.o \
	genetique/chromosome.o  \


# Cibles Principales #
algo_sessad : $(OBJ) 
	$(COMPILO) -o algo_sessad $(OBJ) $(LIBS_PATH) $(LIBS)


# Compilation des sources #
%.o : %.cc
	$(COMPILO)$(FLAGS) -o $< $@ 


