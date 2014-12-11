############################################################################
# apps/examples/hello/Makefile
#
#   Copyright (C) 2008, 2010-2013 Gregory Nutt. All rights reserved.
#   Author: Gregory Nutt <gnutt@nuttx.org>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
# 3. Neither the name NuttX nor the names of its contributors may be
#    used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
############################################################################

-include $(TOPDIR)/.config
-include $(TOPDIR)/Make.defs
include $(APPDIR)/Make.defs

# Application info

# APP_INFO takes the following form
# APP1NAME = <APP_NAME>
# PRIORITY = SCHED_PRIORITY_DEFAULT
# STACKSIZE = 2048
<APP_INFO>

# These are all the source files that are required by the project that aren't the executable files
ASRCS = <ASSEMBLY_SOURCE_FILES> 
CSRCS = <C_SOURCE_FILES>

# APP_SOURCE is takes the following form:
# APP1SRC = app1.c
# APP2SRC = app2.c
<APP_SOURCE>

# MAIN_SRC is takes the following form:
# MAINSRC = $(APP1SRC) $(APP2SRC)
MAINSRC = <MAIN_SOURCE>

# The following two lines do not change.
AOBJS = $(ASRCS:.S=$(OBJEXT))
COBJS = $(CSRCS:.c=$(OBJEXT))


# APP_OBJS takes the following form:
# APP1OBJS = $(APP1SRC:.c=$(OBJEXT))
# APP2OBJS = $(APP2SRC:.c=$(OBJEXT))
<APP_OBJS>

# The following line does not change.
MAINOBJ = $(MAINSRC:.c=$(OBJEXT))

SRCS = $(ASRCS) $(CSRCS) $(MAINSRC)
OBJS = $(AOBJS) $(COBJS)

ifneq ($(CONFIG_BUILD_KERNEL),y)
  OBJS += $(MAINOBJ)
endif

ifeq ($(CONFIG_WINDOWS_NATIVE),y)
  BIN = ..\..\libapps$(LIBEXT)
else
ifeq ($(WINTOOL),y)
  BIN = ..\\..\\libapps$(LIBEXT)
else
  BIN = ../../libapps$(LIBEXT)
endif
endif

ifeq ($(WINTOOL),y)
  INSTALL_DIR = "${shell cygpath -w $(BIN_DIR)}"
else
  INSTALL_DIR = $(BIN_DIR)
endif

# APP_CONFIG_APPNAME takes the following form:
# APP_CONFIG_APP1 ?= APP1$(EXEEXT)
# APP1 = $(APP_CONFIG_APP1)
<APP_CONFIG_APPNAME>

ROOTDEPPATH = --dep-path .

# Common build

VPATH =

all: .built
.PHONY: clean depend distclean

$(AOBJS): %$(OBJEXT): %.S
	$(call ASSEMBLE, $<, $@)

$(COBJS) $(MAINOBJ): %$(OBJEXT): %.c
	$(call COMPILE, $<, $@)

.built: $(OBJS)
	$(call ARCHIVE, $(BIN), $(OBJS))
	@touch .built

ifeq ($(CONFIG_BUILD_KERNEL),y)
# APP_INSTALL takes the following form:
# $(BIN_DIR)$(DELIM)$(APP1): $(OBJS) $(APP1OBJ)
#	@echo "LD: $(APP1)"
#	$(Q) $(LD) $(LDELFFLAGS) $(LDLIBPATH) -o $(INSTALL_DIR)$(DELIM)$(APP1) $(ARCHCRT0OBJ) $(MAINOBJ) $(LDLIBS)
#	$(Q) $(NM) -u  $(INSTALL_DIR)$(DELIM)$(APP1)
#
#	install: $(BIN_DIR)$(DELIM)$(APP1) $(BIN_DIR)$(DELIM)$(APP2)
<APP_INSTALL_PART1>

install: <APP_INSTALL_PART2>

else
install:

endif

ifeq ($(CONFIG_NSH_BUILTIN_APPS),y)
# APP_CONTEXT takes the following form:
# $(BUILTIN_REGISTRY)$(DELIM)$(APP1)_main.bdat: $(DEPCONFIG) Makefile
#	$(call REGISTER,$(APP1),$(PRIORITY),$(STACKSIZE),$(APP1)_main)
# $(BUILTIN_REGISTRY)$(DELIM)$(APP2)_main.bdat: $(DEPCONFIG) Makefile
#	$(call REGISTER,$(APP2),$(PRIORITY),$(STACKSIZE),$(APP2)_main)
#
# context: $(BUILTIN_REGISTRY)$(DELIM)$(APP1NAME)_main.bdat $(BUILTIN_REGISTRY)$(DELIM)$(APP1NAME)_main.bdat
<APP_CONTEXT_PART1>

context: <APP_CONTEXT_PART2>
else
context:
endif

.depend: Makefile $(SRCS)
	@$(MKDEP) $(ROOTDEPPATH) "$(CC)" -- $(CFLAGS) -- $(SRCS) >Make.dep
	@touch $@

depend: .depend

clean:
	$(call DELFILE, .built)
	$(call CLEAN)

distclean: clean
	$(call DELFILE, Make.dep)
	$(call DELFILE, .depend)

-include Make.dep
