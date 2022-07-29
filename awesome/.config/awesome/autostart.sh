#!/usr/bin/env bash


function run {
  if ! pgrep -f $1 ;
  then
    $@&
  fi
}

# Resolution
#xrandr --output HDMI1 --mode 1920x1080 --same-as eDP1 --auto &
xrandr --output HDMI-1 --auto --primary
xrandr --output eDP-1 --right-of HDMI1 --auto
xrandr --output eDP-1 --rotate left

# Compositor
systemctl start v2raya.service
picom --config ~/.config/awesome/config/picom.conf &
run clash
run fcitx5
run flameshot
run obs
run qv2ray
# open start emacs server
run emacs --daemon

####  swap Esc caps
setxkbmap -option caps:swapescape
###  Change the wallpaper
~/.config/awesome/backgrund.sh
