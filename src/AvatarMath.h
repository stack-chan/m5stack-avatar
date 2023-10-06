// for ESP-IDF

#ifndef _AVATAR_MATH_H_
#define _AVATAR_MATH_H_

#include <stdlib.h>
#include "esp_random.h"

namespace m5avatar {


#define _min(a,b) ((a)<(b)?(a):(b))  

long random(long howbig);
long random(long howsmall, long howbig);

} // namespace m5avatar
#endif // _AVATAR_MATH_H_