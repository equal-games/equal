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
#include <equal/core/game_object.hpp>

namespace eq::ui {

class Image;

/**
 * @ingroup ui
 * @brief UI progress bar
 */
class ProgressBar : public GameObject {
private:
  float m_value{0};
  float m_max_value{0};
  Image *m_foreground{nullptr};
  Image *m_background{nullptr};

public:
  ProgressBar(const std::string &id);
  ProgressBar(float value, float max_value, const Position &position, const Size &size);
  virtual ~ProgressBar();

  void value(float value);
  float value() const;
  void max_value(float value);
  float max_value() const;
};

} // namespace eq::ui
