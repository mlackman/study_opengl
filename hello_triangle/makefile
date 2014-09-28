CC=g++
INC=-I ../utils
LIB=-L /usr/local/lib -L /usr/lib/x86_64-linux-gnu -L/usr/lib64
LIBS=-lGLEW -lglfw3 -lX11 -lXxf86vm -lpthread -lGL -lXrandr -lXi 

all:
	$(CC) -std=c++11 main.cpp ../utils/openglapp.cpp $(LIB) $(LIBS) $(INC) -o hello


