/* cheese-effects-manager.c generated by valac 0.30.1, the Vala compiler
 * generated from cheese-effects-manager.vala, do not modify */

/*
 * Copyright © 2010 Yuvaraj Pandian T <yuvipanda@yuvi.in>
 * Copyright © 2010 daniel g. siegel <dgsiegel@gnome.org>
 * Copyright © 2008 Filippo Argiolas <filippo.argiolas@gmail.com>
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
#include <cheese-effect.h>
#include <stdlib.h>
#include <string.h>
#include <glib/gi18n-lib.h>
#include <gst/gst.h>


#define CHEESE_TYPE_EFFECTS_MANAGER (cheese_effects_manager_get_type ())
#define CHEESE_EFFECTS_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), CHEESE_TYPE_EFFECTS_MANAGER, CheeseEffectsManager))
#define CHEESE_EFFECTS_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), CHEESE_TYPE_EFFECTS_MANAGER, CheeseEffectsManagerClass))
#define CHEESE_IS_EFFECTS_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CHEESE_TYPE_EFFECTS_MANAGER))
#define CHEESE_IS_EFFECTS_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), CHEESE_TYPE_EFFECTS_MANAGER))
#define CHEESE_EFFECTS_MANAGER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), CHEESE_TYPE_EFFECTS_MANAGER, CheeseEffectsManagerClass))

typedef struct _CheeseEffectsManager CheeseEffectsManager;
typedef struct _CheeseEffectsManagerClass CheeseEffectsManagerClass;
typedef struct _CheeseEffectsManagerPrivate CheeseEffectsManagerPrivate;
#define __g_list_free__g_object_unref0_0(var) ((var == NULL) ? NULL : (var = (_g_list_free__g_object_unref0_ (var), NULL)))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_hash_table_unref0(var) ((var == NULL) ? NULL : (var = (g_hash_table_unref (var), NULL)))
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))

struct _CheeseEffectsManager {
	GObject parent_instance;
	CheeseEffectsManagerPrivate * priv;
	GList* effects;
};

struct _CheeseEffectsManagerClass {
	GObjectClass parent_class;
};


static gpointer cheese_effects_manager_parent_class = NULL;

GType cheese_effects_manager_get_type (void) G_GNUC_CONST;
enum  {
	CHEESE_EFFECTS_MANAGER_DUMMY_PROPERTY
};
static void _g_object_unref0_ (gpointer var);
static void _g_list_free__g_object_unref0_ (GList* self);
CheeseEffectsManager* cheese_effects_manager_new (void);
CheeseEffectsManager* cheese_effects_manager_construct (GType object_type);
void cheese_effects_manager_load_effects (CheeseEffectsManager* self);
static void _g_free0_ (gpointer var);
static void cheese_effects_manager_add_effect (CheeseEffectsManager* self, const gchar* name, CheeseEffect* effect);
static void _cheese_effects_manager_add_effect_gh_func (gconstpointer key, gconstpointer value, gpointer self);
static gint cheese_effects_manager_sort_value (CheeseEffect* a, CheeseEffect* b);
static gint _cheese_effects_manager_sort_value_gcompare_func (gconstpointer a, gconstpointer b);
CheeseEffect* cheese_effects_manager_get_effect (CheeseEffectsManager* self, const gchar* name);
static gboolean cheese_effects_manager_cmp_value (CheeseEffect* a, CheeseEffect* b);
static void cheese_effects_manager_finalize (GObject* obj);


static void _g_object_unref0_ (gpointer var) {
	(var == NULL) ? NULL : (var = (g_object_unref (var), NULL));
}


static void _g_list_free__g_object_unref0_ (GList* self) {
	g_list_foreach (self, (GFunc) _g_object_unref0_, NULL);
	g_list_free (self);
}


CheeseEffectsManager* cheese_effects_manager_construct (GType object_type) {
	CheeseEffectsManager * self = NULL;
	self = (CheeseEffectsManager*) g_object_new (object_type, NULL);
	__g_list_free__g_object_unref0_0 (self->effects);
	self->effects = NULL;
	return self;
}


CheeseEffectsManager* cheese_effects_manager_new (void) {
	return cheese_effects_manager_construct (CHEESE_TYPE_EFFECTS_MANAGER);
}


/**
     * Add the effects into the manager.
     */
static void _g_free0_ (gpointer var) {
	var = (g_free (var), NULL);
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static void _cheese_effects_manager_add_effect_gh_func (gconstpointer key, gconstpointer value, gpointer self) {
	cheese_effects_manager_add_effect ((CheeseEffectsManager*) self, (const gchar*) key, (CheeseEffect*) value);
}


void cheese_effects_manager_load_effects (CheeseEffectsManager* self) {
	GList* loaded_effects = NULL;
	GList* _tmp0_ = NULL;
	GHashTable* effects_hash = NULL;
	GHashFunc _tmp1_ = NULL;
	GEqualFunc _tmp2_ = NULL;
	GHashTable* _tmp3_ = NULL;
	GList* _tmp4_ = NULL;
	GHashTable* _tmp13_ = NULL;
	GList* _tmp14_ = NULL;
	guint _tmp15_ = 0U;
	g_return_if_fail (self != NULL);
	_tmp0_ = cheese_effect_load_effects ();
	loaded_effects = _tmp0_;
	_tmp1_ = g_str_hash;
	_tmp2_ = g_str_equal;
	_tmp3_ = g_hash_table_new_full (_tmp1_, _tmp2_, _g_free0_, _g_object_unref0_);
	effects_hash = _tmp3_;
	_tmp4_ = loaded_effects;
	{
		GList* effect_collection = NULL;
		GList* effect_it = NULL;
		effect_collection = _tmp4_;
		for (effect_it = effect_collection; effect_it != NULL; effect_it = effect_it->next) {
			CheeseEffect* _tmp5_ = NULL;
			CheeseEffect* effect = NULL;
			_tmp5_ = _g_object_ref0 ((CheeseEffect*) effect_it->data);
			effect = _tmp5_;
			{
				GHashTable* _tmp6_ = NULL;
				CheeseEffect* _tmp7_ = NULL;
				const gchar* _tmp8_ = NULL;
				const gchar* _tmp9_ = NULL;
				gchar* _tmp10_ = NULL;
				CheeseEffect* _tmp11_ = NULL;
				CheeseEffect* _tmp12_ = NULL;
				_tmp6_ = effects_hash;
				_tmp7_ = effect;
				_tmp8_ = cheese_effect_get_name (_tmp7_);
				_tmp9_ = _tmp8_;
				_tmp10_ = g_strdup (_tmp9_);
				_tmp11_ = effect;
				_tmp12_ = _g_object_ref0 (_tmp11_);
				g_hash_table_insert (_tmp6_, _tmp10_, _tmp12_);
				_g_object_unref0 (effect);
			}
		}
	}
	_tmp13_ = effects_hash;
	g_hash_table_foreach (_tmp13_, _cheese_effects_manager_add_effect_gh_func, self);
	_tmp14_ = self->effects;
	_tmp15_ = g_list_length (_tmp14_);
	if (_tmp15_ > ((guint) 0)) {
		CheeseEffect* e = NULL;
		const gchar* _tmp16_ = NULL;
		CheeseEffect* _tmp17_ = NULL;
		CheeseEffect* _tmp18_ = NULL;
		CheeseEffect* _tmp19_ = NULL;
		_tmp16_ = _ ("No Effect");
		_tmp17_ = cheese_effect_new (_tmp16_, "identity");
		e = _tmp17_;
		_tmp18_ = e;
		_tmp19_ = _g_object_ref0 (_tmp18_);
		self->effects = g_list_prepend (self->effects, _tmp19_);
		_g_object_unref0 (e);
	}
	_g_hash_table_unref0 (effects_hash);
	__g_list_free__g_object_unref0_0 (loaded_effects);
}


/**
     * Add an effect into the manager. Used as a HFunc.
     */
static gint _cheese_effects_manager_sort_value_gcompare_func (gconstpointer a, gconstpointer b) {
	gint result;
	result = cheese_effects_manager_sort_value ((CheeseEffect*) a, (CheeseEffect*) b);
	return result;
}


static void cheese_effects_manager_add_effect (CheeseEffectsManager* self, const gchar* name, CheeseEffect* effect) {
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (name != NULL);
	g_return_if_fail (effect != NULL);
	{
		CheeseEffect* _tmp0_ = NULL;
		const gchar* _tmp1_ = NULL;
		const gchar* _tmp2_ = NULL;
		GstElement* _tmp3_ = NULL;
		GstElement* _tmp4_ = NULL;
		CheeseEffect* _tmp5_ = NULL;
		CheeseEffect* _tmp6_ = NULL;
		_tmp0_ = effect;
		_tmp1_ = cheese_effect_get_pipeline_desc (_tmp0_);
		_tmp2_ = _tmp1_;
		_tmp3_ = gst_parse_bin_from_description_full (_tmp2_, FALSE, NULL, GST_PARSE_FLAG_FATAL_ERRORS, &_inner_error_);
		g_object_ref_sink (_tmp3_);
		_tmp4_ = _tmp3_;
		_g_object_unref0 (_tmp4_);
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			goto __catch2_g_error;
		}
		_tmp5_ = effect;
		_tmp6_ = _g_object_ref0 (_tmp5_);
		self->effects = g_list_insert_sorted (self->effects, _tmp6_, _cheese_effects_manager_sort_value_gcompare_func);
	}
	goto __finally2;
	__catch2_g_error:
	{
		GError* err = NULL;
		CheeseEffect* _tmp7_ = NULL;
		const gchar* _tmp8_ = NULL;
		const gchar* _tmp9_ = NULL;
		GError* _tmp10_ = NULL;
		const gchar* _tmp11_ = NULL;
		err = _inner_error_;
		_inner_error_ = NULL;
		_tmp7_ = effect;
		_tmp8_ = cheese_effect_get_name (_tmp7_);
		_tmp9_ = _tmp8_;
		_tmp10_ = err;
		_tmp11_ = _tmp10_->message;
		g_debug ("cheese-effects-manager.vala:70: Effect '%s' did not parse correctly, s" \
"kipping: %s", _tmp9_, _tmp11_);
		_g_error_free0 (err);
	}
	__finally2:
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
}


/**
     * Search for and return the requested effect.
     *
     * @param name the name of the effect to search for
     * @return the effect which matches the supplied name, or null
     */
CheeseEffect* cheese_effects_manager_get_effect (CheeseEffectsManager* self, const gchar* name) {
	CheeseEffect* result = NULL;
	GList* _tmp0_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (name != NULL, NULL);
	_tmp0_ = self->effects;
	{
		GList* effect_collection = NULL;
		GList* effect_it = NULL;
		effect_collection = _tmp0_;
		for (effect_it = effect_collection; effect_it != NULL; effect_it = effect_it->next) {
			CheeseEffect* _tmp1_ = NULL;
			CheeseEffect* effect = NULL;
			_tmp1_ = _g_object_ref0 ((CheeseEffect*) effect_it->data);
			effect = _tmp1_;
			{
				CheeseEffect* _tmp2_ = NULL;
				const gchar* _tmp3_ = NULL;
				const gchar* _tmp4_ = NULL;
				const gchar* _tmp5_ = NULL;
				_tmp2_ = effect;
				_tmp3_ = cheese_effect_get_name (_tmp2_);
				_tmp4_ = _tmp3_;
				_tmp5_ = name;
				if (g_strcmp0 (_tmp4_, _tmp5_) == 0) {
					result = effect;
					return result;
				}
				_g_object_unref0 (effect);
			}
		}
	}
	result = NULL;
	return result;
}


/**
   * Compare two effects by the pipeline description.
   *
   * @param a an effect to compare against
   * @param b another effect to compare against
   * @return true if the effects are the same, false otherwise
   */
static gboolean cheese_effects_manager_cmp_value (CheeseEffect* a, CheeseEffect* b) {
	gboolean result = FALSE;
	CheeseEffect* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	CheeseEffect* _tmp3_ = NULL;
	const gchar* _tmp4_ = NULL;
	const gchar* _tmp5_ = NULL;
	g_return_val_if_fail (a != NULL, FALSE);
	g_return_val_if_fail (b != NULL, FALSE);
	_tmp0_ = a;
	_tmp1_ = cheese_effect_get_pipeline_desc (_tmp0_);
	_tmp2_ = _tmp1_;
	_tmp3_ = b;
	_tmp4_ = cheese_effect_get_pipeline_desc (_tmp3_);
	_tmp5_ = _tmp4_;
	result = g_strcmp0 (_tmp2_, _tmp5_) == 0;
	return result;
}


/**
   * A sort function for effects
   *
   * @param a an effect to sort against
   * @param b another effect to sort against
   * @return -1 if a is less than b, 0 if the effects are the same and 1 if a
   * is greater than b
   */
static gint cheese_effects_manager_sort_value (CheeseEffect* a, CheeseEffect* b) {
	gint result = 0;
	CheeseEffect* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	gchar* _tmp3_ = NULL;
	gchar* _tmp4_ = NULL;
	CheeseEffect* _tmp5_ = NULL;
	const gchar* _tmp6_ = NULL;
	const gchar* _tmp7_ = NULL;
	gchar* _tmp8_ = NULL;
	gchar* _tmp9_ = NULL;
	gboolean _tmp10_ = FALSE;
	g_return_val_if_fail (a != NULL, 0);
	g_return_val_if_fail (b != NULL, 0);
	_tmp0_ = a;
	_tmp1_ = cheese_effect_get_name (_tmp0_);
	_tmp2_ = _tmp1_;
	_tmp3_ = g_utf8_strdown (_tmp2_, (gssize) -1);
	_tmp4_ = _tmp3_;
	_tmp5_ = b;
	_tmp6_ = cheese_effect_get_name (_tmp5_);
	_tmp7_ = _tmp6_;
	_tmp8_ = g_utf8_strdown (_tmp7_, (gssize) -1);
	_tmp9_ = _tmp8_;
	_tmp10_ = g_strcmp0 (_tmp4_, _tmp9_) < 0;
	_g_free0 (_tmp9_);
	_g_free0 (_tmp4_);
	if (_tmp10_) {
		result = -1;
		return result;
	} else {
		CheeseEffect* _tmp11_ = NULL;
		const gchar* _tmp12_ = NULL;
		const gchar* _tmp13_ = NULL;
		gchar* _tmp14_ = NULL;
		gchar* _tmp15_ = NULL;
		CheeseEffect* _tmp16_ = NULL;
		const gchar* _tmp17_ = NULL;
		const gchar* _tmp18_ = NULL;
		gchar* _tmp19_ = NULL;
		gchar* _tmp20_ = NULL;
		gboolean _tmp21_ = FALSE;
		_tmp11_ = a;
		_tmp12_ = cheese_effect_get_name (_tmp11_);
		_tmp13_ = _tmp12_;
		_tmp14_ = g_utf8_strdown (_tmp13_, (gssize) -1);
		_tmp15_ = _tmp14_;
		_tmp16_ = b;
		_tmp17_ = cheese_effect_get_name (_tmp16_);
		_tmp18_ = _tmp17_;
		_tmp19_ = g_utf8_strdown (_tmp18_, (gssize) -1);
		_tmp20_ = _tmp19_;
		_tmp21_ = g_strcmp0 (_tmp15_, _tmp20_) > 0;
		_g_free0 (_tmp20_);
		_g_free0 (_tmp15_);
		if (_tmp21_) {
			result = 1;
			return result;
		} else {
			result = 0;
			return result;
		}
	}
}


static void cheese_effects_manager_class_init (CheeseEffectsManagerClass * klass) {
	cheese_effects_manager_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = cheese_effects_manager_finalize;
}


static void cheese_effects_manager_instance_init (CheeseEffectsManager * self) {
}


static void cheese_effects_manager_finalize (GObject* obj) {
	CheeseEffectsManager * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, CHEESE_TYPE_EFFECTS_MANAGER, CheeseEffectsManager);
	__g_list_free__g_object_unref0_0 (self->effects);
	G_OBJECT_CLASS (cheese_effects_manager_parent_class)->finalize (obj);
}


GType cheese_effects_manager_get_type (void) {
	static volatile gsize cheese_effects_manager_type_id__volatile = 0;
	if (g_once_init_enter (&cheese_effects_manager_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (CheeseEffectsManagerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) cheese_effects_manager_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (CheeseEffectsManager), 0, (GInstanceInitFunc) cheese_effects_manager_instance_init, NULL };
		GType cheese_effects_manager_type_id;
		cheese_effects_manager_type_id = g_type_register_static (G_TYPE_OBJECT, "CheeseEffectsManager", &g_define_type_info, 0);
		g_once_init_leave (&cheese_effects_manager_type_id__volatile, cheese_effects_manager_type_id);
	}
	return cheese_effects_manager_type_id__volatile;
}



