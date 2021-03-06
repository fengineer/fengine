# Utilities.
GXX = gcc
MKDIR = mkdir -p
AR = ar rc
RANLIB = ranlib
RM =  rm -rf

# How to install. If your install program does not support "-p", then you
# may have to run ranlib on the installed libtinyxml.a (do "make ranlib").
INSTALL= install -p
INSTALL_DATA= $(INSTALL) -m 0644


# Path
PROJECT_NAME = libcommon
TEMP_PATH = ./temp/$(PROJECT_NAME)

TARGET_DIR = ../lib_bin/linux
TARGET = $(PROJECT_NAME).a
TARGET_PATH = $(TARGET_DIR)/$(TARGET)

COMMON_DIR = ../Lib/Common
NETWORK_DIR = ../Lib/NetWork
THREAD_DIR = ../Lib/Thread


# 定义编译选项变量
INCLUDE_OP = -I$(COMMON_DIR) -I$(NETWORK_DIR) -I$(THREAD_DIR)
_C_OP = -c
_C_OP += -g3
_C_OP += -Wall 
_C_OP += -pthread
_C_OP += $(INCLUDE_OP)

$(TEMP_PATH)/%.o: $(COMMON_DIR)/%.cpp
	$(GXX) $< $(_C_OP) -o $@ 
$(TEMP_PATH)/%.o: $(NETWORK_DIR)/%.cpp
	$(GXX) $< $(_C_OP) -o $@ 
$(TEMP_PATH)/%.o: $(THREAD_DIR)/%.cpp
	$(GXX) $< $(_C_OP) -o $@ 

OBJS = $(patsubst $(COMMON_DIR)/%.cpp, $(TEMP_PATH)/%.o, $(wildcard $(COMMON_DIR)/*.cpp))
OBJS += $(patsubst $(NETWORK_DIR)/%.cpp, $(TEMP_PATH)/%.o, $(wildcard $(NETWORK_DIR)/*.cpp))
OBJS += $(patsubst $(THREAD_DIR)/%.cpp, $(TEMP_PATH)/%.o, $(wildcard $(THREAD_DIR)/*.cpp))

# first target
all: pre_build target

$(TARGET_PATH): $(OBJS)
	$(AR) $@ $(OBJS)
	$(RANLIB) $@

pre_build:
	$(MKDIR) $(TEMP_PATH) $(TARGET_DIR)

target: $(TARGET_PATH)
	
clean:
	$(RM) $(TEMP_PATH)	

test:
	@echo $(OBJS)
	@echo $(wildcard $(COMMON_DIR)/*.cpp) 

.PHONY: pre_build target all



