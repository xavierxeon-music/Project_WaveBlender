#include "CustomTable.h"

#include <Tools/Variable.h>

#include "RandomWalkTables.h"
#include "WaveBlender.h"

const uint8_t CustomTable::maxBlend = 63;

CustomTable::CustomTable()
   : WaveTable::Table(2 * 2.0f * Maths::pi)
   , Remember::Container()
   , cvMapping(this)
   , waveform(this, Standard::Waveform::Sine)
   , offsetVoltage(this, 0.0)
   , seed(this, 0)
   , seedInternal{0}
   , blend(this, 0)
   , blendInternal{0.0}
   , randomWalkTables(nullptr)
{
   seedInternal = seed;
   blendInternal = static_cast<float>(blend) / static_cast<float>(maxBlend);
}

void CustomTable::init(RandomWalkTables* randomWalkTables)
{
   seedInternal = seed;
   blendInternal = static_cast<float>(blend) / static_cast<float>(maxBlend);

   this->randomWalkTables = randomWalkTables;
}

CvMapping* CustomTable::getCvMapping()
{
   return cvMapping;
}

float CustomTable::setCvAndGetFrequency(const float controlVoltages[4])
{
   cvMapping->apply(controlVoltages);

   const float voltage = (cvMapping->sum(CvMapping::Pitch).value) + offsetVoltage;
   const float frequency = WaveTable::Oscilator::frequencyFromCV(voltage);

   const CvMapping::Sum seedSum = cvMapping->sum(CvMapping::Seed);
   if (seedSum.active)
      seedInternal = static_cast<uint8_t>(0.2 * seedSum.value * RandomWalkTables::maxSeed);
   else
      seedInternal = seed;

   const CvMapping::Sum blendSum = cvMapping->sum(CvMapping::Blend);
   if (blendSum.active)
      blendInternal = blendSum.value;
   else
      blendInternal = static_cast<float>(0.2 * blend) / static_cast<float>(maxBlend);

   return frequency;
}

float CustomTable::valueByAngle(const float& angle) const
{
   const float baseValue = Standard::getTable(static_cast<Standard::Waveform::Shape>(waveform))->valueByAngle(angle);
   const float randomValue = randomWalkTables->valueByAngle(seedInternal, angle);

   const float value = (1.0 - blendInternal) * baseValue + randomValue * blendInternal;
   return value;
}

Standard::Waveform::Shape CustomTable::getWaveform() const
{
   return waveform;
}

void CustomTable::changeWaveform(bool up)
{
   static const std::vector<Standard::Waveform::Shape> waveformOrder = {Standard::Waveform::Sine, Standard::Waveform::Saw, Standard::Waveform::Square, Standard::Waveform::SlopeUp, Standard::Waveform::SlopeDown};
   Variable::Enum<Standard::Waveform::Shape> var(waveform, waveformOrder, true);

   if (var.change(up))
      Remember::Root::setUnsynced();
}

std::string CustomTable::getWaveformName() const
{
   return Standard::getName(static_cast<Standard::Waveform::Shape>(waveform));
}

Note CustomTable::getOffsetNote()
{
   return Note::fromVoltage(offsetVoltage);
}

void CustomTable::changeOffsetNote(bool up)
{
   static const uint8_t minMidiValue = Note::availableNotes.at(1).midiValue;
   static const uint8_t maxMidiValue = Note::availableNotes.at(Note::maxIndex).midiValue;

   uint8_t currentMidiValue = Note::fromVoltage(offsetVoltage).midiValue;

   Variable::Integer<uint8_t> var(currentMidiValue, minMidiValue, maxMidiValue, false);
   if (var.change(up))
   {
      offsetVoltage = Note::fromMidi(currentMidiValue).voltage;
      Remember::Root::setUnsynced();
   }
}

uint8_t CustomTable::getSeed() const
{
   return seed;
}

const uint8_t& CustomTable::getMappedSeed() const
{
   return seedInternal;
}

void CustomTable::changeSeed(bool up)
{
   Variable::Integer<uint8_t> var(seed, 0, RandomWalkTables::maxSeed, true);

   if (var.change(up))
      Remember::Root::setUnsynced();
}

uint8_t CustomTable::getBlend() const
{
   return blend;
}

const float& CustomTable::getMappedBlend() const
{
   return blendInternal;
}

void CustomTable::changeBlend(bool up)
{
   Variable::Integer<uint8_t> var(blend, 0, maxBlend, true);

   if (var.change(up))
      Remember::Root::setUnsynced();
}
