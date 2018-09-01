# A place for my random IoT Stuff
#
#
#
## What will you find here?
---
Some of my personal projects, involving the Intel Genuino UNO 101, ESP8266 and Raspberry Pi.

## What is the purpose of this repository?
---
Since I mentor a small group who seek to learn embedded programming and IoT concepts, I'm starting a proper place to store my codes, so I don't end up looking silly when they ask for it.

## Repo Structure
---
To keep things simple, libs will hold every library used in the projects as a git submodule if possible.
```sh
- libs
- project-folder
  <> project-code.ino 
- another-project
  <> another-code.cpp
- README.md
- LICENSE 
```

I'll see if keeping the projects in separate branches then merging them to master will work better than keeping everything togheter ¯\\\_(ツ)_/¯