#!/usr/bin/env bash
rm ~/.shell.lok*



ls ~/ | grep Imager &> /dev/null
if [ $? == 1 ];
then
	mkdir ~/Imager
else
	echo "It Imager is!! "
fi

feh --randomize --bg-fill ~/Imager/ &> /dev/null
sleep 1800
touch ~/.shell.lok$$ 

while true
do
	ls -a ~/ | grep shell.lok$$ &> /dev/null
	if [ $? == 1 ];
	then
		echo "退出"$$
		exit;
	fi
	feh --randomize --bg-fill ~/Imager/
	echo "1"
	sleep 1800
done
