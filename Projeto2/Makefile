# the compiler: gcc for C program, define as g++ for C++
CC_LINUX = gcc
CC_MAC = cc

# compiler flags:
CFLAGS  = -Wall -pthread
IS_ON_LINUX = -D LINUX_OS
OS := $(shell uname)

# the build target executable:
TARGET = cigarette

all: $(TARGET)

$(TARGET): $(TARGET).c
ifeq ($(OS), Darwin)
		$(CC_MAC) $(CFLAGS) -o $(TARGET) $(TARGET).c
else
		$(CC_LINUX) $(CFLAGS) $(IS_ON_LINUX) -o $(TARGET) $(TARGET).c
endif

.PHONY: clean
clean:
	$(RM) $(TARGET)