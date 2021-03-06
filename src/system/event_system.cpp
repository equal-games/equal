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
#include <equal/component/transform_component.hpp>
#include <equal/core/scene.hpp>
#include <equal/core/script.hpp>
#include <equal/event/key_press.hpp>
#include <equal/event/key_release.hpp>
#include <equal/event/mouse_move.hpp>
#include <equal/event/mouse_press.hpp>
#include <equal/event/mouse_release.hpp>
#include <equal/helper/error.hpp>
#include <equal/helper/system.hpp>
#include <equal/prefab/ui/canvas.hpp>
#include <equal/system/event_system.hpp>
#include <equal/system/script_system.hpp>

namespace eq {

void EventSystem::start() {}

void EventSystem::end() { m_focused = nullptr; }

void EventSystem::emit(Input::Event event, Ref<GameObject> &object, Input::EventData *data) const {
  auto list = get_script_system()->get_all(object->guid());
  for (auto &[type, script] : list) {
    script->dispatch(event, data);
  }
}

Ref<GameObject> EventSystem::check_tree(Ref<GameObject> &object, const Position &position) const {
  if (object && object->visible()) {
    Ref<GameObject> target;
    TransformComponent *transform{object->get<TransformComponent>()};

    if (transform->contain(position)) {
      for (auto child : transform->children()) {
        if ((target = check_tree(child, position))) {
          if (target->interactive()) {
            break;
          }
        }
      }

      if (!target && object->interactive()) {
        target = object;
      }
    }

    return target;
  } else {
    return nullptr;
  }
}

void EventSystem::onMouseMove(const Position &position) {
  Input::EventData data;
  data.mouse = position;

  // Emit to make the on mouse out event
  if (m_focused) {
    emit(Input::Event::MouseMove, m_focused, &data);
  }

  bool focus_locked = m_focused && m_focused->focused();

  if (!m_dragging && !focus_locked) {
    // Get all game object in scene
    auto items = get_scene()->canvas()->get<TransformComponent>()->children();

    std::sort(items.begin(), items.end(),
              [](const Ref<GameObject> l, const Ref<GameObject> r) -> bool { return l->order() > r->order(); });

    // Get focused game object
    for (auto obj : items) {
      if ((m_focused = check_tree(obj, data.mouse))) {
        break;
      }
    }

    if (m_focused) {
      emit(Input::Event::MouseMove, m_focused, &data);
    }
  }
}

void EventSystem::onMousePress(Mouse::Button button, const Position &position) {
  if (m_focused) {
    Input::EventData data;
    if (button == Mouse::Left) {
      m_dragging = true;
    }
    data.mouse = position;
    data.mouse_button = button;

    emit(Input::Event::MousePress, m_focused, &data);
  }
}

void EventSystem::onMouseRelease(Mouse::Button button, const Position &position) {
  if (m_focused) {
    Input::EventData data;
    if (button == Mouse::Left) {
      m_dragging = false;
    }
    data.mouse = position;
    data.mouse_button = button;

    emit(Input::Event::MouseRelease, m_focused, &data);
  }
}

void EventSystem::onKeyPress(Keyboard::Key key) {
  if (m_focused) {
    Input::EventData data;
    data.key = key;

    emit(Input::Event::KeyPress, m_focused, &data);
  }
}

void EventSystem::onKeyRelease(Keyboard::Key key) {
  if (m_focused) {
    Input::EventData data;
    data.key = key;

    emit(Input::Event::KeyRelease, m_focused, &data);
  }
}

void EventSystem::onInsertText(const std::wstring &text) {
  if (m_focused) {
    Input::EventData data;
    data.text = text;

    emit(Input::Event::InsertText, m_focused, &data);
  }
}

} // namespace eq
