bash b.sh && bash o.sh && tmux new-session -s "openocd" -d "openocd -f interface/stlink.cfg -f target/stm32l1.cfg"
