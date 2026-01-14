cmake_minimum_required(VERSION 3.20.0)

set(BOARD esp32_devkitc/esp32/procpu) # default board 
list(APPEND ZEPHYR_EXTRA_MODULES ../modules/lib/open62541/arch) # Open 62541's zephyr module is not in it's root so we do this hack

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(esp32-open65241)

# --- Open62541 Configuration ---
zephyr_compile_definitions(zsock_fd_set=zvfs_fd_set) # fix build error with size of fd_set
set(UA_ARCHITECTURE "zephyr")
set(UA_NAMESPACE_ZERO "MINIMAL") # needed to fit on esp32

# 1. Disable PubSub (Huge savings)
set(UA_ENABLE_PUBSUB OFF)

# 2. Disable Encryption (Removes MbedTLS dependency = Huge RAM savings)
set(UA_ENABLE_ENCRYPTION OFF)

# 3. Disable Discovery Multicast (Saves network buffers)
set(UA_ENABLE_DISCOVERY_MULTICAST OFF)
set(UA_ENABLE_DISCOVERY OFF)
# set(UA_ENABLE_SUBSCRIPTIONS OFF CACHE BOOL "" FORCE)

set(UA_ENABLE_SERVER ON)
# set(UA_ENABLE_CLIENT OFF)

target_link_libraries(app PUBLIC open62541)
target_sources(app PRIVATE src/main.c)