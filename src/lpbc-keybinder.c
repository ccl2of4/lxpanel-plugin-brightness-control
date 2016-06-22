#include <stdio.h>
#include <stdlib.h>
#include <keybinder.h>

#include "lpbc-keybinder.h"
#include "lpbc-brightness.h"

void
lpbc_keybinder_init (void)
{
  keybinder_init();
}

static void
raise_brightness (const char *keystring, void *user_data)
{
  lpbc_brightness_raise (false);
}

static void
lower_brightness (const char *keystring, void *user_data)
{
  lpbc_brightness_lower (false);
}

gboolean
lpbc_keybinder_bind (void)
{
  return keybinder_bind ("XF86MonBrightnessUp", raise_brightness, NULL)
      && keybinder_bind ("XF86MonBrightnessDown", lower_brightness, NULL);
}

void
lpbc_keybinder_unbind (void)
{
  keybinder_unbind ("XF86MonBrightnessUp", raise_brightness);
  keybinder_unbind ("XF86MonBrightnessDown", lower_brightness);
}
