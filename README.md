# Project-Z
My personal Zephyr mono-repo to mess with it

## Repo Setup
A number of directories have been left out of the repo because they're either nested repositories or venvs, so you'll need to do a number of things to setup this repository. First you should refernece the [Zephyr getting started page](https://docs.zephyrproject.org/latest/develop/getting_started/index.html#getting-started-guide) to get the basic dependencies installed with Winget and set your 7z path in Windows but stop once you get to the virtual environment and follow these instructions.
1. Download and install `uv` from [here](https://docs.astral.sh/uv/getting-started/installation/) and `just` from [here](https://github.com/casey/just?tab=readme-ov-file#packages).
2. Clone this repository if you haven't already and enter it:
```bash
cd project-z
```
3. Make a new virtual environment in the base directory of this repository with `uv` and activate it:
```bash
uv venv .venv
.\.venv\Scripts\activate.ps1
```
> [!IMPORTANT]
> `venv` activation is different for each OS, for most unix systems this command is:
> ```bash source .venv/bin/activate ```
4. Install and setup `west`:
```bash
uv pip install --upgrade pip
uv pip install west
uv pip install -r zephyr\scripts\requirements.txt
```
5. Install the Zephyr SDK:
```bash
west sdk install
```
> [!NOTE]
> The Zephyr repository and SDK is multiple gigabytes in size, so all of this setup will take a very long time.

## Building and Flashing
Projects should have a `justfile` which should allow you to build and flash easily from inside of a project directory:
1. For building:
```bash
just build
```
2. For flashing:
```bash
just flash
```

If you are in the root workspace directory:
1. Build the selected project:
```bash
west build -p -d projects/<project>/build -b <board> projects/<project>
```
2. Flash the built project:
```bash
west flash -d projects/<project>/build
```

## Developing Notes
1. You must have built a project before intellisense in VS Code works
2. If you have just made a new project and intellisense is not working after building, try adding `<project>/.vscode/c_cpp_properties.json` with these contents:
```json
{
  "configurations": [
    {
      "name": "Zephyr",
      "compileCommands": "${workspaceFolder}/build/compile_commands.json"
    }
  ],
  "version": 4
}
```
3. Instructions for setting up Zephyr with VS Code debugger coming later...