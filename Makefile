APP = au2mp3
BINPATH = ~/bin/
CC = clang 
FLAG = -Wall -std=c11

audio2mp3: s_audio2mp3.o
	$(CC) $(FLAG) audio2mp3.c s_audio2mp3.o -o $(APP)

s_audio2mp3.o: s_audio2mp3.c
	$(CC) $(FLAG) -c s_audio2mp3.c

clean: $(APP)
	rm $(APP) s_audio2mp3.o
	
install: audio2mp3
	cp $(APP) $(BINPATH)
	rm $(APP)

unistall:
	rm $(BINPATH)$(APP)
