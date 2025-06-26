CC := gcc
FLAGS := -Wall --std=c99 
SRC := main.c
OUT := alacrittyTheme

all:
	${CC} ${FLAGS} ${SRC} -o ${OUT}

install:
	${CC} ${FLAGS} ${SRC} -o ${OUT}
	cp ${OUT} /usr/bin

uninstall:
	rm ${OUT}
	rm /usr/bin/${OUT}
