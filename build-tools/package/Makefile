##############################################################################
#
#  Makefile
#
# Initial creation --------------------------- wesley.xie elelonger@gmail.com
#
##############################################################################

ifndef PROJECT
    $(error Please setup the project environment firstly. (Enter project root and "source project-env"))
endif

# include system config 
include config
# build target
TARGET := package
# project directories
ROOT_DIR := .
DIR_INCLUDE := .
DIR_SRC := .
DIR_DEST := _build
DIR_OBJS := _obj

INST_ROOT ?= ${PROJECT_BUILD_INSTALL}
DIR_INSTALL := ${INST_ROOT}

SUB_DIRS := $(ROOT_DIR)

# look for include files in each of the directories
VPATH           = $(patsubst %' ',%':',$(SUB_DIRS))
CFLAGS          += $(patsubst %,-I%,$(SUB_DIRS))

# include externel libs if required
ifeq ($(CONFIG_BUILD_TARGET), ARM)
CFLAGS            += -I${TOOLCHAIN_ARCH}/include \
                     -I${TOOLCHAIN_USR_INSTALL}/include/
LDFLAGS           +=
endif
ifeq ($(CONFIG_BUILD_TARGET), HOST)
CFLAGS            += -Ilibconfig-1.4.5/lib
LDFLAGS           += -Llibconfig-1.4.5/lib/.libs -lconfig
endif

# debug flags
ifeq ($(CONFIG_DEBUG_OPT),YES)
        CFLAGS            += -ggdb -O0
else
        CFLAGS            += -O3 -fno-strict-aliasing
endif

# link flags
ifeq ($(CONFIG_BUILD_TEMPLATE), APP)
LDFLAGS        += 
endif
ifeq ($(CONFIG_BUILD_TEMPLATE), LIB)
LDFLAGS        += -shared
endif

# compiler flags
CFLAGS         += $(DEFINES) -Wall #-Werror -fpic


# include the description for each module
include $(patsubst %,%/Makefile.sub,$(SUB_DIRS))

# object files
OBJS        := $(patsubst %.c,$(DIR_OBJS)/%.o,$(filter %.c,$(SRCS)))
DEPS        := $(patsubst %.c,$(DIR_OBJS)/%.d,$(filter %.c,$(SRCS)))


.PHONY: usage
usage:
	@echo 
	@echo "Build Help for $(TARGET)"
	@echo "    make all        -- make lib"
	@echo "    make clean      -- clean objects"
	@echo "    make distclean  -- clean all"
	@echo "    make install    -- install lib"
	@echo "    make rebuild    -- distclean, all, install"
	@echo

# build all
.PHONY: all
all: $(DIR_DEST)/$(TARGET)

$(DIR_DEST)/$(TARGET): libconfig_all $(DEPS) $(OBJS)
	@mkdir -pv $(DIR_DEST)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(LDFLAGS)

# install
.PHONY: install
install: all
	@echo
	@echo "Installing $(TARGET) ... "
	@cp -fv $(DIR_DEST)/$(TARGET) $(DIR_INSTALL)
	@echo

# clean up
.PHONY: clean
clean:
	@echo
	@rm -rfv $(DIR_OBJS)/*
	@echo
# distclean
.PHONY: distclean
distclean: clean libconfig_clean
	@rm -rfv $(DIR_OBJS)
	@rm -rfv $(DIR_DEST)/*
	@rm -rfv $(DIR_DEST)

# rebuild
.PHONY: rebuild
rebuild: distclean clean all install


# include the C include dependencies
-include $(OBJS:.o=.d)


# calculate C inlcude dependencies
$(DIR_OBJS)/%.d: %.c
	@set -e; rm -f $@; \
	mkdir -pv $(DIR_OBJS); \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

# calculate c object build rule
$(DIR_OBJS)/%.o: %.c
	@mkdir -pv $(DIR_OBJS)
	${CC} $(CFLAGS) -c -o $@ $<

# rule for libconfig
libconfig_all:
	@if [ ! -e libconfig-1.4.5/lib/.libs/libconfig.a ]; then \
		rm -rf libconfig-1.4.5; \
		tar -xzvf libconfig-1.4.5.tar.gz; \
		cd libconfig-1.4.5 \
			&& configure --enable-shared=no --disable-cxx --disable-examples \
			&& make && make check; \
	fi;
libconfig_clean:
	@rm -rfv libconfig-1.4.5

# include make rules. 
include Makefile.rules
