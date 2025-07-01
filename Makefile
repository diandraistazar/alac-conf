CC := gcc
FLAGS := -Wall --std=c99
SRC 	:= main listingThem selectingThem reload-my-config
OUT := alacrittyTheme

all:
	${CC} ${FLAGS} -c ${SRC}.c
	${CC} ${SRC}.o -o ${OUT}	

install:
	${CC} ${FLAGS} -c ${SRC}.c
	${CC} ${SRC}.o -o ${OUT}	
	cp ${OUT} /usr/bin

uninstall:
	rm ${OUT}
	rm /usr/bin/${OUT}
