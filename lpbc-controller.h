#ifndef __LPBC_CONTROLLER_H__
#define __LPBC_CONTROLLER_H__

#include <lxpanel/plugin.h>

typedef struct {
  guint timeout_id;
  GtkWidget *event_box;
  GtkWidget *label;
} LPBCController;

LPBCController * lpbc_controller_new (void);
GtkWidget * lpbc_controller_get_widget (LPBCController *);

#endif /* __LPBC_CONTROLLER_H__ */
