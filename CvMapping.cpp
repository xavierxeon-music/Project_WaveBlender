#include "CvMapping.h"

#include <Tools/Range.h>

#include "WaveBlender.h"

CvMapping::CvMapping()
   : Remember::Container()
   , sums()
   , bitField(this, 0)
{
}

void CvMapping::apply(const float knobs[4])
{
   for (uint8_t type = 0; type < 4; type++)
   {
      Sum& sum = sums[type];
      sum.value = 0.0;
      sum.active = false;

      for (uint8_t channel = 0; channel < 4; channel++)
      {
         if (!get(static_cast<Type>(type), channel))
            continue;

         sum.value += knobs[channel];
         sum.active = true;
      }

      sum.value = Range::clamp<float>(sum.value, 0.0, 1.0);
   }
}

CvMapping::Sum CvMapping::sum(const Type& type)
{
   return sums[type];
}

void CvMapping::set(const Type& type, const uint8_t& channel, bool on)
{
   const uint16_t mask = 1 << ((4 * type) + channel);
   if (on)
      bitField = (mask | bitField);
   else
      bitField = (~mask & bitField);

   Remember::Root::setUnsynced();
}

bool CvMapping::get(const Type& type, const uint8_t& channel) const
{
   const uint16_t mask = 1 << ((4 * type) + channel);
   bool test = ((mask & bitField) == mask);

   return test;
}
