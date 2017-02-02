LIB = ./lib
LINKS = -lfmod -lfmodstudio -lsfml-graphics -lsfml-window -lsfml-system
INC = -I./include/FMOD -I./include

all:
	clang++ main.cpp oneshot.cpp -o sc ${INC}  -L ${LIB} ${LINKS} -rpath ${LIB} -std=c++11
