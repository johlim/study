/* cheese-main.c generated by valac 0.30.0.3-b11d, the Vala compiler
 * generated from cheese-main.vala, do not modify */

/*
 * Cheese - Take photos and videos with your webcam, with fun graphical effects
 * Copyright © 2013 David King <amigadave@amigadave.com>
 *
 * Licensed under the GNU General Public License Version 2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <glib/gi18n-lib.h>
#include <config.h>
#include <gtk/gtk.h>
#include <gio/gio.h>


#define CHEESE_TYPE_APPLICATION (cheese_application_get_type ())
#define CHEESE_APPLICATION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), CHEESE_TYPE_APPLICATION, CheeseApplication))
#define CHEESE_APPLICATION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), CHEESE_TYPE_APPLICATION, CheeseApplicationClass))
#define CHEESE_IS_APPLICATION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CHEESE_TYPE_APPLICATION))
#define CHEESE_IS_APPLICATION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CHEESE_TYPE_APPLICATION))
#define CHEESE_APPLICATION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), CHEESE_TYPE_APPLICATION, CheeseApplicationClass))

typedef struct _CheeseApplication CheeseApplication;
typedef struct _CheeseApplicationClass CheeseApplicationClass;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))



gint _vala_main (gchar** args, int args_length1);
CheeseApplication* cheese_application_new (void);
CheeseApplication* cheese_application_construct (GType object_type);
GType cheese_application_get_type (void) G_GNUC_CONST;


gint _vala_main (gchar** args, int args_length1) {
	gint result = 0;
	CheeseApplication* _tmp0_ = NULL;
	CheeseApplication* _tmp1_ = NULL;
	gchar** _tmp2_ = NULL;
	gint _tmp2__length1 = 0;
	gint _tmp3_ = 0;
	gint _tmp4_ = 0;
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALEDIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
	_tmp0_ = cheese_application_new ();
	_tmp1_ = _tmp0_;
	_tmp2_ = args;
	_tmp2__length1 = args_length1;
	_tmp3_ = g_application_run ((GApplication*) _tmp1_, _tmp2__length1, _tmp2_);
	_tmp4_ = _tmp3_;
	_g_object_unref0 (_tmp1_);
	result = _tmp4_;
	return result;
}


int main (int argc, char ** argv) {
#if !GLIB_CHECK_VERSION (2,32,0)
	g_thread_init (NULL);
#endif
#if !GLIB_CHECK_VERSION (2,35,0)
	g_type_init ();
#endif
	return _vala_main (argv, argc);
}



