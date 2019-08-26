/*
 * Copyright (c) 2019 Wojciech Matusiak <saphir2357@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

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
