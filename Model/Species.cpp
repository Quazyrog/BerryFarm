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

#include "Species.hpp"
#include <climits>
#include <algorithm>
#include <cmath>

namespace {
template<class T> inline constexpr T sqr(T a) 
{
    return a * a;
}

bool sectors_comparator(const MagicSector &a, const MagicSector &b)
{
    return a.size >= b.size;
}
}


struct ResearchInfo Species::Mix(const Species& first, const Species& second, std::mt19937& rng)
{
    std::uniform_real_distribution<float> mutation(-0.6, 0.6);
    float color = std::clamp<float>((first.color_ + second.color_) / 2.0f + mutation(rng), 0.0f, MAX_COLOR);
    float size = std::clamp<float>((first.size_ + second.size_) / 2.0f + mutation(rng), 0.0f, MAX_SIZE);
    float taste = std::clamp<float>((first.taste_ + second.taste_) / 2.0f + mutation(rng), 0.0f, MAX_TASTE);
    
    ResearchInfo result;
    result.duration = 2;
    result.difficulty = abs(first.color_ - second.color_) + abs(first.size_ - second.size_)
        + abs(first.taste_ - second.taste_);
    result.output = Species{static_cast<int>(color), static_cast<int>(size), static_cast<int>(taste)};
    return result;
}

Species Species::Random(std::mt19937& rng)
{
    using distribution = std::uniform_int_distribution<int>;
    static distribution color(0, MAX_COLOR);
    static distribution size(0, MAX_SIZE);
    static distribution taste(0, MAX_TASTE);
    
    return Species{color(rng), size(rng), taste(rng)};
}


MagicMapper::MagicMapper(std::mt19937& rng, const unsigned n_sectors)
{
    using distribution = std::uniform_real_distribution<float>;
    static distribution color(0, MAX_COLOR);
    static distribution size(0, MAX_SIZE);
    static distribution taste(0, MAX_TASTE);
    
    unsigned min_size;
    do {
        min_size = std::numeric_limits<unsigned>::max();
        for (unsigned i = 0; i < n_sectors; ++i)
            sectors_.emplace_back(color(rng), size(rng), taste(rng));
        compute_sizes_();
        for (auto &sector : sectors_)
            min_size = std::min(min_size, sector.size);
    } while (min_size == 0);
    
    std::sort(sectors_.begin(), sectors_.end(), sectors_comparator);
    for (unsigned i = 0; i < sectors_.size(); ++i)
        sectors_[i].index = i;
}

const MagicSector &MagicMapper::sector_of(const Species& species) const
{
    return sectors_[sector_of_(species)];
}

size_t MagicMapper::sector_of_(const Species& species) const
{
    auto square_dist = [species](const MagicSector &from_sector) 
    {
        return sqr(from_sector.site_color - species.color_) 
            + sqr(from_sector.site_size - species.size_)
            + sqr(from_sector.site_taste - species.taste_);
    };
    
    float min_dist = square_dist(sectors_[0]);
    unsigned min_sect = 0;
    
    for (unsigned int sect = 1; sect < sectors_.size(); ++sect) {
        auto dist = square_dist(sectors_[sect]);
        if (dist < min_dist) {
            min_dist = dist;
            min_sect = sect;
        }
    }
    
    return min_sect;
}

void MagicMapper::compute_sizes_()
{
    Species s;
    
    for (auto &sector : sectors_)
        sector.size = 0;
    
    for (s.color_ = 0; s.color_ <= MAX_COLOR; ++s.color_) {
        for (s.size_ = 0; s.size_ <= MAX_SIZE; ++s.size_) {
            for (s.taste_ = 0; s.taste_ <= MAX_TASTE; ++s.taste_) 
                sectors_[sector_of_(s)].size++;
        }
    }
}

