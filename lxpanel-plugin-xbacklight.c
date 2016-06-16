#include <lxpanel/plugin.h>

#include <stdio.h>

// internal to the plugin source, not used by the 'priv' variable
static int iInstanceCount = 0;

/* the plugin's id – an instance of this struct
   is what will be assigned to 'priv' */
typedef struct
{
  gint iMyId;
} TestPlugin;

GtkWidget *test_constructor(LXPanel *panel, config_setting_t *settings)
{
 /* panel is a pointer to the panel and
     settings is a pointer to the configuration data
     since we don't use it, we'll make sure it doesn't
     give us an error at compilation time */
 (void)panel;
 (void)settings;

 // allocate our private structure instance
 TestPlugin *pTest = g_new0(TestPlugin, 1);

 // update the instance count
 pTest->iMyId = ++iInstanceCount;

 // make a label out of the ID
 char cIdBuf[10] = {'\0'};

 snprintf(cIdBuf, sizeof(cIdBuf), "TP-%d", pTest->iMyId);

 // create a label widget instance
 GtkWidget *pLabel = gtk_label_new(cIdBuf);

 // set the label to be visible
 gtk_widget_show(pLabel);

 // need to create a container to be able to set a border
 GtkWidget *p = gtk_event_box_new();

 // our widget doesn't have a window...
 // it is usually illegal to call gtk_widget_set_has_window() from application but for GtkEventBox it doesn't hurt
 gtk_widget_set_has_window(p, FALSE);

 // bind private structure to the widget assuming it should be freed using g_free()
 lxpanel_plugin_set_data(p, pTest, g_free);

 // set border width
 gtk_container_set_border_width(GTK_CONTAINER(p), 1);

 // add the label to the container
 gtk_container_add(GTK_CONTAINER(p), pLabel);

 // set the size we want
 gtk_widget_set_size_request(p, 40, 25);

 // success!!!
 return p;
}

FM_DEFINE_MODULE(lxpanel_gtk, test)

/* Plugin descriptor. */
LXPanelPluginInit fm_module_init_lxpanel_gtk = {
   .name = "TestPlugin",
   .description = "Run a test plugin.",

   // assigning our functions to provided pointers.
   .new_instance = test_constructor
};
