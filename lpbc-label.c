#include <lxpanel/plugin.h>

#include "lpbc-label.h"

GtkWidget *
lpbc_label_new (void)
{
  GtkWidget *label = gtk_label_new (NULL);
  gtk_widget_show (label);
  return label;
}

void
lpbc_label_set_brightness (GtkWidget *label, int brightness)
{
  char brightness_str[10] = {'\0'};
  snprintf(brightness_str, sizeof(brightness_str), "%d", brightness);
  gtk_label_set_text (GTK_LABEL (label), brightness_str);
}
