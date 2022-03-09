CC 		:= cc
CFLAGS 		:= -Wall -O2 -pedantic

vpath %.h src %.s src

APP		:= au2mp3 
BUILD_DIR 	:= build
SRC_DIR 	:= src
BIN_DIR 	:= ~/bin/
HEADER		:= audio2mp3.h
OBJS 		:= $(patsubst  %.c,%.o,$(wildcard $(SRC_DIR)/*.c))
#-------------------------------------------------------------

$(BUILD_DIR)/$(APP): $(OBJS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJS): $(HEADER)

install: $(BUILD_DIR)/$(APP)
	cp $< $(BIN_DIR)

uninstall: $(BIN_DIR)/$(APP)
	rm -r $<

.PHONY: clean
clean:
	rm -rf $(SRC_DIR)/*.o $(BUILD_DIR)
