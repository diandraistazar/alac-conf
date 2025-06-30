CC := gcc
FLAGS := -Wall --std=c99
#SRC 	:= main.c listingThem.c selectingThem.c
#SRC_O := main.o listingThem.o selectingThem.o
SRC := main.c
SRC_O := main.o
OUT := alacrittyTheme

all:
	${CC} ${FLAGS} -c ${SRC}
	${CC} ${SRC_O} -o ${OUT}	

install:
	${CC} ${FLAGS} -c ${SRC}
	${CC} ${SRC_O} -o ${OUT}	
	cp ${OUT} /usr/bin

uninstall:
	rm ${OUT}
	rm /usr/bin/${OUT}
