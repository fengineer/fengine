
CXX = g++

# 工程名字
PROJECT_NAME = TestServer

# 工程类型
PROJECT_TYPE = exe

# 源代码目录
SRC_DIR = ./TelnetServer
# LIB src directory
FENGINE_LIB_DIR = ../../src/Lib
BASIC_DIR = $(FENGINE_LIB_DIR)/Basic
NETWORK_DIR = $(FENGINE_LIB_DIR)/Network
THREAD_DIR = $(FENGINE_LIB_DIR)/Thread

# 头文件包含目录
INCLUDE_DIR += -I$(SRC_DIR)
INCLUDE_DIR += -I$(BASIC_DIR) -I$(NETWORK_DIR) -I$(THREAD_DIR)

# 共享库链接目录
LIB_DIR = -L$(TARGET_DIR)
# libraries
LIBS = -lpthread -ldl -lutil

# 临时目录
TEMP_DIR = ../Build/Temp/$(PROJECT_NAME)

# 目标目录
TARGET_DIR = ../bin/linux
TARGET = $(PROJECT_NAME)
TARGET_PATH = $(TARGET_DIR)/$(TARGET)

# flags
CFLAGS = -Xlinker -export-dynamic -g3
CFLAGS += $(INCLUDE_DIR)
CFLAGS += $(LIB_DIR)
CFLAGS += $(LIBS)

# --------------------------------------------------
all: pre_build libs testServer

libs: $(wildcard *.cpp)
	$(CXX) $(CFLAGS) $(BASIC_DIR)/*.cpp $(TEMP_DIR) -c;
	$(CXX) $(CFLAGS) $(NETWORK_DIR)/*.cpp $(TEMP_DIR) -c;
	$(CXX) $(CFLAGS) $(THREAD_DIR)/*.cpp $(TEMP_DIR) -c;

$(TARGET_PATH): $(wildcard *.cpp)
	$(CXX) $(CFLAGS) $(TELNET_SERVER_SRC)/*.cpp $(TEMP_DIR) -c;
	$(CXX) $(CFLAGS) *.o $(LIBS) -o $(TARGET_DIR) $@;
	
telnetServer: $(TARGET_PATH)

pre_build:
	mkdir -p $(TEMP_DIR)
	mkdir -p $(TARGET_DIR)

clean:
	rm -rf $(TEMP_DIR)

test: 
	@echo $(FENGINE_LIB_DIR)
	@echo $(BASIC_DIR)

.PHONY: all pre_build libs telnetServer clean test
