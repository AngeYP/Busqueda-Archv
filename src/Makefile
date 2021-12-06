TARGET  = $(BIN_DIR)/main
OBJ_DIR = ../obj
BIN_DIR = ../bin
INC_DIR = ../inc
OBJS     = $(OBJ_DIR)/menu.o \
	   $(OBJ_DIR)/client.o \
	   $(OBJ_DIR)/server.o \
	   $(OBJ_DIR)/tclient.o \
	   $(OBJ_DIR)/fserver.o \
	   $(OBJ_DIR)/tserver.o

CFLAGS = -I$(INC_DIR)
$(TARGET) : $(OBJS)
	mkdir -p $(BIN_DIR)
	gcc -g -pthread $(CFLAGS) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/%.o : %.c
	mkdir -p $(OBJ_DIR)
	gcc -c -MD $(CFLAGS) $< -o $@

-include $(OBJ_DIR)/*.d

.PHONY : clean
clean:
	@rm -r $(OBJ_DIR) $(BIN_DIR)
