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
CGI_DIR := cgi-bin
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
install: install_index install_pages install_js install_css install_images install_cgi

install_index:
	#@cp -fv $(INDEX_FILE) $(INSTALL_ROOT)
	@cp -fv ./*.htm $(INSTALL_ROOT)

install_pages:
	@mkdir -pv $(INSTALL_ROOT)/$(PAGES_DIR)
	@cp -rfv $(PAGES_DIR)/*.htm $(INSTALL_ROOT)/$(PAGES_DIR)

install_js:
	@mkdir -pv $(INSTALL_ROOT)/$(JS_DIR)
	@cp -rfv $(JS_DIR)/* $(INSTALL_ROOT)/$(JS_DIR)

	
install_css:
	@mkdir -pv $(INSTALL_ROOT)/$(CSS_DIR)
	@cp -rfv $(CSS_DIR)/* $(INSTALL_ROOT)/$(CSS_DIR)

install_images:
	@mkdir -pv $(INSTALL_ROOT)/$(IMAGES_DIR)
	@cp -rfv $(IMAGES_DIR)/* $(INSTALL_ROOT)/$(IMAGES_DIR)

install_cgi:
	#@mkdir -pv $(INSTALL_ROOT)/$(CGI_DIR)
	#@cp -rfv $(CGI_DIR)/* $(INSTALL_ROOT)/$(CGI_DIR)

# clean up
.PHONY: clean distclean
clean:

# deep clean
distclean: clean


# rebuild
.PHONY: rebuild

rebuild: distclean all install

