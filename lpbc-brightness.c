#include <stdio.h>
#include <stdlib.h>

#include "lpbc-brightness.h"

long
lpbc_brightness_get (void)
{
  FILE *fp;
  char brightness[1035];
  fp = popen ("xbacklight", "r");

  if (NULL == fp) {
    printf ("Failed to run command\n" );
    return 0;
  }

  if (fgets(brightness, sizeof(brightness) - 1, fp) == NULL) {
    printf ("Failed to get brightness\n");
    return 0;
  }

  long val = strtol(brightness, NULL, 10);

  pclose (fp);

  return val;
}

void
lpbc_brightness_raise (void)
{
  FILE *f = popen ("xbacklight -inc 10", "r");
  if (NULL == f) {
    return;
  }
  pclose (f);
}

void
lpbc_brightness_lower (void)
{
  FILE *f = popen ("xbacklight -dec 10", "r");
  if (NULL == f) {
    return;
  }
  pclose (f);
}
