CC := gcc
FLAGS := -Wall --std=c99 -g
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
