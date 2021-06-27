APP = au2mp3
BINPATH = ~/bin/

audio2mp3:
	gcc -Wall audio2mp3.c -o $(APP)

clean:
	rm $(APP)
	
install: audio2mp3
	cp $(APP) $(BINPATH)

unistall:
	rm $(BINPATH)$(APP)
