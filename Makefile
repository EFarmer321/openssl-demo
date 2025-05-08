COMPILER_FLAGS = -Wall -I/mingw64/include -DWIN32_LEAN_AND_MEAN -DNOMINMAX -std=c++20
LIBRARY_FLAGS = -L/mingw64/lib -lssl -lcrypto -lws2_32 -lcrypt32 -ladvapi32
LIB_FILES = utils.cpp

server:
	g++ $(COMPILER_FLAGS) $(LIB_FILES) server.cpp -o run_server.exe $(LIBRARY_FLAGS)

client:
	g++ $(COMPILER_FLAGS) $(LIB_FILES) client.cpp -o run_client.exe $(LIBRARY_FLAGS)

all: server client