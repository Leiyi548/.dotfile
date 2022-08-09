#! /bin/bash
# DWM自启动脚本

settings() {
    [ $1 ] && sleep $1
    xset s 600
    xset -b
    syndaemon -i 1 -t -K -R -d
    xss-lock -- ~/scripts/app-starter.sh blurlock &
    ~/scripts/set-screen.sh &
}

daemons() {
    [ $1 ] && sleep $1
    fcitx5 &
    nm-applet &
    flameshot &
    xfce4-power-manager &
    dunst -conf ~/scripts/config/dunst.conf &
    # lemonade server &
    ~/scripts/app-starter.sh picom &
}

every1s() {
  ~/scripts/dwm-status.sh &
}

every10s() {
    [ $1 ] && sleep $1
    while true
    do
        ~/scripts/set-screen.sh check &
        ~/scripts/dwm-status.sh &
        sleep 10
    done
}

every300s() {
    [ $1 ] && sleep $1
    while true
    do
        ~/scripts/dwm-status.sh &
        sleep 300
    done
}

every1000s() {
    [ $1 ] && sleep $1
    while true
    do
        xset -b
        # xmodmap ~/scripts/config/xmodmap.conf
        sleep 1000
        [ "$WALLPAPER_MODE" = "PIC" ] && ~/scripts/set-wallpaper.sh &
    done
}

settings 1 &
daemons 3 &
every1s &
# every10s 5 &
# every300s 30 &
every1000s 30 &
