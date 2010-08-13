##############################################
#
#	HacWidgets Library
#
##############################################

include(config.pri)

TEMPLATE = subdirs

contains(CONFIG, Widgets) {
    SUBDIRS += widgets
}

contains(CONFIG, Designer) {
    SUBDIRS += designer
}

contains(CONFIG, Examples) {
    SUBDIRS += examples
}
