
CXX = g++

# LIB directory
FENGINELIBDIR = ./LIB
BASICDIR = $(FENGINELIBDIR )/Basic
NETWORKDIR = $(FENGINELIBDIR )/Network

# test directory
TESTDIR = ../test
BASICLIBTESTDIR = $(TESTDIR )/BasicLibTest

# libraries
LIBS = -lpthread -ldl -lutil

# flags
CFLAGS = -I$(FENGINELIBDIR ) -Xlinker -export-dynamic -g3

libs: $(wildcard *.cpp)
	$(CXX) $(CFLAGS) $(BASICDIR)/*.cpp -c;
	$(CXX) $(CFLAGS) $(NETWORKDIR)/*.cpp -c;

basicLibTest: $(wildcard *.cpp)
	$(CXX) $(CFLAGS) $(BASICLIBTESTDIR)/*.cpp -c;
	$(CXX) $(CFLAGS) *.o $(LIBS);

