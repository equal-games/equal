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
#include <equal/component/renderer_component.hpp>
#include <equal/component/transform_component.hpp>
#include <equal/core/resource.hpp>
#include <equal/prefab/ui/container.hpp>

namespace eq::ui {

Container::Container(const std::string &id) : GameObject(id) {
  name("Container");
  interactive(false);

  add<RendererComponent>(g_res.getTexture("container"));
  get<RendererComponent>()->type(Render::Type::Sliced);
}

Container::Container(const Position &position, const Size &size) : GameObject(position, size) {
  name("Container");
  interactive(false);

  add<RendererComponent>(g_res.getTexture("container"));
  get<RendererComponent>()->type(Render::Type::Sliced);
}

Container::~Container() {}

} // namespace eq::ui
