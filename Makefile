APP = au2mp3
BINPATH = ~/bin/
CC = clang 
FLAG = -Wall -std=c11 -I include
TEST = test_au2mp3
SRC = src/

audio2mp3: s_audio2mp3.o audio2mp3.o util.o setlist.o
	$(CC) $(FLAG) audio2mp3.o s_audio2mp3.o util.o setlist.o -o $(APP)

audio2mp3.o: src/audio2mp3.c
	$(CC) $(FLAG) -c $(SRC)audio2mp3.c

s_audio2mp3.o: src/s_audio2mp3.c
	$(CC) $(FLAG) -c $(SRC)s_audio2mp3.c

util.o: src/util.c
	$(CC) $(FLAG) -c $(SRC)util.c

setlist.o: src/setlist.c
	$(CC) $(FLAG) -c $(SRC)setlist.c

clean:
	rm $(APP) s_audio2mp3.o test.o audio2mp3.o util.o setlist.o $(TEST)
	
install: audio2mp3
	cp $(APP) $(BINPATH)
	rm $(APP)

test: s_audio2mp3.o test.o
	$(CC) $(FLAG) s_audio2mp3.o test.o -o $(TEST)

test.o: test/test.c
	$(CC) $(FLAG) -c test/test.c

unistall:
	rm $(BINPATH)$(APP)
