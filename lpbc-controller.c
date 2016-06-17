#include <lxpanel/plugin.h>

#include "lpbc-event-box.h"
#include "lpbc-label.h"
#include "lpbc-controller.h"
#include "lpbc-brightness.h"
#include "lpbc-keybinder.h"

static void
lpbc_controller_update (LPBCController *controller)
{
    long brightness = lpbc_brightness_get();
    lpbc_label_set_brightness(controller->label, brightness);
}

static gboolean
lpbc_controller_on_update (gpointer user_data)
{
  LPBCController *controller = user_data;
  lpbc_controller_update(controller);
  return TRUE;
}

static void
lpbc_controller_init_module (void)
{
  static gboolean did_init = FALSE;
  if (!did_init) {
    lpbc_keybinder_init();
    did_init = TRUE;
  }
}

static void
lpbc_controller_destroy (LPBCController *controller)
{
  lpbc_keybinder_unbind();
  g_source_remove(controller->timeout_id);
}

static void
lpbc_controller_init (LPBCController *controller)
{
  lpbc_keybinder_bind();
  g_signal_connect(controller->event_box, "destroy", G_CALLBACK(lpbc_controller_destroy), NULL);
  controller->timeout_id = g_timeout_add(1000, lpbc_controller_on_update, controller);
  lpbc_controller_update(controller);
}

LPBCController *
lpbc_controller_new (void)
{
  LPBCController *controller  = g_new0(LPBCController, 1);
  GtkWidget      *label       = lpbc_label_new();
  GtkWidget      *event_box   = lpbc_event_box_new(label);

  controller->label = label;
  controller->event_box = event_box;

  lpbc_controller_init_module();
  lpbc_controller_init(controller);
  lxpanel_plugin_set_data(controller->event_box, controller, g_free);

  return controller;
}

GtkWidget *
lpbc_controller_get_widget (LPBCController *controller)
{
  return controller->event_box;
}
