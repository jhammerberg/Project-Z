# Project-Z

My repository for trying out Zephyr. This repository is a "T2" style repository.

For most info, check out the excellent [Zephyr documentation](https://docs.zephyrproject.org/latest/index.html). This README will only cover setup instructions specific to how I've made this repository.

## Setup Commands
0. If you are on a Windows machine, do this in Windows and NOT in WSL. WSL will complicate the flashing process & permissions
1. Clone and enter this repository
```bash
git clone Project-Z
cd Project-Z
```
2. Setup and install `west`
```bash
uv venv
<activate venv for your os>
uv pip install --upgrade pip
uv pip install west
```
3. Install or update Zephyr
```bash 
west init -l .
west update
west packages pip --install
west zephyr-export
west sdk install
```
4. Build & flash whatever project you want
```bash
west build <some project directory> -p always
west flash
```