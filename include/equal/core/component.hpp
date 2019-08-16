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

#include <equal/core/timestep.hpp>

namespace eq {

class GameObject;

/**
 * @defgroup components Components
 * @ingroup core
 * @brief Components definitions
 */

/**
 * @brief Component Base
 * @ingroup core
 */
class Component {
protected:
  Ref<GameObject> m_target;

public:
  virtual ~Component();

  void target(Ref<GameObject> &target);

  virtual void update(const Timestep &timestep) = 0;
  virtual void fixed_update(const Timestep &timestep) = 0;
};

} // namespace eq