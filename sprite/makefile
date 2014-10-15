CC=g++
ifeq ($(OS),Windows_NT)
CPPFLAGS=-DGLEW_STATIC
LIB_INC_PATH=../include
LIB=-L ../libs 
LIBS=-lglew32s -lglew32mxs -lglfw3 -lgdi32 -lglu32 -lSOIL -lopengl32
else
LIB=-L /usr/local/lib -L /usr/lib/x86_64-linux-gnu -L/usr/lib64
LIBS=-lGLEW -lglfw3 -lX11 -lXxf86vm -lpthread -lGL -lXrandr -lXi -lSOIL
endif

INC=-I$(LIB_INC_PATH) -I ../utils

all:
	$(CC) -std=c++11 main.cpp ../utils/openglapp.cpp $(CPPFLAGS) $(LIB) $(LIBS) $(INC) -o sprite


