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

#include <equal/core/component.hpp>
#include <equal/core/types.hpp>
#include <vector>

namespace eq {

class GameObject;

/**
 * @ingroup components
 * @brief
 */
class TransformComponent : public Component {
private:
  Position m_local_position{0};
  Position m_position{0};
  Rotation m_local_rotation{0};
  Rotation m_rotation{0};
  Size m_size{0};
  Origin m_local_origin{0};
  Origin m_origin{0};
  Transform::Anchor m_anchor{Transform::Anchor::TL};
  BoundingBox m_bbox{0};
  bool m_need_update{true};
  Ref<GameObject> m_parent;
  std::vector<Ref<GameObject>> m_children;

public:
  TransformComponent() = default;
  TransformComponent(const Position &position);
  TransformComponent(const Position &position, const Size &size);
  virtual ~TransformComponent();

  const Ref<GameObject> parent() const;
  void parent(Ref<GameObject> &object);
  const std::vector<Ref<GameObject>> children();
  const Ref<GameObject> child(int index) const;
  void add(Ref<GameObject> &parent, Ref<GameObject> object);
  void remove(const Ref<GameObject> &object);
  void parentUpdate();

  Transform::Anchor anchor() const;
  void anchor(Transform::Anchor anchor);
  void position(const Position &position);
  const Position &position() const;
  const Position &local_position() const;
  void rotation(const Rotation &position);
  const Rotation &rotation() const;
  const Rotation &local_rotation() const;
  void size(const Size &size);
  const Size &size() const;
  void origin(const Origin &origin);
  const Origin &origin() const;
  const Origin &local_origin() const;
  void bbox(const BoundingBox &bbox);
  const BoundingBox &bbox() const;
  bool contain(const Position &position) const;

  void update(const Timestep &timestep);
  void fixed_update(const Timestep &timestep);
};

} // namespace eq
