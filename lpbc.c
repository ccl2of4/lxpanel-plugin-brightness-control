#include <stdio.h>
#include <stdlib.h>
#include <lxpanel/plugin.h>

#include "lpbc-label.h"
#include "lpbc-event-box.h"
#include "lpbc-controller.h"

FM_DEFINE_MODULE(lxpanel_gtk, lxpanel-plugin-xbacklight);

GtkWidget *new_instance (LXPanel *panel, config_setting_t *settings)
{
  LPBCController *controller = lpbc_controller_new();
  GtkWidget      *widget     = lpbc_controller_get_widget(controller);
  return widget;
}

/* Plugin descriptor. */
LXPanelPluginInit fm_module_init_lxpanel_gtk = {
   .name           = "Brightness Control",
   .description    = "Controls screen brightness using xbacklight",
   .one_per_system = TRUE,
   .new_instance   = new_instance
};
