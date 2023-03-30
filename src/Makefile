OBJ := libmsg.o prework.o interact.o main.o
INCLUDE := $(addprefix ../, $(INCLUDE))
TARGET := ../$(TARGET)
TARGET_STATIC := ../$(TARGET_STATIC)
CFLAGS += $(patsubst %, -I%, $(INCLUDE))

all: $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

$(OBJ):%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.phony: clean static

static: $(OBJ)
	$(CC) $(OBJ) -o $(TARGET_STATIC) $(LDFLAGS_STATIC)

clean:
	$(RM) $(OBJ)