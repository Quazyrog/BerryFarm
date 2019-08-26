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
