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

#include <equal/core/game_object.hpp>
#include <equal/core/types.hpp>

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
  Ref<Image> m_foreground;
  Ref<Image> m_background;

public:
  /**
   * @brief Construct a new Progress Bar object
   *
   * @param id
   */
  ProgressBar(const std::string &id);

  /**
   * @brief Construct a new Progress Bar object
   *
   * @param value
   * @param max_value
   * @param position
   * @param size
   */
  ProgressBar(float value, float max_value, const Position &position, const Size &size);

  /**
   * @brief Destroy the Progress Bar object
   *
   */
  virtual ~ProgressBar();

  /**
   * @brief
   *
   * @param value
   */
  void value(float value);

  /**
   * @brief
   *
   * @return float
   */
  float value() const;

  /**
   * @brief
   *
   * @param value
   */
  void max_value(float value);

  /**
   * @brief
   *
   * @return float
   */
  float max_value() const;
};

} // namespace eq::ui
