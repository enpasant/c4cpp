#!/bin/bash
if [ -e "/usr/bin/c4cpp" ]; then
	stype="rmc"
	echo "Would you like to remove c4cpp? (y/n) "
	read choicerm
	if [ "$choicerm" = "y" ]; then
		sudo rm /usr/bin/c4cpp
		echo "Done."
	else
		echo "Abort."
	fi
fi

if [ ! -e "/usr/bin/c4cpp" ]; then
	if [ "$stype" = "rmc" ]; then
		echo "Script ended"

	else 
		echo "Would you like to extract c4cpp to /usr/bin/? (y/n)"
		read choiceex
		if [ "$choiceex" = "y" ]; then
			echo "Building c4cpp..."
			g++ main.cpp -o c4cpp
			sudo mv c4cpp /usr/bin/
			echo "Compiled and extracted."
		else
			echo "Abort."
		fi
	fi
fi

