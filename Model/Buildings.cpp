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

#include <cassert>
#include "World.hpp"
#include "Buildings.hpp"

AbstractBuilding::AbstractBuilding(BuildingSlot &slot):
    WorldEntity(slot.game()),
    slot_(&slot)
{
    assert(slot.building() == nullptr);
}

void BuildingUpgradeInfo::give_upgrade_points(unsigned n_points)
{
    if (required_points_ == accumulated_points_)
        return;

    if (required_points_ - accumulated_points_ > n_points) {
        accumulated_points_ = required_points_;
        finish_upgrade();
    } else {
        accumulated_points_ += n_points;
    }
}

void BuildingUpgradeInfo::finish_upgrade()
{
    building_->on_upgraded();
    slot_->building_ = nullptr;
    auto new_building = building_->upgraded();
    new_building->on_built();
    slot_->game().mark_for_deletion_(*building_);
    building_ = nullptr;
    slot_ = nullptr;
}
