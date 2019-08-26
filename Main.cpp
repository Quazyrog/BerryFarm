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

#include "Model/Species.hpp"
#include <iostream>


std::ostream &operator<<(std::ostream &s, const MagicSector &sect)
{
    return s << "MagicSector{" << sect.index << ", " << sect.size << ", c=" << sect.site_color  << ", s=" << sect.site_size << ", t=" << sect.site_taste << "}";
}

std::ostream &operator<<(std::ostream &s, const Species &species)
{
    return s << "Species{" << species.color_ << ", " << species.size_ << ", " << species.taste_ << "}";
}


int main()
{
    return 0;
}
