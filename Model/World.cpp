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


WorldEntity::WorldEntity(World &parent):
    game_(&parent)
{
    game_->register_entity_(*this);
}

WorldEntity::WorldEntity(WorldEntity &&other) noexcept:
    game_(other.game_),
    id_(other.id_)
{
    other.game_ = nullptr;
    other.id_ = ENTITY_ID_NONE;
}

WorldEntity::~WorldEntity()
{
    if (game_)
        game_->unregister_entity_(*this);
}


void World::register_entity_(WorldEntity &entity)
{
    assert(entity.id_ == ENTITY_ID_NONE);
    entities_[next_entity_id] = &entity;
    entity.id_ = next_entity_id++;
}

void World::unregister_entity_(WorldEntity &entity)
{
    auto it = entities_.find(entity.id_);
    assert(it != entities_.end());
    entities_.erase(it);
    entity.id_ = ENTITY_ID_NONE;
}

void World::mark_for_deletion_(WorldEntity &entity)
{
    assert(entities_.find(entity.id_) != entities_.end());
    marked_for_deletion_.push(&entity);
}

void World::delete_marked()
{
    while (!marked_for_deletion_.empty()) {
        auto entity = marked_for_deletion_.top();
        marked_for_deletion_.pop();
        delete entity;
    }
}

BuildingSlot::~BuildingSlot()
{
    delete building_;
}
