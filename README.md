# SDL_Game_overhead_perspective
In order for it to work you need to download:
SDL2
SDL2_ttf (optional)
SDL2_image
SDL2_mixer (optional)

You can learn more about how to set up SDL here: 
https://www.youtube.com/watch?v=DgpcRIK2uug

## Dependencies

- **SDL2**: The Simple DirectMedia Layer is required for rendering and handling input.
- **SDL2_ttf** (Optional): This library provides TrueType font rendering support.
- **SDL2_image**: Required for loading various image formats.
- **SDL2_mixer** (Optional): Use this library for audio mixing and sound effects.

## Installation

### Linux (Debian/Ubuntu)

You can install the required dependencies on Debian/Ubuntu using `apt`:

```bash
sudo apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev
To install optional dependencies, use:
sudo apt-get install libsdl2-mixer-dev

Windows
For Windows, download the precompiled libraries from the official SDL2 website and follow the installation instructions.

macOS
You can use Homebrew to install the required libraries:
brew install sdl2 sdl2_ttf sdl2_image
For optional dependencies, use:
brew install sdl2_mixer
