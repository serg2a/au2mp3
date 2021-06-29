APP = au2mp3
BINPATH = ~/bin/
CC = gcc
FLAG = -Wall -std=c17

audio2mp3:
	$(CC) $(FLAG) audio2mp3.c -o $(APP)

clean:
	rm $(APP)
	
install: audio2mp3
	cp $(APP) $(BINPATH)

unistall:
	rm $(BINPATH)$(APP)
