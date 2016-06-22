#include <stdio.h>
#include <stdlib.h>
#include <lxpanel/plugin.h>

#include "lpbc-controller.h"

FM_DEFINE_MODULE(lxpanel_gtk, lxpanel-plugin-xbacklight);

GtkWidget *
new_instance (LXPanel *panel, config_setting_t *settings)
{
  LPBCController *controller = lpbc_controller_new ();
  GtkWidget      *widget     = lpbc_controller_get_widget (controller);
  return widget;
}

gboolean
button_press_event (GtkWidget *widget, GdkEventButton *event, LXPanel *panel)
{
  LPBCController *controller = lpbc_controller_get_from_widget (widget);
  lpbc_controller_toggle_popup (controller);
  return TRUE;
}

/* Plugin descriptor. */
LXPanelPluginInit fm_module_init_lxpanel_gtk = {
   .name               = "Brightness Control",
   .description        = "Controls screen brightness using xbacklight",
   .one_per_system     = TRUE,
   .new_instance       = new_instance,
   .button_press_event = button_press_event
};
