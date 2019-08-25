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


int main() {
    std::mt19937 rng;
    
    std::cerr << "Building mapper" << std::endl;
    MagicMapper mapper(rng, 10);
    std::cerr << "Built mapper; sectors:";
    for (const auto &sect : mapper.sectors_)
        std::cerr << "\n  " << sect;
    std::cerr << std::endl;
    
    for (int i = 0 ; i < 20 ; ++i) {
        Species s1 = Species::Random(rng);
        Species s2 = Species::Random(rng);
        std::cerr << "Mixing " << s1 << " and " << s2 << " gives " << Species::Mix(s1, s2, rng).output << std::endl;
    }
    return 0;
}
