# TRJ

TRJ is a Windows console application written in C using the Win32 API.  
It provides basic system-related utilities such as logical drive enumeration and system information retrieval (currently in development).

## Features

At this stage, TRJ includes the following functionality:

- Displays a list of logical drives along with their types:
  - Fixed disks
  - Removable drives
  - Network drives
  - CD-ROM drives

- System information module (work in progress)

- Adds the application to Windows startup via the registry key:
  `HKCU\Software\Microsoft\Windows\CurrentVersion\Run`

## Project Structure

The project is organized into modular components for better maintainability:

- `src/Trj.c` — entry point of the application, handles main menu logic
- `src/modules/` — menu navigation and user interaction logic
- `src/registry/` — Windows Registry operations and drive type detection
- `src/utils/` — helper functions (input validation and utility routines)

## Requirements

- Windows 10/11 (or compatible Windows version with Win32 API support)
- C compiler with Windows API support:
  - MSVC (`cl.exe`) or
  - Clang for Windows

## Build

### Using Clang

```powershell
clang.exe src\Trj.c src\modules\modules.c src\registry\registry.c src\utils\utils.c -o trj.exe
