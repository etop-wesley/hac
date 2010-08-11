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

TARGET=dnw
INST_ROOT ?= ${PROJECT_BUILD_INSTALL}

CC=gcc
CFLAGS +=
LDFLAGS += -lusb

SRCS := dnw.c

OBJS := $(patsubst %.c, %.o, $(filter %.c,$(SRCS)))


.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# install
.PHONY: install
install: all
	@echo
	@echo "Installing $(TARGET) ... "
	@cp -fv $(TARGET) $(INST_ROOT)
	@echo

# clean up
.PHONY: clean
clean:
	@echo
	@rm -rfv $(OBJS)
	@echo

# distclean
.PHONY: distclean
distclean: clean
	@rm -rfv $(TARGET)

# rebuild
.PHONY: rebuild
rebuild: distclean clean all install

