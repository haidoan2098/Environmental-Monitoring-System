# Makefile for environmental_monitor_app (C++ version, Yocto-ready)

# -----------------------------
# Compiler & flags (override by Yocto)
# -----------------------------
CXX ?= arm-poky-linux-gnueabi-g++
CXXFLAGS ?= -Wall -Wextra -std=c++11
CXXFLAGS += -Iinc
LDFLAGS ?=

# Sysroot for Yocto toolchain (set by environment if needed)
SYSROOT ?= $(shell $(CXX) --print-sysroot)
CXXFLAGS += --sysroot=$(SYSROOT)
LDFLAGS += --sysroot=$(SYSROOT)

# -----------------------------
# Directories
# -----------------------------
SRCDIR := src
INCDIR := inc
OBJDIR := build

# -----------------------------
# Files
# -----------------------------
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
TARGET := env_monitor_app

# -----------------------------
# Default target
# -----------------------------
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

# Compile
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build dir if missing
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Phony targets
.PHONY: all clean
