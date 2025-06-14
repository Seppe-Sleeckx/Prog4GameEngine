# Minigin

Minigin is a very small project using [SDL2](https://www.libsdl.org/) and [glm](https://github.com/g-truc/glm) for 2D c++ game projects. It is in no way a game engine, only a barebone start project where everything sdl related has been set up. It contains glm for vector math, to aleviate the need to write custom vector and matrix classes.

[![Build Status](https://github.com/avadae/minigin/actions/workflows/msbuild.yml/badge.svg)](https://github.com/avadae/msbuild/actions)
[![GitHub Release](https://img.shields.io/github/v/release/avadae/minigin?logo=github&sort=semver)](https://github.com/avadae/minigin/releases/latest)

# Goal

Minigin can/may be used as a start project for the exam assignment in the course [Programming 4](https://youtu.be/j96Oh6vzhmg) at DAE. In that assignment students need to recreate a popular 80's arcade game with a game engine they need to program themselves. During the course we discuss several game programming patterns, using the book '[Game Programming Patterns](https://gameprogrammingpatterns.com/)' by [Robert Nystrom](https://github.com/munificent) as reading material. 

# Disclaimer

Minigin is, despite perhaps the suggestion in its name, **not** a game engine. It is just a very simple sdl2 ready project with some of the scaffolding in place to get started. None of the patterns discussed in the course are used yet (except singleton which use we challenge during the course). It is up to the students to implement their own vision for their engine, apply patterns as they see fit, create their game as efficient as possible.

# Use

Either download the latest release of this project and compile/run in visual studio or, since students need to have their work on github too, they can use this repository as a template (see the "Use this template" button at the top right corner). There is no point in forking this project.

# Project
This remake of Qbert uses (a modified) minigin engine. Some notable features added on top of minigin during the making of this project are: a soundsystem using SDL_Mixer, keyboard + controller input using SDL and implementations of multiple design patterns like (ex.): the Command pattern, Observer pattern, the Finite State Machine pattern and more. The game itself is completely written in C++ making use of aforementioned design patterns. All of the levels in the game are loaded from .bin files which are created in DEBUG mode, so when changing some of the level settings be sure to reload them in DEBUG, the bin files can be found in the Data folder just like all of the game's other resources. The source files for the entire project can be found here: https://github.com/Seppe-Sleeckx/Prog4GameEngine .

# Game
The game itself is a simple arcade game programmed with modern techniques completely in C++ 20; Making use of a gameobject - component design like many other modern engines we can abstract elements of a game into objects and their respective properties as components. On top of this gameobject - component structure I also make use of the command structure to reduce duplicated code and simplify otherwise complex operations into multiple smaller commands. These commands can then also be bound to input from either the keyboard or a controller to keep my codebase more clean and organized. I also use some sound effect which can be loaded from files and played by a soundsystem that uses concurrency to play these sounds during gameplay without blocking the main thread; I also changed the Scenemanager and Scene classes from their original to behave like a FSM with corresponding OnEnter() and OnExit() functions allowing me to easily and quickly setup scenes and per-scene control bindings in an organized manner. Furthermore does this approach also allow me to quickly and easily switch between scenes needing nothing but the new scene's name. More Specifically for this game, I have implemented an Isometric grid on which all of my game entities move around. Using an isometric grid makes moving my gameobjects very easy and doesnt require me to constantly recalculate their world position whenever something about the grid changes as this is now done automatically.