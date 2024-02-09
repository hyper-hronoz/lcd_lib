openocd -f interface/stlink-v2.cfg -f target/stm32l1.cfg -c init -c "reset halt" -c "flash write_image erase ./build/target.bin 0x08000000" -c "reset"

