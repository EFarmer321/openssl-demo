COMPILER = /mingw64/bin/g++
COMPILER_FLAGS = -Wall -I./openssl/include
LIBRARY_FLAGS = -L./openssl -lssl -lcrypto -lws2_32 -lcrypt32 -ladvapi32
LIB_FILES = utils.cpp

server:
	$(COMPILER) $(COMPILER_FLAGS) $(LIB_FILES) server.cpp -o server.exe $(LIBRARY_FLAGS)

client:
	$(COMPILER) $(COMPILER_FLAGS) $(LIB_FILES) client.cpp -o client.exe $(LIBRARY_FLAGS)
