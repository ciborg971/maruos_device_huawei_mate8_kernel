set system_img=system_4k.img
echo "######################  burn log  start  ############################" >>burn_log.txt
echo "%date% %time%">>burn_log.txt
::先识别页大小，然后根据页大小动态烧写对应的system镜像
fastboot -i 0x12d1 getvar pagesize 2>&1 | find "2048" && set system_img=system_2k.img
echo %system_img% >> burn_log.txt 2>&1
fastboot -i 0x12d1 flash ptable ptable.bin >> burn_log.txt 2>&1
fastboot -i 0x12d1 flash m3boot m3boot.bin >> burn_log.txt 2>&1
fastboot -i 0x12d1 flash m3image bsp_mcore.bin >> burn_log.txt 2>&1
fastboot -i 0x12d1 flash fastboot fastboot.img >> burn_log.txt 2>&1
fastboot -i 0x12d1 flash kernel boot.img >> burn_log.txt 2>&1
fastboot -i 0x12d1 flash modem balong_modem.bin >> burn_log.txt 2>&1
fastboot -i 0x12d1 erase system >> burn_log.txt 2>&1
echo "burn的方式已经变化，烧写LOG请看burn_log.txt"
fastboot -i 0x12d1 flash system %system_img% >> burn_log.txt 2>&1
fastboot -i 0x12d1 flash dts modem_dt.img >> burn_log.txt 2>&1
fastboot -i 0x12d1 flash dsp lphy.bin >> burn_log.txt 2>&1
fastboot -i 0x12d1 flash hifi hifi.bin >> burn_log.txt 2>&1
fastboot -i 0x12d1 flash cbbe xphy_mcore.bin >> burn_log.txt 2>&1
fastboot -i 0x12d1 flash nvdload nv.bin >> burn_log.txt 2>&1
fastboot -i 0x12d1 reboot-bootloader >> burn_log.txt 2>&1
ping -n 2 127.0.0.1>nul
echo "%date% %time%">>burn_log.txt
echo "######################  burn log  end  ############################" >>burn_log.txt

