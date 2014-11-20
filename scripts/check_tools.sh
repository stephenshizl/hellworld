#!/bin/sh
TOOLS=`which arm-linux-gnueabihf-gcc`
	if [ ! -f "$TOOLS" ]; then
		sudo apt-get install -y g++-arm-linux-gnueabihf	
	else
		echo "tools arm-linux-gnueabihf-gcc to build project......"
	fi
 

