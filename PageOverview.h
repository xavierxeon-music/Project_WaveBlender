#ifndef PageOverviewH
#define PageOverviewH

#include <Abstract/AbstractPageBase.h>

#include <Tools/Range.h>

#include "CustomTable.h"

class PageOverview : public Abstract::Page::Base
{
public:
   PageOverview(CustomTable** tableArray);

private:
   void render(OledDisplay* display) override;
   State clicked() override;

private:
   CustomTable* tableArray[4];
   static const Range::Mapper amplitudeMapper;
   static const Range::Mapper seedMapper;
   static const Range::Mapper blendMapper;
};

#endif // PageOverviewH
