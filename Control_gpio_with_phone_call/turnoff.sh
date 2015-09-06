#!/bin/sh

if [ ! -d /sys/class/gpio/gpio24 ]; then  
	echo " Exporting GPIO24"
	echo 24 > /sys/class/gpio/export
fi 

echo "out" > /sys/class/gpio/gpio24/direction

	echo "0" > /sys/class/gpio/gpio24/value 
