#include <lxpanel/plugin.h>
#include "lpbc-scale.h"

GtkWidget *
lpbc_scale_new (void)
{
  GtkWidget *scale = gtk_hscale_new_with_range (0, 100, 10);
  gtk_scale_set_draw_value (GTK_SCALE (scale), FALSE);
  gtk_widget_show (scale);
  return scale;
}
