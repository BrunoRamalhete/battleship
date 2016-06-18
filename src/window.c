/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * window.c
 * Copyright (C) Bruno Ramalhete 2015-2016 <bram.512@gmail.com>
 * 
 * window.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * window.c is distributed in the hope that it will be useful, but
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

extern gboolean on_his_position_clicked (GtkButton* button, GdkEventButton *event, gpointer data);
extern gboolean on_my_position_clicked (GtkButton* button, gpointer row, gpointer column);
extern void menu_remove_marks ();
extern void menu_start ();
extern void menu_exit ();
extern void menu_preferences ();
extern void menu_help ();
extern void menu_about ();
extern void initialize ();


extern gint NumberOfRows, NumberOfColumns, NumberOfShips;


GtkWidget *window;
GtkWidget *my_frame, *his_frame;
GtkWidget *my_vbox, *his_vbox;
GtkWidget *my_table, *his_table;
GtkWidget *my_label, *his_label;
GtkWidget *my_time_label, *his_time_label;
GtkButton *my_position[15][15], *his_position[15][15];
gulong my_handler_id[15][15], his_handler_id[15][15];
extern GdkPixbuf *pixbuf_unknown, *pixbuf_logo;
extern GtkWidget *my_image[15][15], *his_image[15][15];
GtkWidget *image;


GtkWidget* display_window () {
	GtkWidget *vbox, *menu_bar, *root_menu, *menu, *menu_item, *hbox, *vseparator, *my_hbox, *his_hbox;
	gint row, column;
	
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (window), -1, -1);
    gtk_window_set_title (GTK_WINDOW (window), _("Battle Ship"));
	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect_swapped (G_OBJECT (window), "delete_event", G_CALLBACK (gtk_widget_destroy), G_OBJECT (window));

    vbox = gtk_vbox_new (FALSE, 8);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);

    menu_bar = gtk_menu_bar_new ();
    gtk_box_pack_start (GTK_BOX (vbox), menu_bar, FALSE, FALSE, 2);
    gtk_widget_show (menu_bar);
	
	root_menu = gtk_menu_item_new_with_label (_("Game"));
    gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar), root_menu);
	gtk_widget_show (root_menu);

	menu = gtk_menu_new ();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (root_menu), menu);

	menu_item = gtk_image_menu_item_new_from_stock (GTK_STOCK_CLEAR, NULL);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_item);
	g_signal_connect_swapped (G_OBJECT (menu_item), "activate", G_CALLBACK (menu_remove_marks), NULL);
	gtk_widget_show (menu_item);
	
	menu_item = gtk_image_menu_item_new_from_stock (GTK_STOCK_REDO, NULL);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_item);
	g_signal_connect_swapped (G_OBJECT (menu_item), "activate", G_CALLBACK (menu_start), NULL);
	gtk_widget_show (menu_item);
	
	menu_item = gtk_separator_menu_item_new ();
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_item);
	gtk_widget_show (menu_item);
	
	menu_item = gtk_image_menu_item_new_from_stock (GTK_STOCK_QUIT, NULL);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_item);
	g_signal_connect_swapped (G_OBJECT (menu_item), "activate", G_CALLBACK (menu_exit), NULL);
	gtk_widget_show (menu_item);
	
	root_menu = gtk_menu_item_new_with_label (_("Preferences"));
    gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar), root_menu);
	gtk_widget_show (root_menu);

	menu = gtk_menu_new ();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (root_menu), menu);

	menu_item = gtk_image_menu_item_new_from_stock (GTK_STOCK_PREFERENCES, NULL);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_item);
	g_signal_connect_swapped (G_OBJECT (menu_item), "activate", G_CALLBACK (menu_preferences), NULL);
	gtk_widget_show (menu_item);

	root_menu = gtk_menu_item_new_with_label (_("Help"));
    gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar), root_menu);
	gtk_widget_show (root_menu);

	menu = gtk_menu_new ();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (root_menu), menu);

	menu_item = gtk_image_menu_item_new_from_stock (GTK_STOCK_HELP, NULL);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_item);
	g_signal_connect_swapped (G_OBJECT (menu_item), "activate", G_CALLBACK (menu_help), NULL);
	gtk_widget_show (menu_item);

	menu_item = gtk_image_menu_item_new_from_stock (GTK_STOCK_ABOUT, NULL);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_item);
	g_signal_connect_swapped (G_OBJECT (menu_item), "activate", G_CALLBACK (menu_about), NULL);
	gtk_widget_show (menu_item);
	
	hbox = gtk_hbox_new (FALSE, 8);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
    gtk_widget_show (hbox);
	
	image = gtk_image_new_from_pixbuf (pixbuf_logo);
    gtk_box_pack_start (GTK_BOX (hbox), image, TRUE, FALSE, 16);
    gtk_widget_show (image);
	
	vseparator = gtk_vseparator_new();
    gtk_box_pack_start (GTK_BOX (hbox), vseparator, FALSE, FALSE, 0);
    gtk_widget_show (vseparator);	
	
	my_frame = gtk_frame_new (_("My Ships"));
	gtk_box_pack_start (GTK_BOX (hbox), my_frame, FALSE, FALSE, 8);
    gtk_widget_show (my_frame);
	
	my_vbox = gtk_vbox_new (FALSE, 8);
    gtk_container_add (GTK_CONTAINER (my_frame), my_vbox);
	gtk_widget_show (my_vbox);
	
	my_table = gtk_table_new (NumberOfRows, NumberOfColumns, TRUE);
    gtk_box_pack_start (GTK_BOX (my_vbox), my_table, FALSE, FALSE, 0);
    gtk_widget_show (my_table);
	
	for (row=0;row<NumberOfRows;row++)
		for (column=0;column<NumberOfColumns;column++) {
			my_position[row][column] = GTK_BUTTON (gtk_button_new_with_label (""));
			my_image[row][column] = gtk_image_new_from_pixbuf (pixbuf_unknown);
			gtk_button_set_image (my_position[row][column], my_image[row][column]);
			my_handler_id[row][column] = g_signal_connect (G_OBJECT (my_position[row][column]), "clicked", G_CALLBACK (on_my_position_clicked), GINT_TO_POINTER (row*100+column));
			gtk_table_attach_defaults (GTK_TABLE (my_table), GTK_WIDGET (my_position[row][column]), column, column+1, row, row+1);
			gtk_widget_show (GTK_WIDGET (my_position[row][column]));
		}
	
	my_hbox = gtk_hbox_new (FALSE, 0);
    gtk_box_pack_end (GTK_BOX (my_vbox), my_hbox, FALSE, FALSE, 0);
    gtk_widget_show (my_hbox);

	my_time_label = gtk_label_new (" 0:00,000");
	gtk_box_pack_start (GTK_BOX (my_hbox), my_time_label, TRUE, FALSE, 0);
    gtk_widget_show (my_time_label);
	
	my_label = gtk_label_new (_("Set ships."));
	gtk_box_pack_start (GTK_BOX (my_hbox), my_label, TRUE, FALSE, 0);
    gtk_widget_show (my_label);
	
	vseparator = gtk_vseparator_new();
    gtk_box_pack_start (GTK_BOX (hbox), vseparator, FALSE, FALSE, 0);
    gtk_widget_show (vseparator);	
	
	his_frame = gtk_frame_new (_("The Enemy's Ships"));
	gtk_box_pack_start (GTK_BOX (hbox), his_frame, FALSE, FALSE, 8);
    gtk_widget_show (his_frame);
	
	his_vbox = gtk_vbox_new (FALSE, 8);
    gtk_container_add (GTK_CONTAINER (his_frame), his_vbox);
    gtk_widget_show (his_vbox);
	
	his_table = gtk_table_new (NumberOfRows, NumberOfColumns, TRUE);
    gtk_box_pack_start (GTK_BOX (his_vbox), his_table, FALSE, FALSE, 0);
    gtk_widget_show (his_table);
	
	for (row=0;row<NumberOfRows;row++)
		for (column=0;column<NumberOfColumns;column++) {
			his_position[row][column] = GTK_BUTTON (gtk_button_new_with_label (""));
			his_image[row][column] = gtk_image_new_from_pixbuf (pixbuf_unknown);
			gtk_button_set_image (his_position[row][column], his_image[row][column]);
			his_handler_id[row][column] = g_signal_connect (G_OBJECT (his_position[row][column]), "button-press-event", G_CALLBACK (on_his_position_clicked), GINT_TO_POINTER (row*100+column));
			gtk_table_attach_defaults (GTK_TABLE (his_table), GTK_WIDGET (his_position[row][column]), column, column+1, row, row+1);
			gtk_widget_show (GTK_WIDGET (his_position[row][column]));
		}
	
	his_hbox = gtk_hbox_new (FALSE, 0);
    gtk_box_pack_end (GTK_BOX (his_vbox), his_hbox, FALSE, FALSE, 0);
    gtk_widget_show (his_hbox);

	his_time_label = gtk_label_new (" 0:00");
	gtk_box_pack_start (GTK_BOX (his_hbox), his_time_label, TRUE, FALSE, 0);
    gtk_widget_show (his_time_label);
	
	his_label = gtk_label_new ("");
	gtk_box_pack_start (GTK_BOX (his_hbox), his_label, TRUE, FALSE, 0);
    gtk_widget_show (his_label);

	return window;
}

 
void end_dialog (char *string) {
	GtkWidget *end_dialog, *label;
	extern gint timeout_id;
	gint result;

	g_source_remove (timeout_id);
		
	end_dialog = gtk_dialog_new_with_buttons (_("End"), 
											  GTK_WINDOW (window), 
											  GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, 
											  GTK_STOCK_QUIT, 1, 
											  GTK_STOCK_REDO, 2,
											  NULL);
	
	label = gtk_label_new (string);
	// gtk_box_pack_start (GTK_BOX (GTK_DIALOG (end_dialog)->vbox), label, TRUE, TRUE, 0);
    gtk_widget_show (label);
	
	result = gtk_dialog_run (GTK_DIALOG (end_dialog));
	switch (result) {
		case 1:
			menu_exit ();
			break;
		case 2:
			initialize ();
		default:
			break;
    }
	gtk_widget_destroy (end_dialog);

}
