#include <zephyr/kernel.h>

int main(void) {
    while (1) {
        k_sleep(K_SECONDS(1));
        printk("Hello from ESP32 Dev Board!\n");
    }
    return 0;
}