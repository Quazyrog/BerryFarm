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

#ifndef SPECIES_HPP
#define SPECIES_HPP

#include <cassert>
#include <random>
#include <tuple>


constexpr float MAX_COLOR = 5.0;
enum class Color : uint8_t
{
    RED,
    YELLOW,
    PURPLE,
    BLUE,
    GREEN,
    ORANGE
};


constexpr float MAX_SIZE = 4.0;
enum class Size : uint8_t
{
    TINY,
    SMALL,
    MEDIUM,
    LARGE,
    HUGE
};


constexpr float MAX_TASTE = 5.0;
enum class Taste : uint8_t
{
    SWEET,
    BITTER,
    TART,
    SALTY,
    SOUR,
    TASTELESS
};


class Species
{
    friend class MagicMapper;
    friend std::ostream &operator<<(std::ostream &, const Species &species);
    
    int color_ = 0;
    int size_ = 0;
    int taste_ = 0;
    
public:
    static struct ResearchInfo Mix(const Species &first, const Species &second, std::mt19937& rng);
    static Species Random(std::mt19937 &rng);
    
    Species() = default;
    
    Species(int c, int s, int t):
        color_(c),
        size_(s),
        taste_(t)
    {}
    
    Color color() const
    {
        assert(0 <= color_ && color_ <= MAX_COLOR);
        return static_cast<Color>(color_);
    }
    
    Size size() const
    {
        assert(0 <= size_ && size_ <= MAX_SIZE);
        return static_cast<Size>(size_);
    }
    
    Taste taste() const
    {
        assert(0 <= taste_ && taste_ <= MAX_TASTE);
        return static_cast<Taste>(taste_);
    }
};


struct ResearchInfo
{
    unsigned duration;
    unsigned difficulty;
    Species output;
};


struct MagicSector
{
    using CoordType = float;
    
    unsigned index = 0;
    CoordType site_color;
    CoordType site_size;
    CoordType site_taste;
    unsigned size = 0;
    
    MagicSector() = default;
    
    MagicSector(CoordType c, CoordType s, CoordType t):
        site_color(c),
        site_size(s),
        site_taste(t)
    {
        assert(0 <= c && c <= MAX_COLOR);
        assert(0 <= s && s <= MAX_SIZE);
        assert(0 <= t && t <= MAX_TASTE);
    }
};


class MagicMapper
{
    using CoordType = MagicSector::CoordType;
        
    std::vector<MagicSector> sectors_;
    
    size_t sector_of_(const Species &species) const;
    void compute_sizes_();
    
public:
    MagicMapper(std::mt19937 &rng, const unsigned n_sectors);

    const MagicSector &sector_by_index(unsigned index) { return sectors_.at(index); }
    [[nodiscard]] unsigned sectors_number() const { return sectors_.size(); }
    [[nodiscard]] const MagicSector &sector_of(const Species &species) const;
};

#endif // SPECIES_HPP
