#####################################################################################
# common stuff used in applications makefile.
# 
# Initial creation.------------------------ 04-03-2009 wesley.xie elelonger@gmail.com
# 
######################################################################################

ifndef PROJECT
    $(error Please setup the project environment firstly. (Enter project root and "source project-env"))
endif

EXTLIB_STRIP=${STRIP} --strip-unneeded -v
EXTLIB_MKDIR=mkdir -pv

# install a directory $(1) to directory $(2):wq:
install_dir=[ -d $(2) ] || mkdir -pv $(2) && cp -avT $(1)

# install a file $(1) to directory $(2)
install_file=[ -d $(2)] || mkdir -pv $(2) && cp -av $(1) $(2)

# to check required utils needed for building
check_utils=@for u in $(1); do if ! which $$u > /dev/null; then \
		echo "'$$u' util not found in host, please install it firstly"; exit 1; \
		fi; done
