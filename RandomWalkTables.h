#ifndef RandomWalkTablesH
#define RandomWalkTablesH

#include <Sound/WaveTable.h>

#include <Global.h>

class RandomWalkTables : public WaveTable::Table
{
public:
   static const uint8_t maxSeed;

public:
   RandomWalkTables();

public:
   void setSeed(const uint8_t& newSeed);
   float valueByAngle(const float& angle) const;

private:
   struct Index
   {
      uint8_t major; // 0 to 64
      uint8_t minor; // 0 to 64
   };

private:
   uint64_t fullIndexFromAngle(float angle) const;
   Index indexFromFullIndex(const uint64_t& fullIndex) const;
   float valueFromIndex(const uint8_t seed, const Index& index) const;

private:
   uint8_t seed;
   float tables[128][64]; // seed, index
};

#endif // RandomWalkTablesH
