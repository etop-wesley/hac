#####################################################################################
# applications main makefile
# 
# Initial creation.------------------------ 08-08-2009 wesley.xie elelonger@gmail.com
# 
######################################################################################

include ./make-common.mk

# application list
APP_HACSERVER	:= hac-server
APP_HAC01	:= hac01

# library list
LIB_HACWIDGETS	:= hac-widgets
LIB_HACSETTINGS	:= hac-settings
LIB_HACPLUGINS	:= hac-plugins

# libraries list, the library should be built before application
QT_LIBS			:= $(LIB_HACWIDGETS) $(LIB_HACSETTINGS)

# applications those need qmake to go there
QT_APPS 		:= $(APP_HACSERVER) $(APP_HAC01)


# applications those need lrelease to go there
QT_LRELEASE_APPS	:=

# applications those have their own makefiles
APPS			:=


.PHONY: usage

usage:
	@echo "applications build help"
	@echo "    all        -- build the entire project"
	@echo "    install    -- install to target"
	@echo "    clean      -- clean project"
	@echo "    distclean   -- deep clean project"
	@echo "    lrelease   -- "
	@echo "    lupdate    -- "
	@echo "    install_qm -- "

.PHONY:  all install clean distclean rebuild

all:
	@for lib in $(QT_LIBS); do \
		cd $$lib && \
		${QMAKE} -nocache && ${MAKE} all install || exit 1; \
		cd -; \
	done;

	@for app in $(QT_APPS); do \
		cd $$app && \
		${QMAKE} -nocache && ${MAKE} all || exit 1; \
		cd -; \
	done;

	@for app in $(APPS); do \
		${MAKE} -C $$app all || exit 1; \
	done;

install:
	@for lib in $(QT_LIBS); do \
		cd $$lib && \
		${QMAKE} -nocache && ${MAKE} install || exit 1 && \
		cd -; \
	done;

	@for app in $(QT_APPS); do \
		cd $$app && \
		${QMAKE} -nocache && ${MAKE} install || exit 1 && \
		cd -; \
	done;

	@for app in $(APPS); do \
		${MAKE} -C $$app install || exit 1; \
	done;

clean:
	@for lib in $(QT_LIBS); do \
		cd $$lib && \
		${QMAKE} -nocache && ${MAKE} clean || exit 1 && \
		cd -; \
	done;

	@for app in $(QT_APPS); do \
		cd $$app && \
		${QMAKE} -nocache && ${MAKE} clean || exit 1 && \
		cd -; \
	done;

	@for app in $(APPS); do \
		${MAKE} -C $$app clean || exit 1; \
	done;

distclean:
	@for lib in $(QT_LIBS); do \
		cd $$lib && \
		${QMAKE} -nocache && ${MAKE} distclean || exit 1 && \
		cd -; \
	done;
	
	@for app in $(QT_APPS); do \
		cd $$app && \
		${QMAKE} -nocache && ${MAKE} distclean || exit 1 && \
		cd -; \
	done;

	@for app in $(APPS); do \
		${MAKE} -C $$app distclean || exit 1; \
	done;

rebuild:
	@for lib in $(QT_LIBS); do \
		cd $$lib && \
		${QMAKE} -nocache && ${MAKE} distclean && \
		${QMAKE} -nocache && ${MAKE} all install || exit 1 && \
		cd -; \
	done;
	
	@for app in $(QT_APPS); do \
		cd $$app && \
		${QMAKE} -nocache && ${MAKE} distclean && \
		${QMAKE} -nocache && ${MAKE} all install || exit 1 && \
		cd -; \
	done;

	@for app in $(APPS); do \
		${MAKE} -C $$app distclean all install || exit 1; \
	done;

