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

#ifndef BERRYFARM_PLAYERTOWN_HPP
#define BERRYFARM_PLAYERTOWN_HPP
#include <unordered_map>
#include <stack>


using EntityID = unsigned;
constexpr EntityID ENTITY_ID_NONE = 0;
constexpr EntityID ENTITY_ID_FIRST = 1;

class AbstractBuilding;

class World;
class WorldEntity;


class WorldEntity
{
    friend class World;

private:
    World *game_{nullptr};
    EntityID id_{ENTITY_ID_NONE};

protected:
    WorldEntity() = default;
    explicit WorldEntity(World &parent);

public:
    WorldEntity(WorldEntity &&other) noexcept;
    virtual ~WorldEntity();

    [[nodiscard]] EntityID id() const { return id_; }
    [[nodiscard]] World &game() const { return *game_; }
};


class World
{
    friend class WorldEntity;

private:
    unsigned mana_production_;
    unsigned mana_consumption_;

    EntityID next_entity_id = ENTITY_ID_FIRST;
    std::unordered_map<EntityID, WorldEntity*> entities_;
    std::stack<WorldEntity*> marked_for_deletion_;

    void register_entity_(WorldEntity &entity);
    void unregister_entity_(WorldEntity &entity);

public:
    void mark_for_deletion_(WorldEntity &entity);
    void delete_marked();
};


class BuildingSlot : public WorldEntity
{
    friend class BuildingUpgradeInfo;

protected:
    AbstractBuilding *building_ = nullptr;

public:
    using WorldEntity::WorldEntity;
    ~BuildingSlot() override;

    [[nodiscard]] AbstractBuilding *building() const { return building_; }
};

#endif //BERRYFARM_PLAYERTOWN_HPP
