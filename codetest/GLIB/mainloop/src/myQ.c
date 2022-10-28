#include <glib.h>

static GThread *my_thread;
static GMainLoop *my_loop;

static gboolean 
idle_thread(gpointer data){
    g_usleep(1000000);
    g_printf("idle thread called\n");
    return TRUE;
}
static gboolean 
timeout_callback(gpointer data){
    printf("timeout_callback called\n");
    return TRUE;
}

static void
add_idle_to_my_thread (GSourceFunc    func,
                       gpointer       data)
{
  GSource *src;

  src = g_idle_source_new ();
  g_source_set_callback (src, func, data, NULL);
  g_source_attach (src,
                   g_main_loop_get_context (my_loop));
  g_source_unref (src);
}

static void
add_timeout_to_my_thread (guint          interval,
                          GSourceFunc    func,
                          gpointer       data)
{
  GSource *src;

  src = g_timeout_source_new (interval);
  g_source_set_callback (src, func, data, NULL);
  g_source_attach (src,
                   g_main_loop_get_context (my_loop));
  g_source_unref (src);
}

static gpointer
loop_func (gpointer data)
{
  GMainLoop *loop = data;

  g_main_loop_run (loop);

  return NULL;
}

static void
start_my_thread (void)
{
  GMainContext *context;

  context = g_main_context_new ();
  my_loop = g_main_loop_new (context, FALSE);
  g_main_context_unref (context);

  my_thread = g_thread_create (loop_func, my_loop, TRUE, NULL);
}

static void
stop_my_thread (void)
{
  g_main_loop_quit (my_loop);
  g_thread_join (my_thread);
  g_main_loop_unref (my_loop);
}

int main(void)
{
	start_my_thread();
	add_idle_to_my_thread(idle_thread,NULL);
	add_timeout_to_my_thread(5000,timeout_callback,NULL);
	while(my_loop);
	return 0;
}

