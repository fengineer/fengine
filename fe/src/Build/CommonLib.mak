# Utilities.
MKDIR = mkdir -p
AR = ar rc
RANLIB = ranlib

# How to install. If your install program does not support "-p", then you
# may have to run ranlib on the installed libtinyxml.a (do "make ranlib").
INSTALL= install -p
INSTALL_DATA= $(INSTALL) -m 0644


install:

.PHONY: install