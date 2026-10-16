# Arcade Engine

A small 2D game engine written in C++20 on top of SFML 3. It handles the window, the frame loop, input from keyboard, mouse, and gamepads, resources, audio, saves, screenshots, and an in-game GUI layer, so a game built on it only has to supply scenes and gameplay.

Arcade is a solo project and a work in progress. The engine core and its managers are in place. Scene switching is the next piece being built.

## Features

- **Frame loop with capped delta time.** Each frame processes events, updates, and renders. Delta time is clamped to a configurable maximum (0.03 s by default), so a stall or a dragged window doesn't produce a huge physics step.
- **Action-based input.** Game code binds logical actions (any `int` or enum) to one or more physical inputs, which can be a keyboard scancode, a mouse button, a gamepad button, or an analog axis with a threshold. `Pressed(action)` returns true if any binding for that action is active.
- **Gamepad layout mapping.** Gamepad buttons use logical names (`South`, `East`, `L1`, `Select`, and so on). The engine reads the controller's USB vendor ID and maps Xbox and PlayStation layouts to the same names, so bindings don't change between controllers.
- **Virtual cursor.** The left stick drives the cursor with a configurable speed and deadzone, and it stays inside the window. The gamepad's South button clicks GUI widgets, so menus work without a mouse.
- **Event dispatch with `std::visit`.** SFML 3 events go to a visitor with one overload per event type the engine cares about and a catch-all for the rest.
- **Managers** live in one `EngineContext`:
  - `ResourceManager` loads textures, sounds, and fonts on first use and caches them by filename. It streams music instead of caching it.
  - `AudioManager` sets the global volume and the 3D listener position and direction.
  - `RenderManager` draws the scene to an off-screen render texture with a background layer, then presents it to the window. It also supports custom views for cameras.
  - `GuiManager` wraps TGUI with a dark theme and rescales the GUI when the window is resized.
  - `SaveManager` keeps key/value save data as JSON and writes it to disk on shutdown.
  - `SceneManager` queues scene changes and restarts so they happen between frames.
  - `TimeManager`, `RandomManager` (ints, floats, bools, positions, angles, colors), `ClipboardManager`, `ScreenshotManager`, and `CursorManager`.
- **JSON configuration.** Window title and size, max delta time, volume, background color, cursor settings, and joystick deadzone all come from `Content/Config.json`.
- **Logging** through spdlog with `LOG_INFO`, `LOG_WARNING`, and `LOG_ERROR` macros.

## Controls

| Input | Action |
|---|---|
| Ctrl + Shift + S | Save a timestamped screenshot to `Content/Screenshots/` |
| R | Restart the current scene |
| M, or gamepad Select | Return to the menu scene |
| Left stick | Move the cursor |
| Gamepad South (A on Xbox, Cross on PlayStation) | Click the GUI widget under the cursor |

## Building

You need CMake 3.28 or newer and a C++20 compiler (MSVC, GCC, or Clang). CMake downloads all dependencies through `FetchContent`, so you don't install them separately. On Linux, SFML also needs the usual system development packages for X11, OpenGL, udev, and audio. See SFML's build docs for the exact list.

```sh
cmake -B Build -DCMAKE_BUILD_TYPE=Debug
cmake --build Build -j
```

The engine loads `Content/` with relative paths, so run the executable from the repository root. VS Code users can build with the included default build task.

## Project layout

```
Engine/
  Include/   headers (Core, Managers, Utils)
  Source/    implementation and Main.cpp
Content/
  Config.json   engine settings
  Fonts/        DM Sans
  Textures/     window icon and background
  Themes/       TGUI dark theme
```

## Dependencies

| Library | Version | Used for |
|---|---|---|
| [SFML](https://github.com/SFML/SFML) | 3.0.2 | Windowing, graphics, audio, input |
| [TGUI](https://github.com/texus/TGUI) | 1.11.0 | In-game GUI widgets |
| [nlohmann/json](https://github.com/nlohmann/json) | 3.12.0 | Config and save files |
| [spdlog](https://github.com/gabime/spdlog) | 1.16.0 | Logging |

## Roadmap

- Scene switching (the queue is in place; loading and swapping scenes is next)
