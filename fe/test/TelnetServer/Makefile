
CXX = g++

# LIB directory
FENGINE_LIB_DIR = ../../src/Lib
BASIC_DIR = $(FENGINE_LIB_DIR)/Basic
NETWORK_DIR = $(FENGINE_LIB_DIR)/Network
THREAD_DIR = $(FENGINE_LIB_DIR)/Thread

TELNET_SERVER_DIR = ./TelnetServer

# libraries
LIBS = -lpthread -ldl -lutil

# flags
CFLAGS = -I$(FENGINE_LIB_DIR) -Xlinker -export-dynamic -g3

libs: $(wildcard *.cpp)
	$(CXX) $(CFLAGS) $(BASIC_DIR)/*.cpp -c;
	$(CXX) $(CFLAGS) $(NETWORK_DIR)/*.cpp -c;
	$(CXX) $(CFLAGS) $(THREAD_DIR)/*.cpp -c;

telnetServer: $(wildcard *.cpp)
	$(CXX) $(CFLAGS) $(TELNET_SERVER_DIR)/*.cpp -c;
	$(CXX) $(CFLAGS) *.o $(LIBS);
	
test: 
	echo $(FENGINE_LIB_DIR)
	echo $(BASIC_DIR)

.PHONY: test
