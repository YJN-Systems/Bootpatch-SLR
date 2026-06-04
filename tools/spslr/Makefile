# SPDX-License-Identifier: GPL-2.0

CC ?= gcc

# If CXX was not passed, derive it from CC.
ifeq ($(origin CXX),default)
override CXX := $(subst gcc,g++,$(CC))
endif

OUTPUT ?= .

PINPOINT := $(OUTPUT)/pinpoint.so
PATCHCOMPILE := $(OUTPUT)/patchcompile

GCC_PLUGIN_DIR := $(shell $(CXX) -print-file-name=plugin)

COMMON_CXXFLAGS := -std=c++20

PINPOINT_CXXFLAGS := \
	$(COMMON_CXXFLAGS) \
	-fPIC -fno-rtti -fno-exceptions \
	-D_GNU_SOURCE \
	-Isrc/pinpoint \
	-Isrc/pinpoint/safegcc \
	-Isrc/pinpoint/stage0 \
	-Isrc/pinpoint/stage1 \
	-Isrc/pinpoint/stage2 \
	-Isrc/pinpoint/final \
	-I$(GCC_PLUGIN_DIR)/include

PATCHCOMPILE_CXXFLAGS := \
	$(COMMON_CXXFLAGS) \
	-Isrc/patchcompile

PINPOINT_SRCS := \
	src/pinpoint/pinpoint.cpp \
	src/pinpoint/stage0/on_register_attributes.cpp \
	src/pinpoint/stage0/on_finish_type.cpp \
	src/pinpoint/stage0/on_preserve_component_ref.cpp \
	src/pinpoint/stage0/on_finish_decl.cpp \
	src/pinpoint/stage0/on_start_unit.cpp \
	src/pinpoint/stage0/target.cpp \
	src/pinpoint/stage0/separator.cpp \
	src/pinpoint/stage0/separate_offset_pass.cpp \
	src/pinpoint/stage1/asm_offset_pass.cpp \
	src/pinpoint/stage2/rtl_pin_lower_pass.cpp \
	src/pinpoint/final/on_finish_unit.cpp

PATCHCOMPILE_SRCS := \
	src/patchcompile/patchcompile.cpp \
	src/patchcompile/accumulation.cpp \
	src/patchcompile/emit.cpp

PINPOINT_OBJS := $(PINPOINT_SRCS:.cpp=.o)
PATCHCOMPILE_OBJS := $(PATCHCOMPILE_SRCS:.cpp=.o)

.PHONY: all clean
all: $(PINPOINT) $(PATCHCOMPILE)

$(PINPOINT): $(PINPOINT_OBJS)
	$(CXX) -shared -o $@ $^

$(PATCHCOMPILE): $(PATCHCOMPILE_OBJS)
	$(CXX) -o $@ $^

src/pinpoint/%.o: src/pinpoint/%.cpp
	$(CXX) $(PINPOINT_CXXFLAGS) -c -o $@ $<

src/patchcompile/%.o: src/patchcompile/%.cpp
	$(CXX) $(PATCHCOMPILE_CXXFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	@echo '  CLEAN   tools/spslr'
	@rm -f ./pinpoint.so ./patchcompile \
		$(PINPOINT_OBJS) \
		$(PATCHCOMPILE_OBJS)
