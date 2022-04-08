# Wireless-Tempurature-Probe

In this project I created a tempurature probe that was connected to an esp-32 chip.
The micro controller code is in the "ESP Arduino Code" folder

This project also contains a windows service that I created in the "ESP-Server" folder.
I set this service to run on my PC at startup, and it would collect any tempurature data that was sent by the ESP-32 over wifi.
Data is collected in a SQL database. 
