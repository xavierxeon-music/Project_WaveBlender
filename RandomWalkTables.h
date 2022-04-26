#ifndef RandomWalkTablesH
#define RandomWalkTablesH

#include <Sound/WaveTable.h>

#include <Global.h>

class RandomWalkTables
{
public:
   static const uint8_t maxSeed;

public:
   RandomWalkTables();

public:
   float valueByAngle(const uint8_t seed, const float& angle) const;

private:
   struct Index
   {
      uint8_t major; // 0 to 64
      uint8_t minor; // 0 to 64
   };

private:
   void create(const uint8_t seed);
   uint64_t fullIndexFromAngle(float angle) const;
   Index indexFromFullIndex(const uint64_t& fullIndex) const;
   float valueFromIndex(const uint8_t seed, const Index& index) const;

private:
   float tables[128][64]; // seed, index
};

#endif // RandomWalkTablesH
