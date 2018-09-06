# A place for my random IoT Stuff

## What will you find here?
Some of my personal projects, involving the Intel Genuino UNO 101, ESP8266 and Raspberry Pi.

## What is the purpose of this repository?
Since I mentor a small group who seek to learn embedded programming and IoT concepts, I'm starting a proper place to store my codes, so I don't end up looking silly when they ask for it.

---

## Repo Structure
To keep things simple, the ```libs``` folder will hold every library used in the projects as a git submodule whenever possible. I'll also use PlatformIO (https://platformio.org/) structure to better enable user made libraries, using the ```lib_extra_dirs = ..\libs``` options on ```platformio.ini``` file. The ```lib``` (singular) folder will contain only some very specific libraries for that project, generic libraries go in ```libs```. 

What I want with all this is to have all the projects working on the go, the user will only need to clone the repository and compile/upload it using PlatformIO, instead of going through the hassle of instaling libraries to the global Arduino Library Folder.

The structure will look something like this:

```sh
IosTuff
│
├───libs
│   ├───user-made-lib
│   └───git-submodule-lib
│       ├───src
│       └───examples
│           
├───some-project
│   ├───platformio.ini
│   ├───lib
│   │   ├───very-specific-lib.h
│   │   └───very-specific-lib.cpp
│   └───src
│       └───some-code.ino
│
├───other-project
│   ├───platformio.ini
│   ├───lib
│   └───src
│       └───other-code.ino
├─ .gitignore
├─ .gitmodules
├─ README.md
└─ LICENSE 
```

I'll see if keeping the projects in separate branches then merging them to master will work better than keeping everything togheter ¯\\\_(ツ)_/¯
