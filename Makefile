#311318075
#shanibasteker@gmail.com

TARGET = monopoly
SOURCES = main.cpp

# SFML library 
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

$(TARGET):
	g++ -o $(TARGET) $(SOURCES) $(LIBS)

clean:
	rm -f $(TARGET)
