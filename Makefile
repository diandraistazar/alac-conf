CC := gcc
FLAGS := -Wall --std=c99
SRC 	:= main.c listThem.c selectThem.c reloadThem.c
SRC_O := main.c listThem.c selectThem.c reloadThem.c
OUT := alac-conf 

all:
	${CC} ${FLAGS} -c ${SRC}
	${CC} ${SRC_O} -o ${OUT}	

install:
	${CC} ${FLAGS} -c ${SRC}
	${CC} ${SRC_O} -o ${OUT}	
	cp ${OUT} /usr/bin

uninstall:
	rm ${OUT}
	rm *.o
	rm /usr/bin/${OUT}
