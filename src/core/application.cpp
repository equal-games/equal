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
#include <equal/core/application.hpp>
#include <equal/core/logger.hpp>
#include <equal/helper/error.hpp>
#include <equal/helper/string.hpp>
#include <equal/prefab/scene/blank.hpp>
#include <equal/system/event_system.hpp>

namespace eq {

Application g_app;

void Init() {
  Scope<Window> &window = g_app.window;
  Scope<Painter> &painter = g_app.painter;
  Scope<Timestep> &timestep = g_app.timestep;
  Scope<Scene> &scene = g_app.scene;
  const WindowOptions &options = g_app.window->options();

  while (window->opened()) {
    // Timestep
    timestep->reset();
    EQ_CORE_TRACE("FPS: {0:6d} | Delta Time: {1:.4f} | Fixed Delta Time: {2:.4f}", timestep->fps, timestep->time,
                  timestep->fixed_time);

    // Window
    window->update();

    // Scene
    scene->update(*timestep);
    timestep->fix([&](const Timestep &timestep_fixed) -> void { scene->fixed_update(timestep_fixed); });

    // Painter
    painter->clear(Color{128, 128, 128, 255});
    painter->draw(scene);
    painter->display();

    // Lock engine max FPS
    if (*timestep < timestep->MAX_FPS) {
      int delay = static_cast<int>(timestep->MAX_FPS - *timestep);
      std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }

    // If defined FPS limit
    if (!options.vsync && options.fps_limit) {
      float limit = 1000.0f / static_cast<float>(options.fps_limit);
      if (*timestep < limit) {
        int delay = static_cast<int>(limit - *timestep);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
      }
    }
  }
}

void Quit() { g_app.window->shutdown(); }

} // namespace eq
