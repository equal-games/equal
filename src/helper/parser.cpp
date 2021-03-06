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
#include <chrono>
#include <equal/component/renderer_component.hpp>
#include <equal/component/text_component.hpp>
#include <equal/component/transform_component.hpp>
#include <equal/core/game_object.hpp>
#include <equal/core/logger.hpp>
#include <equal/core/window.hpp>
#include <equal/helper/error.hpp>
#include <equal/helper/parser.hpp>
#include <equal/helper/string.hpp>
#include <equal/helper/system.hpp>
#include <equal/helper/timer.hpp>
#include <equal/prefab/ui/ui.hpp>
#include <fstream>
#include <memory>

namespace eq {

Ref<ui::Canvas> ParserUI(const std::string &filename, const Parser::Actions &actions) {
  try {
    eq::Timer timer("Parsing UI");
    Ref<ui::Canvas> canvas = std::make_shared<ui::Canvas>(Position{0, 0}, get_window()->size());

    std::ifstream ui_file(filename);
    std::string line;

    Ref<GameObject> object;

    while (std::getline(ui_file, line)) {
      std::istringstream iss(line);
      if (iss.eof()) {
        break;
      } else if (iss.bad() || iss.fail()) {
        std::throw_with_nested(iss.exceptions());
      } else if (line.empty() || str::trim_copy(line).empty()) {
        continue;
      }

      // Detect who is parent of who
      int level_child = 0;
      std::for_each(line.begin(), line.end(), [&level_child](const char c) -> void {
        if (std::isspace(c)) {
          level_child += 1;
        }
      });
      level_child /= 2;

      std::string word;
      iss >> word;

      // Ignore commented line
      if (word == "--") {
        continue;
      }

      // Get name of object type or property
      if (std::isupper(word.at(0))) { // Is object type
        std::pair<std::string, std::string> p = str::split_pair(word, '#');
        std::string type = p.first;
        std::string id = p.second;

        Ref<GameObject> parent;

        if (level_child == 0) {
          parent = canvas;
        } else {
          parent = canvas->get<TransformComponent>()->children().back();
          for (int level = 1; level < level_child; ++level) {
            parent = parent->get<TransformComponent>()->children().back();
          }
        }

        if (type == "Image") {
          object = parent->create_object<ui::Image>(id);
        } else if (type == "Container") {
          object = parent->create_object<ui::Container>(id);
        } else if (type == "Text") {
          object = parent->create_object<ui::Text>(id);
        } else if (type == "Button") {
          object = parent->create_object<ui::Button>(id);
        } else if (type == "Window") {
          object = parent->create_object<ui::Window>(id);
        } else if (type == "TextInput") {
          object = parent->create_object<ui::TextInput>(id);
        } else if (type == "ProgressBar") {
          object = parent->create_object<ui::ProgressBar>(id);
        }

      } else if (std::find(line.begin(), line.end(), ':') != line.end()) { // Is Property
        std::pair<std::string, std::string> p = str::split_pair(line, ':');
        std::string attr = p.first;
        std::string value = p.second;

        if (attr == "position") {
          std::pair<std::string, std::string> p = str::split_pair(value, ' ');
          int x = std::atoi(p.first.c_str());
          int y = std::atoi(p.second.c_str());
          object->get<TransformComponent>()->position(Position{x, y});
        } else if (attr == "size") {
          std::pair<std::string, std::string> p = str::split_pair(value, ' ');
          int x = std::atoi(p.first.c_str());
          int y = std::atoi(p.second.c_str());
          object->get<TransformComponent>()->size(Size{x, y});
        } else if (attr == "anchor") {
          object->get<TransformComponent>()->anchor(Transform::AnchorFromString(value));
        } else if (attr == "visible") {
          object->visible(value == "true" ? true : false);
        } else if (object->name() == "Image") {

        } else if (object->name() == "Container") {

        } else if (object->name() == "Text") {
          Ref<ui::Text> obj = std::dynamic_pointer_cast<ui::Text>(object);

          if (attr == "text") {
            obj->text(value);
          }
        } else if (object->name() == "Button") {
          Ref<ui::Button> obj = std::dynamic_pointer_cast<ui::Button>(object);

          if (attr == "text") {
            obj->text(value);
          } else if (attr == "@action") {
            auto action = actions.find(value);
            if (action != actions.end()) {
              obj->action(action->second);
            } else {
              auto action = actions.find("*");
              if (action != actions.end()) {
                obj->action(action->second);
              } else {
                EQ_CORE_WARN("Can't associate action({}) to button({})", value, obj->id());
              }
            }
          }
        } else if (object->name() == "Window") {
          Ref<ui::Window> obj = std::dynamic_pointer_cast<ui::Window>(object);

          if (attr == "title") {
            obj->title(value);
          }
        } else if (object->name() == "TextInput") {
          Ref<ui::TextInput> obj = std::dynamic_pointer_cast<ui::TextInput>(object);

          if (attr == "masked") {
            obj->masked(value == "true" ? true : false);
          } else if (attr == "text") {
            obj->text(value);
          }
        } else if (object->name() == "ProgressBar") {
          Ref<ui::ProgressBar> obj = std::dynamic_pointer_cast<ui::ProgressBar>(object);

          if (attr == "value") {
            obj->value(std::atof(value.c_str()));
          } else if (attr == "max_value") {
            obj->max_value(std::atof(value.c_str()));
          }
        }
      }
    }

    return canvas;
  } catch (...) {
    EQ_THROW("Error on parse: {}", filename);
  }
}

} // namespace eq
