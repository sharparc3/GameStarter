# Game Starter framework

## Introduction

This project is a 2D simple game framework designed to facilitate the development of simple 2D games. It provides essential features such as creating game window, rendering sprites, playing sounds, managing game states. The framework is built with ease of use in mind, making it suitable for beginners developers who want to quickly prototype and create simple 2D games.

Key features of this 2D game framework include:
- **Sprite Rendering**: Easily load and render 2D sprites with support for animation.
- **Sound Playback**: Integrate and play sound effects and background music.
- **State Management**: Manage different game states such as menus, gameplay, and paused states.

A few tools and libraries are integrated to facilitate various tasks: [Box2D](https://github.com/erincatto/box2d), [nlohmann JSON](https://github.com/nlohmann/json), [Dear ImGui](https://github.com/ocornut/imgui).

## Prerequisites

Visual Studio 2022 Community Edition with build tool v143.

## Building

Open ```GameStarter.sln``` and build.
Run ```copy_lib.bat``` in the root folder to copy DLLs into executable folder.

## Getting Started

### Render a Sprite

Most of the time, components of the framework will work with C++ shared pointer.

```cpp
// load a texture
RESOURCE()->LoadTexture("texture.png");

// create a sprite
std::shared_ptr<Sprite2D> sprite = std::make_shared<Sprite2D>(RESOURCE()->GetTexture("texture.png"));

// create a sprite renderer
SpriteRenderer renderer;

// .. 

// inside the Draw method of the state
renderer.AddObject(sprite);

render.Render();

```

### Play a Sound

```cpp
// load a sound
RESOURCE()->LoadSound("sound.mp3");

// get sound object
auto sound = RESOURCE()->GetSound("sound.mp3");

// play
SOUNDPLAYER()->Play(sound);

```

### Change State

```cpp
GSM()->PushState(GameStateType::MENU);
```

## Documentation

To be updated

## License

This project is licensed under the MIT License. 

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
