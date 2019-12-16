# Makefile for Week 05 lecture exercises

#CC=dcc
CC=gcc
CFLAGS=-Wall -Werror
BINS=fail fail2 cat1 cat2 cat3 cat4 stat sadd1 sadd2 slist1 slist2

all: $(BINS)

open : open.c
open1 : open1.c
open2 : open2.c
copies : copies.c
fail : fail.c
fail2 : fail2.c
fail3 : fail3.c
cat1 : cat1.c
cat2 : cat2.c
cat3 : cat3.c
cat4 : cat4.c
stat : stat.c
sadd1 : sadd1.o Student.o
sadd1.o : sadd1.c Student.h
slist1 : slist1.o Student.o
slist1.o : slist1.c Student.h
sadd2 : sadd2.o Student.o
sadd2.o : sadd2.c Student.h
slist2 : slist2.o Student.o
slist2.o : slist2.c Student.h
Student.o : Student.c Student.h

clean :
	rm -f $(BINS) a.out
