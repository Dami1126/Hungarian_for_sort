.SUFFIXES:.c .o

CC=gcc
EXEC=dami
SRCS=main.c\
	 Hungarian.c
			
			

OBJS=$(SRCS:.c=.o)
FLAG1=-o
FLAG2=-c

start: $(OBJS)
	$(CC) $(FLAG1) $(EXEC) $(OBJS) -lm
	@echo "---------ok--------"

.c.o:
	$(CC) $(FLAG1) $@ $(FLAG2) $<

clean:
	rm -rf $(OBJS)
