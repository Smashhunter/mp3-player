# mp3-player — CLI music player

A small command-line application to play MP3 files and manage simple playlists.

**Quick summary:** lightweight, console-driven music player using SFML for audio playback. Intended as a learning / hobby project and a minimal local media tool.

## Features

- **Play audio:** play MP3 files from local disk.
- **Console interface:** simple menu-driven controls for playback and playlists.
- **Playlist support:** enqueue and manage tracks via a small repository layer.

## Prerequisites

- C++ compiler (g++ / clang++)
- CMake (recommended)
- Build tools: make, ninja, etc.
- On Debian/Ubuntu you can install common tools with:

```bash
sudo apt update
sudo apt install build-essential cmake libsfml-dev
```

Note: this repository includes SFML sources in the build tree for convenience, but having system SFML installed can simplify the build.

## Build (CMake)

1. Create a build directory and run CMake:

```bash
mkdir -p build
cd build
cmake ..
cmake --build . --config Release
```

1. After a successful build, locate the produced executable in the `build` tree. If you are unsure of the binary name, run:

```bash
find build -type f -executable -maxdepth 3 -print
```

## Build (single-file compile)

For quick experiments you can also compile an individual source file using the provided VS Code task or a simple g++ command pointed at a specific .cpp file (not recommended for full builds).

## Run

- Run the executable discovered in the previous step. Example (replace with the actual path from your build):

```bash
./build/<executable-name>
```

- The program uses a console menu. Follow on-screen prompts to load tracks, play, pause, and manage playlists.

## Project layout (important files)

- **[src/main/main.cpp](src/main/main.cpp)**: program entry point and app bootstrap.
- **[src/lib/PlayerApplication.cpp](src/lib/PlayerApplication.cpp)**: main application loop and console UI.
- **[data-source/TrackRepository.hpp](data-source/TrackRepository.hpp)**: simple track repository used by the player.
- **CMakeLists.txt**: top-level CMake configuration for building the project.

## Contributing

- Open an issue or a pull request for bugs, improvements, or feature ideas.
- Keep changes small and focused; add small, descriptive commits.

## License

This project does not include a license file. If you want this repository to be open-source, consider adding a LICENSE (for example, MIT).

## Next steps / ideas

- Add support for more audio formats.
- Improve playlist persistence (save/load playlists).
- Add unit tests and CI build.

Enjoy — open an issue if something breaks or if you want help building or extending the player.
