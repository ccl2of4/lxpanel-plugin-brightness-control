#include <lxpanel/plugin.h>
#include "lpbc-scale.h"

GtkWidget *
lpbc_scale_new (void)
{
  GtkWidget *scale = gtk_vscale_new_with_range (0, 100, 10);
  gtk_widget_show (scale);
  return scale;
}
