# Makefile for gerador and sauna #

CC = gcc

PROG = gerador

src: gerador.c sauna.c
	cc -Wall gerador.c -o gerador -lpthread
	cc -Wall sauna.c -o sauna -lpthread
clean:
	rm -f gerador
	rm -f sauna

CFLAGS = -Wall

