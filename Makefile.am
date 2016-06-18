## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src po

battleshipdocdir = ${prefix}/doc/battleship
battleshipdoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS

EXTRA_DIST = $(battleshipdoc_DATA) \
	$(desktop_DATA)\
	$(icon_DATA)

desktop_DATA = \
	battleship.desktop

desktopdir = \
	/usr/share/applications

icon_DATA = \
	icons/battleship.xpm

icondir = \
	$(prefix)/share/pixmaps

# Copy all the spec files. Of cource, only one is actually used.
dist-hook:
	for specfile in *.spec; do \
		if test -f $$specfile; then \
			cp -p $$specfile $(distdir); \
		fi \
	done

