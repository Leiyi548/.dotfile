#!/bin/sh

while true; do
	find ~/.dotfile/wallpaper -type f \( -name '*.jpg' -o -name '*.png' \) -print0 |
		shuf -n1 -z | xargs -0 feh --bg-scale
	# s 是秒 m是分钟
	sleep 15m
done

