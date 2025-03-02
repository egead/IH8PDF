CC = gcc
CFLAGS = -Wall
TARGET= ih8pdf
PREFIX= /usr/local

all:$(TARGET)

$(TARGET): ih8pdf.C
	$(CC) $(CFLAGS) ih8pdf.C -o $(TARGET)

install: $(TARGET)
	sudo cp $(TARGET) $(PREFIX)/bin/$(TARGET)

uninstall:
	sudo rm -f $(PREFIX)/bin/$(TARGET)

clean: 
	rm -f $(TARGET)