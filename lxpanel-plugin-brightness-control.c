#include <lxpanel/plugin.h>
#include <stdlib.h>
#include <stdio.h>

static gboolean update_label(gpointer data) {
  GtkWidget *label = data;

  FILE *fp;
  char brightness[1035];
  fp = popen("xbacklight", "r");
  if (NULL == fp) {
    printf("Failed to run command\n" );
    exit(1);
  }
  /* Read the output a line at a time - output it. */
  if (fgets(brightness, sizeof(brightness) - 1, fp) == NULL) {
    printf("Failed to get brightness\n");
  }

  long val = strtol(brightness, NULL, 10);

  /* close */
  pclose(fp);

  char brightnessBuf[10] = {'\0'};
  snprintf(brightnessBuf, sizeof(brightnessBuf), "%ld", val);
  gtk_label_set_text(GTK_LABEL(label), brightnessBuf);

  return 1;
}

GtkWidget *new_instance(LXPanel *panel, config_setting_t *settings)
{
 /* panel is a pointer to the panel and
     settings is a pointer to the configuration data
     since we don't use it, we'll make sure it doesn't
     give us an error at compilation time */
 (void)panel;
 (void)settings;



 char brightnessBuf[10] = {'\0'};

 snprintf(brightnessBuf, sizeof(brightnessBuf), "%s", "100");

 // label
 GtkWidget *label = gtk_label_new(brightnessBuf);
 gtk_widget_show(label);

 // event box
 GtkWidget *eventBox = gtk_event_box_new();
 gtk_widget_set_has_window(eventBox, FALSE);
 gtk_container_set_border_width(GTK_CONTAINER(eventBox), 1);

 // add label to event box
 gtk_container_add(GTK_CONTAINER(eventBox), label);

 // set the size we want
 gtk_widget_set_size_request(eventBox, 25, 25);

 g_timeout_add(20, update_label, label);

 // success!!!
 return eventBox;
}

FM_DEFINE_MODULE(lxpanel_gtk, lxpanel-plugin-xbacklight)

/* Plugin descriptor. */
LXPanelPluginInit fm_module_init_lxpanel_gtk = {
   .name = "Brightness Control",
   .description = "Controls screen brightness using xbacklight",

   // assigning our functions to provided pointers.
   .new_instance = new_instance
};
