#include "AvatarMath.h"

static bool s_useRandomHW = true;


long m5avatar::random( long howbig )
{
  if ( howbig == 0 )
  {
    return 0 ;
  }
  if (howbig < 0) {
    return (m5avatar::random(0, -howbig));
  }
  // if randomSeed was called, fall back to software PRNG
  uint32_t val = (s_useRandomHW) ? esp_random() : rand();
  return val % howbig;
}

long m5avatar::random(long howsmall, long howbig)
{
    if(howsmall >= howbig) {
        return howsmall;
    }
    long diff = howbig - howsmall;
    return m5avatar::random(diff) + howsmall;
}

