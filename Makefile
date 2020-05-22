#
# Les variables d'environnement libG2X, incG2X
# sont definies dans le fichier ~/.bashrc par le script ../install.sh
#
#compilateur
CC = gcc
#compil en mode 'debug' ou optmisée (-O2)
DBG = yes

ifeq ($(DBG),yes) #en mode debug
  CFLAGS = -g -Wpointer-arith -Wall -ansi
else              #en mode normal
  CFLAGS = -O2 -ansi
endif

# assemblage des infos de lib. et inc.
lib =   $(libG3X)
# fichiers *.c locaux
src = src/
# fichiers *.h locaux et lib.
inc = -I./include $(incG3X) 

# règle de compilation générique des objets
%.o : $(src)%.c
	@echo "module $@"
	@$(CC) $(CFLAGS) $(inc) -c $< -o $@
	
# règle de compilation générique
% : %.o 
	@echo "edition de lien $^ -> $@"
	@$(CC) $^ $(lib) -o $@
	
# SimpleOsc : PMat.o Link.o SimpleOsc.o	
# 	@echo "edition de lien $^ -> $@"
# 	@$(CC) $^ $(lib) -o $@

# Corde1 : PMat.o Link.o Corde1.o	
# 	@echo "edition de lien $^ -> $@"
# 	@$(CC) $^ $(lib) -o $@

# Corde2 : PMat.o Link.o Corde2.o	
# 	@echo "edition de lien $^ -> $@"
# 	@$(CC) $^ $(lib) -o $@

Projet : PMat.o Link.o Projet.o	
	@echo "edition de lien $^ -> $@"
	@$(CC) $^ $(lib) -o $@

.PHONY : clean cleanall

clean : 
	rm -f *.o .tmp*
cleanall : 
	rm -f *.o .tmp* $(EXEC)
