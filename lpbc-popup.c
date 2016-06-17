#include <lxpanel/plugin.h>
#include "lpbc-popup.h"

GtkWidget *
lpbc_popup_new (void)
{
  GtkWidget *popup = gtk_window_new (GTK_WINDOW_POPUP);
  gtk_widget_show (popup);
  return popup;
}
