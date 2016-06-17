#ifndef __LPBC_CONTROLLER_H__
#define __LPBC_CONTROLLER_H__

#include <lxpanel/plugin.h>

typedef struct {
  guint timeout_id;
  GtkWidget *event_box;
  GtkWidget *label;
  GtkWidget *popup;
  GtkWidget *scale;
} LPBCController;

LPBCController * lpbc_controller_new (void);
LPBCController * lpbc_controller_get_from_widget (GtkWidget *);
GtkWidget * lpbc_controller_get_widget (LPBCController *);
void lpbc_controller_toggle_popup (LPBCController *);

#endif /* __LPBC_CONTROLLER_H__ */
