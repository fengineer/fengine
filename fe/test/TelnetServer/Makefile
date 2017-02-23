
CXX = g++

# LIB directory
FENGINE_LIB_DIR = ../../src/Lib
BASIC_DIR = $(FENGINELIBDIR )/Basic
NETWORK_DIR = $(FENGINELIBDIR)/Network
THREAD_DIR = $(FENGINELIBDIR)/Thread

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
	