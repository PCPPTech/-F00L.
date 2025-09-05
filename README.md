# $F00L.
An open source CLI Terminal made with C++.

# Status:
## Version 1.0.0 (2025. 08. 30)
- Lightweight, 0 customisability, basic commands. If command is not on the `help` (`--help`) list, then it directly uses window's CMD to execute it (this is for other terminal CLI's, like terminal-based code editors).
## Version 1.1.0 (2025. 09. 01)
- Added working directory (current path) color customization via `color {your_color}`. Type `color` to get the list of colors.
- The picked color saves inside `data/wdcolor.txt`.
## Version 1.1.1 (2025. 09. 05)
- Added `[CONSOLE]` tag color customisation via `ctagc {your_color}`. Type `ctagc` for available console tag colors.
- The picked color saves inside `data/ctagcolor.txt`.
- Integrated comments to make the code more readable
