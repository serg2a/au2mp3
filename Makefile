CC 		:= gcc 
CFLAGS 		:= -Wall -O2 
APP		:= au2mp3 
BUILD_DIR 	:= build
SRC_DIR 	:= src
BIN_DIR 	:= ~/bin/
OBJS 		:= $(patsubst  %.c,%.o,$(wildcard $(SRC_DIR)/*.c))
#-------------------------------------------------------------

$(BUILD_DIR)/$(APP): $(OBJS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

install: $(BUILD_DIR)/$(APP)
	cp $< $(BIN_DIR)

uninstall: $(BIN_DIR)/$(APP)
	rm -r $<

.PHONY: clean
clean:
	rm -rf $(SRC_DIR)/*.o $(BUILD_DIR)
