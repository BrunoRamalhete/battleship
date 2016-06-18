/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) Bruno Ramalhete 2015-2016 <bram.512@gmail.com>
 *
 * main.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * main.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <config.h>
#include <gtk/gtk.h>
/*
 * Standard gettext macros.
 */
#ifdef ENABLE_NLS
#  include <libintl.h>
#  undef _
#  define _(String) dgettext (PACKAGE, String)
#  ifdef gettext_noop
#    define N_(String) gettext_noop (String)
#  else
#    define N_(String) (String)
#  endif
#else
#  define textdomain(String) (String)
#  define gettext(String) (String)
#  define dgettext(Domain,Message) (Message)
#  define dcgettext(Domain,Message,Type) (Message)
#  define bindtextdomain(Domain,Directory) (Domain)
#  define _(String) (String)
#  define N_(String) (String)
#endif

extern void initialize ();
extern gint load (const gchar *keyword);
extern GtkWidget* display_window ();
extern const guint8 icon_water[], icon_my_ship[], icon_his_ship[], icon_hit_ship[], icon_unknown[], icon_logo[];

gint my_matrix[15][15], his_matrix[15][15], found_matrix[15][15], found_row[15], found_column[15];
gint NumberOfRows=10, NumberOfColumns=10, NumberOfShips=8, DifficultyLimit=1;
gint help = 1;
GdkPixbuf *pixbuf_water, *pixbuf_my_ship, *pixbuf_his_ship, *pixbuf_hit_ship, *pixbuf_unknown, *pixbuf_logo;


int main (int argc, char *argv[]) {
 	GtkWidget *window;
	gint tmp;


#ifdef ENABLE_NLS
	setlocale (LC_ALL, "");
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif

//	gtk_set_locale ();
	gtk_init (&argc, &argv);

	if ((tmp = load ("NumberOfRows")) != 0 ) NumberOfRows = (tmp<=15 ? tmp : 15);
	if ((tmp = load ("NumberOfColumns")) != 0 ) NumberOfColumns = (tmp<=15 ? tmp : 15);
	if ((tmp = load ("NumberOfShips")) != 0 ) NumberOfShips = tmp;
	if ((tmp = load ("DifficultyLimit")) != 0 ) DifficultyLimit = tmp;
	if ((tmp = load ("Help")) != 0 ) help = tmp;

	pixbuf_water = gdk_pixbuf_new_from_inline (-1, icon_water, FALSE, NULL);
	pixbuf_my_ship = gdk_pixbuf_new_from_inline (-1, icon_my_ship, FALSE, NULL);
	pixbuf_his_ship = gdk_pixbuf_new_from_inline (-1, icon_his_ship, FALSE, NULL);
	pixbuf_hit_ship = gdk_pixbuf_new_from_inline (-1, icon_hit_ship, FALSE, NULL);
	pixbuf_unknown = gdk_pixbuf_new_from_inline (-1, icon_unknown, FALSE, NULL);
	pixbuf_logo = gdk_pixbuf_new_from_inline (-1, icon_logo, FALSE, NULL);
//	if (pixbuf_unknown == NULL) g_print("Fehler\n"); else g_print("klasse\n");

	//enable images on buttons, since gnome disabled them by default
	GtkSettings *default_settings = gtk_settings_get_default();
	g_object_set (default_settings, "gtk-button-images", TRUE, NULL);

	window = display_window ();

	gtk_widget_show (window);
    gtk_window_resize (GTK_WINDOW (window), 1, 1);

	initialize ();

	gtk_main ();

	return 0;
}
