## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir). \
	$(GTK__CFLAGS)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(BATTLESHIP_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = battleship 

battleship_SOURCES = \
	callbacks.c \
	main.c \
	window.c \
	misc.c \
	icons.c

battleship_LDFLAGS = \
	-Wl,--export-dynamic

battleship_LDADD = $(BATTLESHIP_LIBS) \
	$(GTK__LIBS)

EXTRA_DIST = $(glade_DATA) \
	$(miscellaneous_DATA)\
	$(desktop_DATA)

INCLUDES = 

