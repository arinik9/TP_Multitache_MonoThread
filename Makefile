EXE = Parking
CC = g++
EDL = g++
INC_PATH = -I./ -I/shares/public/tp/tp-multitache/ # chemins des répertoires d'interfaces
LIB_PATH = -L./ -L/shares/public/tp/tp-multitache/ -L/lib64 # chemins des répertoires de bibliothèques
LIBS = -ltp -lncurses -ltcl
EDL_FLAG = $(LIB_PATH) -o $(EXE)
CC_FLAG = $(INC_PATH) -Wall -fexceptions -c -o
MAIN = Mere
INT = Clavier.h Entree.h Configuration.h Sortie.h
REA = $(INT:.h=.cpp)
OBJ = $(INT:.h=.o)
RM = rm
 
.PHONY : clean
 
all : $(EXE)
 
$(EXE) : $(OBJ) $(MAIN).o
	$(EDL) $(EDL_FLAG) $(OBJ) $(MAIN).o $(LIBS)

%.o : %.cpp
	echo $@ par compilation de $<
	$(CC) $(CC_FLAG) $@ $<

clean :
	$(RM) -f $(OBJ) $(MAIN).o core

