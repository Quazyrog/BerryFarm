#include <gtest/gtest.h>
#include <random>
#include "../Model/Species.hpp"

TEST(Species, mapper_creates_sites)
{
    constexpr unsigned N_SECTORS = 20;
    std::mt19937 rng;
    MagicMapper mapper(rng, N_SECTORS);

    ASSERT_EQ(mapper.sectors_number(), N_SECTORS);
    for (unsigned i = 0; i < mapper.sectors_number(); ++i) {
        auto sector = mapper.sector_by_index(i);
        ASSERT_NE(sector.site_size, 0);
    }
}

TEST(Species, mixing_gives_near_result)
{
    std::mt19937 rng;

    Species s1{2, 2, 2};
    Species s2{3, 3, 3};
    auto info = Species::Mix(s1, s2, rng);
    auto out = info.output;
    ASSERT_EQ(info.difficulty, 3);
    ASSERT_TRUE(out.color() == Color::PURPLE || out.color() == Color::BLUE);
    ASSERT_TRUE(out.size() == Size::MEDIUM || out.size() == Size::LARGE);
    ASSERT_TRUE(out.taste() == Taste::TART || out.taste() == Taste::SALTY);
}
