#####################################################################################
# Makefile for HAC Web Application
# # 
# # Initial creation.------------------------ 08-19-2010 wesley.xie elelonger@gmail.com
# # 
# ######################################################################################

include ../make-common.mk

PROJECT_NAME := Hac Web

PAGES_DIR := pages
IMAGES_DIR := images
CSS_DIR := css
JS_DIR := js
INDEX_FILE := index.htm

INSTALL_ROOT := ${ROOTFS_INSTALL}/usr/www

.PHONY: usage
usage:
	@echo 
	@echo " $(PROJECT_NAME) Build Help"
	@echo "    make all        -- make project "
	@echo "    make clean      -- clean project "
	@echo "    make distclean  -- deep clean "
	@echo "    make install    -- install project "
	@echo "    make rebuild    -- clean all install in right order "
	@echo


# build all
.PHONY: all
all:

# install
.PHONY: install
install:
	@cp -rfv *[!Makefile] $(INSTALL_ROOT)

# clean up
.PHONY: clean distclean
clean:

# deep clean
distclean: clean


# rebuild
.PHONY: rebuild

rebuild: distclean all install

