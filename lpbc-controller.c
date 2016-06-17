#include <lxpanel/plugin.h>

#include "lpbc-event-box.h"
#include "lpbc-label.h"
#include "lpbc-controller.h"
#include "lpbc-brightness.h"
#include "lpbc-keybinder.h"
#include "lpbc-popup.h"
#include "lpbc-scale.h"

static GQuark
lpbc_controller_get_quark (void)
{
  return g_quark_from_static_string("lpbc-controller");
}

static void
lpbc_controller_update (LPBCController *controller)
{
    long brightness = lpbc_brightness_get ();
    lpbc_label_set_brightness (controller->label, brightness);
    if(controller->scale) {
      gtk_range_set_value (GTK_RANGE(controller->scale), brightness);
    }
}

static gboolean
lpbc_controller_on_update (gpointer user_data)
{
  LPBCController *controller = user_data;
  lpbc_controller_update (controller);
  return TRUE;
}

static void
lpbc_controller_init_module (void)
{
  static gboolean did_init = FALSE;
  if (!did_init) {
    lpbc_keybinder_init ();
    did_init = TRUE;
  }
}

static void
lpbc_controller_destroy (gpointer data)
{
  LPBCController * controller = data;
  lpbc_keybinder_unbind ();
  g_source_remove (controller->timeout_id);
  g_free (controller);
}

static void
lpbc_controller_init (LPBCController *controller)
{
  lpbc_keybinder_bind ();
  controller->timeout_id = g_timeout_add (1000, lpbc_controller_on_update, controller);
  lpbc_controller_update (controller);
}

static void
lpbc_controller_bind (LPBCController *controller)
{
  g_object_set_qdata_full (
    G_OBJECT (controller->event_box),
    lpbc_controller_get_quark (),
    controller,
    lpbc_controller_destroy
  );
}

LPBCController *
lpbc_controller_new (void)
{
  LPBCController *controller  = g_new0 (LPBCController, 1);
  GtkWidget      *label       = lpbc_label_new ();
  GtkWidget      *event_box   = lpbc_event_box_new (label);

  controller->label = label;
  controller->event_box = event_box;

  lpbc_controller_init_module ();
  lpbc_controller_init (controller);
  lpbc_controller_bind (controller);

  return controller;
}

LPBCController *
lpbc_controller_get_from_widget (GtkWidget *widget)
{
  LPBCController *controller = g_object_get_qdata (G_OBJECT (widget), lpbc_controller_get_quark ());
  return controller;
}

GtkWidget *
lpbc_controller_get_widget (LPBCController *controller)
{
  return controller->event_box;
}

static void
lpbc_controller_create_popup (LPBCController *controller)
{
  GtkWidget *popup = lpbc_popup_new ();
  GtkWidget *scale = lpbc_scale_new ();
  controller->popup = popup;
  controller->scale = scale;
  gtk_container_add (GTK_CONTAINER (popup), scale);
  lxpanel_plugin_adjust_popup_position (GTK_WIDGET (popup), controller->event_box);
  lpbc_controller_update (controller);
}

static void
lpbc_contoller_destroy_popup (LPBCController *controller)
{
  gtk_widget_destroy (GTK_WIDGET (controller->popup));
  controller->popup = NULL;
  controller->scale = NULL;
}

void
lpbc_controller_toggle_popup (LPBCController *controller)
{
  if (NULL == controller->popup) {
    lpbc_controller_create_popup (controller);
  } else {
    lpbc_contoller_destroy_popup (controller);
  }
}
