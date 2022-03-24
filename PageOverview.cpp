#include "PageOverview.h"

#include "RandomWalkTables.h"

const Range::Mapper PageOverview::amplitudeMapper(-1.0, 1.0, 30.0, 0.0);
const Range::Mapper PageOverview::seedMapper(0, RandomWalkTables::maxSeed, 0.0, 63.0);
const Range::Mapper PageOverview::blendMapper(0, 1.0, 30.0, 0.0);

PageOverview::PageOverview(CustomTable** tableArray)
   : Abstract::Page::Base()
   , tableArray{tableArray[0], tableArray[1], tableArray[2], tableArray[3]}
{
}

void PageOverview::render(OledDisplay* display)
{
   static const float maxAngle = 4.0f * Maths::pi;
   static const float anglePerStep = maxAngle / static_cast<float>(63);

   for (uint8_t channel = 0; channel < 4; channel++)
   {
      uint8_t lastY = 0;
      for (uint8_t x = 0; x < 63; x++)
      {
         uint8_t xDraw = x;
         if (1 == channel || 3 == channel)
            xDraw += 63;

         const float angle = x * anglePerStep;
         const float& value = tableArray[channel]->valueByAngle(angle);
         uint8_t y = 2 + static_cast<uint8_t>(amplitudeMapper(value));
         if (2 == channel || 3 == channel)
            y += 32;

         if (0 != x)
            display->DrawLine(xDraw - 1, lastY, xDraw, y, White);

         lastY = y;
      }
   }
   display->DrawLine(0, 32, width, 32, White);
   display->DrawLine(63, 0, 63, 64, White);
}

Abstract::Page::State PageOverview::clicked()
{
   return State::Turn;
}
