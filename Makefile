CC=gcc

INCLUDES=-Iinclude
LIBS=-lm -lSDL2 -lSDL2_ttf

SRCS=main.c text.c util.c window.c matrix.c nn.c
OBJS=$(SRCS:.c=.o)

TARGET=predictor

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(INCLUDES) -c $< -o $@

clean:
	$(RM) *.o $(TARGET)
