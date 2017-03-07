
CXX = g++

# LIB directory
FENGINE_LIB_DIR = ./Lib
BASIC_DIR = $(FENGINELIBDIR )/Basic
NETWORK_DIR = $(FENGINELIBDIR)/Network
THREAD_DIR = $(FENGINELIBDIR)/Network

# test directory
TEST_DIR = ../test
BASIC_LIB_TEST_DIR = $(TESTDIR)/BasicLibTest
TELNET_SERVER_DIR = $(TESTDIR)/TelnetServer

# libraries
LIBS = -lpthread -ldl -lutil

# flags
CFLAGS = -I$(FENGINE_LIB_DIR) -Xlinker -export-dynamic -g3

libs: $(wildcard *.cpp)
	$(CXX) $(CFLAGS) $(BASIC_DIR)/*.cpp -c;
	$(CXX) $(CFLAGS) $(NETWORK_DIR)/*.cpp -c;
	$(CXX) $(CFLAGS) $(THREAD_DIR)/*.cpp -c;

basicLibTest: $(wildcard *.cpp)
	$(CXX) $(CFLAGS) $(BASIC_LIB_TEST_DIR)/*.cpp -c;
	$(CXX) $(CFLAGS) *.o $(LIBS);

telnetServer: $(wildcard *.cpp)
	$(CXX) $(CFLAGS) $(TELNET_SERVER_DIR)/*.cpp -c;
	$(CXX) $(CFLAGS) *.o $(LIBS);
	