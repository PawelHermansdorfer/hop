<p align="left">
<!-- <img src="./images/img.png" width="200" /> -->
<img src="./images/gif.gif" width="350" />
</p>


# 🎮 Controls
| Key       | Action                                                      |
|---------- |-------------------------------------------------------------|
| `d`       | Move to the right                                           |
| `a`       | Move to the left                                            |
| `SPACE`   | Jump/Start game                                             |
| `ESC`     | Exit game                                                   |

# ⚙️ How to run

## POSIX
### Dependencies
- [clang]
- [sdl2]
- [sdl2_ttf]
- [pkg-config]

```console
$ ./build.sh
$ ./build/main
```

## Windows MSVC
### Dependencies
- [MSVC 2015+][visual-studio]

```console
> .\setup_dependencies.bat
> .\build_msvc.bat --release
> .\build\main.exe
```

## Other
For other platforms I provided CMakeLists.txt for use with [cmake]

```console
$ mkdir ./build
$ cd build
$ cmake .. -Drelease=true
$ cmake --build ./
$ ./main
```

# 🔤 Font
https://www.1001fonts.com/the-jewish-bitmap-font.html

[visual-studio]: https://www.visualstudio.com/
[clang]: https://clang.llvm.org/
[cmake]: https://cmake.org/
[sdl2]: https://www.libsdl.org/
[sdl2_ttf]: https://wiki.libsdl.org/SDL_ttf/FrontPage
[pkg-config]: https://www.freedesktop.org/wiki/Software/pkg-config/
