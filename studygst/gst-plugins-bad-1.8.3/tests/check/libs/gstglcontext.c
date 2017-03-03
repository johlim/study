/* GStreamer
 *
 * Copyright (C) 2013 Matthew Waters <ystreet00@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <gst/check/gstcheck.h>

#include <gst/gl/gstglcontext.h>

#include <stdio.h>

static GstGLDisplay *display;

static void
setup (void)
{
  display = gst_gl_display_new ();
}

static void
teardown (void)
{
  gst_object_unref (display);
}

static GLuint vbo, vbo_indices, vao, fbo_id, rbo, tex;
static GstGLFramebuffer *fbo;
static GstGLShader *shader;
static GLint shader_attr_position_loc;
static GLint shader_attr_texture_loc;

static const GLfloat vertices[] = {
  /* x, y, z, s, t */
  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
  -1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
  -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
  1.0f, -1.0f, 0.0f, 1.0f, 1.0f
};

static const GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

static void
init (gpointer data)
{
  GstGLContext *context = data;
  GError *error = NULL;

  /* has to be called in the thread that is going to use the framebuffer */
  fbo = gst_gl_framebuffer_new (context);

  gst_gl_framebuffer_generate (fbo, 320, 240, &fbo_id, &rbo);
  fail_if (fbo == NULL || fbo_id == 0, "failed to create framebuffer object");

  gst_gl_context_gen_texture (context, &tex, GST_VIDEO_FORMAT_RGBA, 320, 240);
  fail_if (tex == 0, "failed to create texture");

  shader = gst_gl_shader_new_default (context, &error);
  fail_if (shader == NULL, "failed to create shader object: %s",
      error->message);

  shader_attr_position_loc =
      gst_gl_shader_get_attribute_location (shader, "a_position");
  shader_attr_texture_loc =
      gst_gl_shader_get_attribute_location (shader, "a_texcoord");
}

static void
deinit (gpointer data)
{
  GstGLContext *context = data;
  GstGLFuncs *gl = context->gl_vtable;
  gl->DeleteTextures (1, &tex);
  if (vao)
    gl->DeleteVertexArrays (1, &vao);
  gst_object_unref (fbo);
  gst_object_unref (shader);
}

static void
clear_tex (gpointer data)
{
  GstGLContext *context = data;
  GstGLFuncs *gl = context->gl_vtable;
  static gfloat r = 0.0, g = 0.0, b = 0.0;

  gl->ClearColor (r, g, b, 1.0);
  gl->Clear (GL_COLOR_BUFFER_BIT);

  r = r > 1.0 ? 0.0 : r + 0.03;
  g = g > 1.0 ? 0.0 : g + 0.01;
  b = b > 1.0 ? 0.0 : b + 0.015;
}

static void
draw_tex (gpointer data)
{
  gst_gl_framebuffer_use_v2 (fbo, 320, 240, fbo_id, rbo, tex,
      (GLCB_V2) clear_tex, data);
}

static void
_bind_buffer (GstGLContext * context)
{
  const GstGLFuncs *gl = context->gl_vtable;

  gl->BindBuffer (GL_ELEMENT_ARRAY_BUFFER, vbo_indices);
  gl->BindBuffer (GL_ARRAY_BUFFER, vbo);

  /* Load the vertex position */
  gl->VertexAttribPointer (shader_attr_position_loc, 3, GL_FLOAT, GL_FALSE,
      5 * sizeof (GLfloat), (void *) 0);

  /* Load the texture coordinate */
  gl->VertexAttribPointer (shader_attr_texture_loc, 2, GL_FLOAT, GL_FALSE,
      5 * sizeof (GLfloat), (void *) (3 * sizeof (GLfloat)));

  gl->EnableVertexAttribArray (shader_attr_position_loc);
  gl->EnableVertexAttribArray (shader_attr_texture_loc);
}

static void
_unbind_buffer (GstGLContext * context)
{
  const GstGLFuncs *gl = context->gl_vtable;

  gl->BindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
  gl->BindBuffer (GL_ARRAY_BUFFER, 0);

  gl->DisableVertexAttribArray (shader_attr_position_loc);
  gl->DisableVertexAttribArray (shader_attr_texture_loc);
}

static void
init_blit (gpointer data)
{
  GstGLContext *context = data;
  const GstGLFuncs *gl = context->gl_vtable;

  if (!vbo) {
    if (gl->GenVertexArrays) {
      gl->GenVertexArrays (1, &vao);
      gl->BindVertexArray (vao);
    }

    gl->GenBuffers (1, &vbo);
    gl->BindBuffer (GL_ARRAY_BUFFER, vbo);
    gl->BufferData (GL_ARRAY_BUFFER, 4 * 5 * sizeof (GLfloat), vertices,
        GL_STATIC_DRAW);

    gl->GenBuffers (1, &vbo_indices);
    gl->BindBuffer (GL_ELEMENT_ARRAY_BUFFER, vbo_indices);
    gl->BufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof (indices), indices,
        GL_STATIC_DRAW);

    if (gl->GenVertexArrays) {
      _bind_buffer (context);
      gl->BindVertexArray (0);
    }

    gl->BindBuffer (GL_ARRAY_BUFFER, 0);
    gl->BindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
  }
}

static void
deinit_blit (gpointer data)
{
  GstGLContext *context = data;
  const GstGLFuncs *gl = context->gl_vtable;

  if (vbo)
    gl->DeleteBuffers (1, &vbo);
  vbo = 0;
  if (vbo_indices)
    gl->DeleteBuffers (1, &vbo_indices);
  vbo_indices = 0;
  if (vao)
    gl->DeleteVertexArrays (1, &vao);
  vao = 0;
}

static void
draw_render (gpointer data)
{
  GstGLContext *context = data;
  GstGLContextClass *context_class = GST_GL_CONTEXT_GET_CLASS (context);
  const GstGLFuncs *gl = context->gl_vtable;

  gl->Clear (GL_COLOR_BUFFER_BIT);

  gst_gl_shader_use (shader);

  gl->ActiveTexture (GL_TEXTURE0);
  gl->BindTexture (GL_TEXTURE_2D, tex);
  gst_gl_shader_set_uniform_1i (shader, "s_texture", 0);

  if (gl->GenVertexArrays)
    gl->BindVertexArray (vao);
  else
    _bind_buffer (context);

  gl->DrawElements (GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

  if (gl->GenVertexArrays)
    gl->BindVertexArray (0);
  else
    _unbind_buffer (context);

  context_class->swap_buffers (context);
}

GST_START_TEST (test_share)
{
  GstGLContext *context;
  GstGLWindow *window;
  GstGLContext *other_context;
  GstGLWindow *other_window;
  GError *error = NULL;
  gint i = 0;

  context = gst_gl_context_new (display);

  window = gst_gl_window_new (display);
  gst_gl_context_set_window (context, window);

  gst_gl_context_create (context, 0, &error);

  fail_if (error != NULL, "Error creating master context %s\n",
      error ? error->message : "Unknown Error");

  other_window = gst_gl_window_new (display);

  other_context = gst_gl_context_new (display);
  gst_gl_context_set_window (other_context, other_window);

  gst_gl_context_create (other_context, context, &error);

  fail_if (error != NULL, "Error creating secondary context %s\n",
      error ? error->message : "Unknown Error");

  /* make the window visible */
  gst_gl_window_set_preferred_size (window, 320, 240);
  gst_gl_window_draw (window);

  gst_gl_window_send_message (other_window, GST_GL_WINDOW_CB (init), context);
  gst_gl_window_send_message (window, GST_GL_WINDOW_CB (init_blit), context);

  while (i < 10) {
    gst_gl_window_send_message (other_window, GST_GL_WINDOW_CB (draw_tex),
        context);
    gst_gl_window_send_message (window, GST_GL_WINDOW_CB (draw_render),
        context);
    i++;
  }

  gst_gl_window_send_message (other_window, GST_GL_WINDOW_CB (deinit), context);
  gst_gl_window_send_message (window, GST_GL_WINDOW_CB (deinit_blit), context);

  gst_object_unref (window);
  gst_object_unref (other_window);
  gst_object_unref (other_context);
  gst_object_unref (context);
}

GST_END_TEST;

static void
accum_true (GstGLContext * context, gpointer data)
{
  gint *i = data;
  *i = 1;
}

static void
check_wrapped (gpointer data)
{
  GstGLContext *wrapped_context = data;
  GError *error = NULL;
  gint i = 0;
  gboolean ret;

  /* check that scheduling on an unactivated wrapped context asserts */
  ASSERT_CRITICAL (gst_gl_context_thread_add (wrapped_context,
          (GstGLContextThreadFunc) accum_true, &i));
  fail_if (i != 0);

  /* check that scheduling on an activated context succeeds */
  gst_gl_context_activate (wrapped_context, TRUE);
  gst_gl_context_thread_add (wrapped_context,
      (GstGLContextThreadFunc) accum_true, &i);
  fail_if (i != 1);

  /* check filling out the wrapped context's info */
  fail_if (wrapped_context->gl_vtable->TexImage2D != NULL);
  ret = gst_gl_context_fill_info (wrapped_context, &error);
  fail_if (!ret, "error received %s\n",
      error ? error->message : "Unknown error");
  fail_if (wrapped_context->gl_vtable->TexImage2D == NULL);
  gst_gl_context_activate (wrapped_context, FALSE);
}

GST_START_TEST (test_wrapped_context)
{
  GstGLContext *context, *other_context, *wrapped_context;
  GstGLWindow *window, *other_window;
  GError *error = NULL;
  gint i = 0;
  guintptr handle, handle2;
  GstGLPlatform platform, platform2;
  GstGLAPI apis, apis2;

  context = gst_gl_context_new (display);

  window = gst_gl_window_new (display);
  gst_gl_context_set_window (context, window);

  gst_gl_context_create (context, 0, &error);

  fail_if (error != NULL, "Error creating master context %s\n",
      error ? error->message : "Unknown Error");

  handle = gst_gl_context_get_gl_context (context);
  platform = gst_gl_context_get_gl_platform (context);
  apis = gst_gl_context_get_gl_api (context);

  wrapped_context =
      gst_gl_context_new_wrapped (display, handle, platform, apis);

  handle2 = gst_gl_context_get_gl_context (wrapped_context);
  platform2 = gst_gl_context_get_gl_platform (wrapped_context);
  apis2 = gst_gl_context_get_gl_api (wrapped_context);

  fail_if (handle != handle2);
  fail_if (platform != platform2);
  fail_if (apis != apis2);

  other_context = gst_gl_context_new (display);
  other_window = gst_gl_window_new (display);
  gst_gl_context_set_window (other_context, other_window);

  gst_gl_context_create (other_context, wrapped_context, &error);

  fail_if (error != NULL, "Error creating secondary context %s\n",
      error ? error->message : "Unknown Error");

  /* make the window visible */
  gst_gl_window_set_preferred_size (window, 320, 240);
  gst_gl_window_draw (window);

  gst_gl_window_send_message (other_window, GST_GL_WINDOW_CB (init), context);
  gst_gl_window_send_message (window, GST_GL_WINDOW_CB (init_blit), context);

  while (i < 10) {
    gst_gl_window_send_message (other_window, GST_GL_WINDOW_CB (draw_tex),
        context);
    gst_gl_window_send_message (window, GST_GL_WINDOW_CB (draw_render),
        context);
    i++;
  }

  gst_gl_window_send_message (window, GST_GL_WINDOW_CB (check_wrapped),
      wrapped_context);

  gst_gl_window_send_message (other_window, GST_GL_WINDOW_CB (deinit), context);
  gst_gl_window_send_message (window, GST_GL_WINDOW_CB (deinit_blit), context);

  gst_object_unref (other_context);
  gst_object_unref (other_window);
  gst_object_unref (window);
  gst_object_unref (context);
  gst_object_unref (wrapped_context);
}

GST_END_TEST;

struct context_info
{
  GstGLAPI api;
  guint major;
  guint minor;
  GstGLPlatform platform;
  guintptr handle;
};

static void
_fill_context_info (GstGLContext * context, struct context_info *info)
{
  info->handle = gst_gl_context_get_current_gl_context (info->platform);
  info->api =
      gst_gl_context_get_current_gl_api (info->platform, &info->major,
      &info->minor);
}

GST_START_TEST (test_current_context)
{
  GstGLContext *context;
  GError *error = NULL;
  guintptr handle;
  GstGLPlatform platform;
  GstGLAPI api;
  gint major, minor;
  struct context_info info;

  context = gst_gl_context_new (display);

  gst_gl_context_create (context, 0, &error);

  fail_if (error != NULL, "Error creating master context %s\n",
      error ? error->message : "Unknown Error");

  handle = gst_gl_context_get_gl_context (context);
  platform = gst_gl_context_get_gl_platform (context);
  api = gst_gl_context_get_gl_api (context);
  gst_gl_context_get_gl_version (context, &major, &minor);

  info.platform = platform;

  gst_gl_context_thread_add (context,
      (GstGLContextThreadFunc) _fill_context_info, &info);

  fail_if (info.platform != platform);
  fail_if (info.api != api);
  fail_if (info.major != major);
  fail_if (info.minor != minor);
  fail_if (info.handle != handle);

  gst_object_unref (context);
}

GST_END_TEST;

GST_START_TEST (test_context_can_share)
{
  GstGLContext *c1, *c2, *c3;
  GError *error = NULL;

  c1 = gst_gl_context_new (display);
  gst_gl_context_create (c1, NULL, &error);
  fail_if (error != NULL, "Error creating context %s\n",
      error ? error->message : "Unknown Error");

  c2 = gst_gl_context_new (display);
  gst_gl_context_create (c2, c1, &error);
  fail_if (error != NULL, "Error creating context %s\n",
      error ? error->message : "Unknown Error");

  fail_unless (gst_gl_context_can_share (c1, c2));
  fail_unless (gst_gl_context_can_share (c2, c1));

  c3 = gst_gl_context_new (display);
  gst_gl_context_create (c3, c2, &error);
  fail_if (error != NULL, "Error creating context %s\n",
      error ? error->message : "Unknown Error");

  fail_unless (gst_gl_context_can_share (c1, c3));
  fail_unless (gst_gl_context_can_share (c3, c1));
  fail_unless (gst_gl_context_can_share (c2, c3));
  fail_unless (gst_gl_context_can_share (c3, c2));

  /* destroy the middle context */
  gst_object_unref (c2);
  c2 = NULL;

  fail_unless (gst_gl_context_can_share (c1, c3));
  fail_unless (gst_gl_context_can_share (c3, c1));

  gst_object_unref (c1);
  gst_object_unref (c3);
}

GST_END_TEST;

GST_START_TEST (test_is_shared)
{
  GstGLContext *c1, *c2;
  GError *error = NULL;

  c1 = gst_gl_context_new (display);
  gst_gl_context_create (c1, NULL, &error);
  fail_if (error != NULL, "Error creating context %s\n",
      error ? error->message : "Unknown Error");

  c2 = gst_gl_context_new (display);
  gst_gl_context_create (c2, c1, &error);
  fail_if (error != NULL, "Error creating context %s\n",
      error ? error->message : "Unknown Error");

  fail_unless (gst_gl_context_is_shared (c1));
  fail_unless (gst_gl_context_is_shared (c2));

  gst_object_unref (c2);
  c2 = NULL;

  fail_unless (!gst_gl_context_is_shared (c1));

  gst_object_unref (c1);
}

GST_END_TEST;

GST_START_TEST (test_display_list)
{
  GstGLContext *c1, *c2;
  GError *error = NULL;

  c1 = gst_gl_context_new (display);
  gst_gl_context_create (c1, NULL, &error);
  fail_if (error != NULL, "Error creating context %s\n",
      error ? error->message : "Unknown Error");

  GST_OBJECT_LOCK (display);
  {
    /* no context added so get should return NULL */
    GstGLContext *tmp =
        gst_gl_display_get_gl_context_for_thread (display, NULL);
    fail_unless (tmp == NULL);
  }

  fail_unless (gst_gl_display_add_context (display, c1));
  /* re-adding the same context is a no-op */
  fail_unless (gst_gl_display_add_context (display, c1));

  {
    GThread *thread;
    GstGLContext *tmp;

    thread = gst_gl_context_get_thread (c1);
    fail_unless (thread != NULL);

    tmp = gst_gl_display_get_gl_context_for_thread (display, thread);
    fail_unless (tmp == c1);
    g_thread_unref (thread);
    gst_object_unref (tmp);

    tmp = gst_gl_display_get_gl_context_for_thread (display, NULL);
    fail_unless (tmp == c1);
    gst_object_unref (tmp);
  }

  c2 = gst_gl_context_new (display);
  gst_gl_context_create (c2, c1, &error);
  fail_if (error != NULL, "Error creating context %s\n",
      error ? error->message : "Unknown Error");

  fail_unless (gst_gl_display_add_context (display, c2));
  /* re-adding the same context is a no-op */
  fail_unless (gst_gl_display_add_context (display, c2));

  {
    GThread *thread;
    GstGLContext *tmp;

    thread = gst_gl_context_get_thread (c2);
    fail_unless (thread != NULL);

    tmp = gst_gl_display_get_gl_context_for_thread (display, thread);
    fail_unless (tmp == c2);
    g_thread_unref (thread);
    gst_object_unref (tmp);

    /* undefined which context will be returned for the NULL thread */
    tmp = gst_gl_display_get_gl_context_for_thread (display, NULL);
    fail_unless (tmp != NULL);
    gst_object_unref (tmp);
  }

  gst_object_unref (c1);
  /* c1 is now dead */

  {
    GstGLContext *tmp;

    tmp = gst_gl_display_get_gl_context_for_thread (display, NULL);
    fail_unless (tmp == c2);
    gst_object_unref (tmp);
  }
  GST_OBJECT_UNLOCK (display);

  gst_object_unref (c2);
  /* c2 is now dead */

  {
    /* no more contexts alive */
    GstGLContext *tmp =
        gst_gl_display_get_gl_context_for_thread (display, NULL);
    fail_unless (tmp == NULL);
  }
}

GST_END_TEST;

static Suite *
gst_gl_context_suite (void)
{
  Suite *s = suite_create ("GstGLContext");
  TCase *tc_chain = tcase_create ("general");

  suite_add_tcase (s, tc_chain);
  tcase_add_checked_fixture (tc_chain, setup, teardown);
  tcase_add_test (tc_chain, test_share);
  tcase_add_test (tc_chain, test_wrapped_context);
  tcase_add_test (tc_chain, test_current_context);
  tcase_add_test (tc_chain, test_context_can_share);
  tcase_add_test (tc_chain, test_is_shared);
  tcase_add_test (tc_chain, test_display_list);

  return s;
}

GST_CHECK_MAIN (gst_gl_context);