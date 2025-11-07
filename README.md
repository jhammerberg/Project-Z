# Project-Z

## Setup Commands
git clone Project-Z
cd Project-Z
uv venv
activate venv
uv pip install --upgrade pip
uv pip install west
west init -l .
west update
west packages pip --install
west zephyr-export
west sdk install
west build nucleo-blinky