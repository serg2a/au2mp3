APP = au2mp3
BINPATH = ~/bin/
CC = clang 
FLAG = -Wall -std=c11
TEST = test

audio2mp3: s_audio2mp3.o audio2mp3.o
	$(CC) $(FLAG) audio2mp3.o s_audio2mp3.o -o $(APP)

audio2mp3.o: audio2mp3.c
	$(CC) $(FLAG) -c audio2mp3.c

s_audio2mp3.o: s_audio2mp3.c
	$(CC) $(FLAG) -c s_audio2mp3.c

clean:
	rm $(APP) s_audio2mp3.o test.o audio2mp3.o $(TEST)
	
install: audio2mp3
	cp $(APP) $(BINPATH)
	rm $(APP)

test: s_audio2mp3.o test.o
	$(CC) $(FLAG) s_audio2mp3.o test.o -o $(TEST)

test.o: test.c
	$(CC) $(FLAG) -c test.c

unistall:
	rm $(BINPATH)$(APP)
