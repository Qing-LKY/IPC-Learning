OBJ := libmsg.o prework.o interact.o main.o
INCLUDE := $(addprefix ../, $(INCLUDE))
TARGET := ../$(TARGET)
CFLAGS += $(patsubst %, -I%, $(INCLUDE))

all: $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

$(OBJ):%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.phony: clean

clean:
	$(RM) $(OBJ)