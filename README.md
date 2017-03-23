# JustAGame

[![Build Status](https://travis-ci.org/Shinao/JustAGame.svg?branch=master)](https://travis-ci.org/Shinao/JustAGame)

JustAGame is a game framework written in C++. It has been a project to learn and understand all the facets of a game development. It can add any game mode as it wants by building a shared library inheriting a common interface for the client/server to load at runtime for test purposes. Or to just have some fun.

### Preview
Showing the sample game Tic Tac Toe where two clients connect to a local server
<p align="center">
 <img width="50%" src="/docs/JAGLeftResized.gif"/><img width="50%" src="/docs/JAGRightResized.gif"/>
</p>

### Capacities
- Portable: linux/windows
- GUI: widgets, console, chat, screen manager...
- Network: udp, tcp, reliability, commands...
- Utility: system management mostly
- Custom modes (like TicTacToe) are loaded via shared library via a common interface for easy to download/share
- Common clients to connect to server, save user settings, download modes...

### Build
```
cmake . && make && ./justagame
```
Tried on Windows 7 MinGW / Linux Debian

### Dependencies
 - Libraries SFML & Box2D
 - C++11 Compiler
 - CMake/Make

### Libraries
- SFML 2.1 - Multimedia library - https://www.sfml-dev.org/
- Box2D 3.0 - Physic library - http://box2d.org/
- Thor - SFML Extension (Altered) - https://github.com/Bromeon/Thor/
- SimpleIni - INI Library - https://github.com/brofield/simpleini
