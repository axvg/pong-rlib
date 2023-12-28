CC = g++
CFLAGS = -Iinclude -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
TARGET = main
SRC = src/main.cpp src/Ball.cpp src/Paddle.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)