#ifndef __LPBC_BRIGHTNESS_H__
#define __LPBC_BRIGHTNESS_H__

#include <stdbool.h>

long lpbc_brightness_get (void);
void lpbc_brightness_raise (bool async);
void lpbc_brightness_lower (bool async);
void lpbc_brightness_set (double brightness, bool async);

#endif /* __LPBC_BRIGHTNESS_H__ */
