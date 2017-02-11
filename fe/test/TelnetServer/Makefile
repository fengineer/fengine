
CXX = g++

# 工程名字
PROJECT_NAME = TestServer

# 工程类型
PROJECT_TYPE = exe

# 源代码目录
SRC_DIR = .
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
CFLAGS = -g3 -Wall
CFLAGS += $(INCLUDE_DIR)
CFLAGS += $(LIB_DIR)
CFLAGS += $(LIBS)

OBJS = $(patsubst $(BASIC_DIR)/%.cpp, $(TEMP_DIR)/%.o, $(wildcard $(BASIC_DIR)/*.cpp))
OBJS += $(patsubst $(NETWORK_DIR)/%.cpp, $(TEMP_DIR)/%.o, $(wildcard $(NETWORK_DIR)/*.cpp))
OBJS += $(patsubst $(THREAD_DIR)/%.cpp, $(TEMP_DIR)/%.o, $(wildcard $(THREAD_DIR)/*.cpp))
OBJS += $(patsubst $(SRC_DIR)/%.cpp, $(TEMP_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cpp))

# 编译所有源文件
$(TEMP_DIR)/%.o : $(BASIC_DIR)/%.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

$(TEMP_DIR)/%.o : $(NETWORK_DIR)/%.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

$(TEMP_DIR)/%.o : $(THREAD_DIR)/%.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

$(TEMP_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

# --------------------------------------------------
all: pre_build telnetServer

$(TARGET_PATH): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(CFLAGS) 
	
telnetServer: $(TARGET_PATH)

pre_build:
	mkdir -p $(TEMP_DIR)
	mkdir -p $(TARGET_DIR)

clean:
	rm -rf $(TEMP_DIR)

test: 
	@echo $(FENGINE_LIB_DIR)
	@echo $(BASIC_DIR)
	@echo $(TEMP_DIR)
	@echo $(TARGET_DIR)
	@echo $(OBJS)

.PHONY: all pre_build libs telnetServer clean test
