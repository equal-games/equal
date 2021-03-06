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
#include <equal/core/painter.hpp>
#include <equal/core/scene.hpp>
#include <equal/core/window.hpp>
#include <equal/helper/system.hpp>
#include <equal/system/event_system.hpp>

namespace eq {

const Scope<EventSystem> &get_event_system() { return g_app.scene->event_system(); }

const Scope<ComponentSystem> &get_component_system() { return g_app.scene->component_system(); }

const Scope<ScriptSystem> &get_script_system() { return g_app.scene->script_system(); }

const Scope<Scene> &get_scene() { return g_app.scene; }

const Scope<Window> &get_window() { return g_app.window; }

const Scope<Painter> &get_painter() { return g_app.painter; }

} // namespace eq
