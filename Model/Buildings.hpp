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

#ifndef BUILDINGS_HPP
#define BUILDINGS_HPP

#include "World.hpp"

class BuildingSlot;
class AbstractBuilding;
class BuildingUpgradeInfo;


class AbstractBuilding : public WorldEntity
{
protected:
    BuildingSlot *slot_;

public:
    explicit AbstractBuilding(BuildingSlot &slot);
    ~AbstractBuilding() override = default;

    virtual void on_built() = 0;
    virtual void on_destroyed() = 0;
    virtual void on_upgraded() = 0;

    virtual BuildingUpgradeInfo &upgrade_info() = 0;
    virtual AbstractBuilding *upgraded() = 0;
};


class BuildingUpgradeInfo
{
    AbstractBuilding *building_;
    BuildingSlot *slot_;
    unsigned required_points_;
    unsigned accumulated_points_ = 0;

public:
    BuildingUpgradeInfo(AbstractBuilding &building, BuildingSlot &slot, unsigned required_upgrade_points):
        building_(&building),
        slot_(&slot),
        required_points_(required_upgrade_points)
    {}

    [[nodiscard]] AbstractBuilding &building() const { return *building_; }

    [[nodiscard]] unsigned accumulated_upgrade_points() const { return accumulated_points_; }

    [[nodiscard]] unsigned required_upgrade_points() const { return required_points_; }

    void give_upgrade_points(unsigned n_points);
    void finish_upgrade();
};


template<class Building> class ConstructionSite : public AbstractBuilding
{
    BuildingUpgradeInfo upgrade_info_;

public:
    ConstructionSite(BuildingSlot &slot, unsigned int points_to_build):
        AbstractBuilding(slot),
        upgrade_info_(*this, points_to_build)
    {}

    void on_built() override {}

    void on_destroyed() override {}

    void on_upgraded() override {}

    BuildingUpgradeInfo &upgrade_info() override
    {
        return upgrade_info_;
    }

    AbstractBuilding *upgraded() override
    {
        return new Building(slot_);
    }
};

#endif //BUILDINGS_HPP
