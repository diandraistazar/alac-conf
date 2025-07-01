CC := gcc
FLAGS := -Wall --std=c99
SRC 	:= main.c listingThem.c selectingThem.c reload-my-config.c
SRC_O := main.c listingThem.c selectingThem.c reload-my-config.c
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
