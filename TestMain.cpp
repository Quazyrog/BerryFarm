#include <gtest/gtest.h>

#include "Test/SpeciesTests.cpp"


int main(int argc, char **argv)
{
    std::srand((unsigned int)std::time(nullptr));
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

