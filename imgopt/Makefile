#
# Copyright 2011 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# Author: jmarantz@google.com (Joshua Marantz)

# This Makefile provides a mechanism to generate a Page Speed Automatic
# library (.a) from an already-built mod_pagespeed distribution.  This

# MOD_PAGESPEED_ROOT should be set to the 'src' directory where mod_pagespeed
# was built.  See:
# https://modpagespeed.com/doc/build_from_source
#
# When running this Makefile from the 'automatic' directory then it will
# be set automatically.
MOD_PAGESPEED_ROOT = $(shell cd ..; pwd)

# OUTPUT_ROOT should be set to wherever you want to put output files.  Default
# is to put them in the current directory.
OUTPUT_DIR = $(PWD)

# You can use a Debug or a Release build.  Default is Release.  Feel free
# to set this to Debug to get visibility into Page Speed Automatic code.
#
# Note that this is the same Makefile variable used by the generated Makefiles
# on Linux.
BUILDTYPE = Release

# The 'gclient' build flow uses 'xcodebuild' on Mac and 'make' on Linux.
# To make matters worse, it puts all the intermediate libraries in the same
# directory on Mac but distributes them over a directory tree on Linux.


# TODO(jmarantz): test this on 32-bit systems.  Add fail handler for non-linux
# non-mac.
ifeq ($(HOSTTYPE),x86_64-linux)
 INCLUDE_ARCH = arch/linux/x64
else
 INCLUDE_ARCH = arch/linux/ia32
endif
INCLUDE_ARCH = arch/linux/x64
SYSLIBS = -lpthread -lrt #-luuid
TESTBENCH_LIB = $(MOD_PAGESPEED_ROOT)/out/$(BUILDTYPE)/obj.target/third_party/re2/libre2_bench_util.a

BASE_LIBS = \
    pagespeed/libpagespeed_image_optimizer_pb.a \
    third_party/protobuf/libprotobuf_full_do_not_use.a 

INCLUDE_PATH = \
    -I$(MOD_PAGESPEED_ROOT) \
    -I$(MOD_PAGESPEED_ROOT)/out/$(BUILDTYPE)/obj/gen/protoc_out/instaweb \
    -I$(MOD_PAGESPEED_ROOT)/third_party/chromium/src \
    -I$(MOD_PAGESPEED_ROOT)/third_party/gflags/arch/gen/$(INCLUDE_ARCH)/include \
    -I$(MOD_PAGESPEED_ROOT)/third_party/google-sparsehash/src/src \
    -I$(MOD_PAGESPEED_ROOT)/third_party/google-sparsehash/gen/$(INCLUDE_ARCH)/include \
    -I$(MOD_PAGESPEED_ROOT)/third_party/protobuf/src/src \
    -I$(MOD_PAGESPEED_ROOT)/third_party/re2/src \
    -I$(MOD_PAGESPEED_ROOT)/third_party/libpng/src \
    -I$(MOD_PAGESPEED_ROOT)/url/

LIBS = $(addprefix $(MOD_PAGESPEED_ROOT)/out/$(BUILDTYPE)/obj.target/, $(BASE_LIBS))

PSOL = $(MOD_PAGESPEED_ROOT)/pagespeed/automatic/pagespeed_automatic.a

OBJS = $(OUTPUT_DIR)/imgopt.o \
       $(PSOL)

EXE  = $(OUTPUT_DIR)/imgopt

MAKE := $(MAKE) --no-print-directory
exe : $(EXE)

# Specifying 'build_libraries' as a dependency but recursively making
# 'static_rewriter' allows 'make -j' to work.  This is needed because
# we don't articulate all the dependencies required to build the libraries.
all : $(EXE)

# Flags used to compile static_rewriter.cc.  Note that these are not
# the flags used to compile pagespeed_automatic, which is compiled
# with either BUILDTYPE=Release or BUILDTYPE=Debug
#
# These are the same flags as we set in common.gypi, but this Makefile doesn't
# know about gyp.
override CXXFLAGS := $(CXXFLAGS) -std=gnu++0x -D_GLIBCXX_USE_CXX11_ABI=0 -static-libstdc++

# Ideally we want the main .o files to depend on all the headers in PSOL,
# but that's not easy to keep up-to-date.  As a proxy for those, recompile
# .o files whenever the library changes.  This is a little conservative
# because the library might change without any header changes, but recompiling
# the .o files is cheap.
$(OUTPUT_DIR)/%.o : %.cc
	$(CXX) $(INCLUDE_PATH) $(CXXFLAGS) $(MOD_PAGESPEED_INCLUDE) -c $< -o $@

$(EXE) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS) $(SYSLIBS)

clean :
	rm -f $(EXE) *.o
