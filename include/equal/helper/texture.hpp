/*
 * Copyright 2019 Equal Games
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <equal/core/types.hpp>
#include <equal/world/data.hpp>

namespace eq {

/**
 * @ingroup helpers
 * @brief Get the Tile Texture By ID object
 *
 * @param texture_id unsigned int
 * @param tile_size const eq::Size &
 * @param texture_size const eq::Size &
 * @return eq::VertexPoint
 */
VertexPoint GetVertexTextureByID(uint32_t texture_id, const Size &tile_size, const Size &texture_size);

/**
 * @brief Get the Tile Texture By ID object
 *
 * @param texture_id uint32_t
 * @param world const eq::World&
 * @return eq::Position
 */
Position GetTileTextureByID(uint32_t texture_id, const World &world);

} // namespace eq
