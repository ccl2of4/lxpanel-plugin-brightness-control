#include "lpbc-event-box.h"
#include <lxpanel/plugin.h>

GtkWidget *
lpbc_event_box_new (GtkWidget *label)
{
  GtkWidget *event_box = gtk_event_box_new ();
  gtk_widget_set_has_window (event_box, FALSE);
  gtk_container_set_border_width (GTK_CONTAINER (event_box), 1);
  gtk_container_add (GTK_CONTAINER (event_box), label);
  gtk_widget_set_size_request (event_box, 25, 25);
  return event_box;
}
