CC=g++

ifeq ($(OS),Windows_NT)
INC=-I ../include
LIB=-L ../libs 
LIBS=-lglew32s -lglew32mxs -lglfw3 -lopengl32 -lgdi32 -lglu32
else
INC=/usr/local/include
LIB=-L /usr/local/lib -L /usr/lib/x86_64-linux-gnu -L/usr/lib64
LIBS=-lGLEW -lglfw3 -lX11 -lXxf86vm -lpthread -lGL -lXrandr -lXi 
endif

all:
	$(CC) main.cpp $(LIB) $(LIBS) $(INC)  -o hello


