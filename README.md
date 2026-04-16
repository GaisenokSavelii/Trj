# TRJ

`TRJ` is a Windows console application written in C.

## Description

The program performs two main tasks:

- Displays a list of logical drives and their types: fixed, removable, network, CD-ROM, and more.
- Adds the application to Windows startup by writing to the registry key `HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Run`.

## Project Structure

- `src/Trj.c` — main entry point, displays the menu and manages navigation.
- `src/core/` — screen switching logic and user input handling.
- `src/RegeditFunctions/` — registry functions and drive type detection.
- `src/utils/` — utility function for input validation.

## Features

- Uses Windows API:
  - `GetLogicalDrives`
  - `GetDriveTypeW`
  - `RegOpenKeyExW`
  - `RegSetValueExW`
- Supports UTF-8 output in the console.
- Modular architecture for easier maintenance and extension.

## Build

Use a compiler that supports the Windows API, such as `clang` or `cl`.

```powershell
clang.exe src\Trj.c src\core\core.c src\RegeditFunctions\RegFunctions.c src\utils\utils.c -o trj.exe
```

## Run

Run `trj.exe` from a Windows console.

> This program only works on Windows and uses the Win32 API.
