#ifndef WaveBlenderH
#define WaveBlenderH

#include <Abstract/AbstractPatch.h>
#include <Storage/FlashSettings.h>

#include <Remember.h>
#include <Sound/WaveTable.h>

#include "CustomTable.h"
#include "RandomWalkTables.h"

class WaveBlender : public Abstract::Patch, public FlashSettings
{
public:
   WaveBlender();

private:
   void audioLoop(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size) override;
   void nonAudioLoop() override;

private: // things to remember
   using CustomTableArray_ = Remember::RefArray<CustomTable, 4>;

private:
   WaveTable::Oscilator oscilators[4];
   RandomWalkTables randomWalkTables;
   CustomTableArray_ tables;
};

#endif // WaveBlenderH
