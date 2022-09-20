#!/usr/bin/env bash

DIR=`pwd`
FDIR="$HOME/.local/share/fonts"

# insatll fonts

install_fonts() {
	echo -e "\n[*] Installing font ..."
	if [[ -d "$FDIR" ]]; then
		cp -rf $DIR/fonts/* "$FDIR"
	else
		mkdir -p "$FDIR"
		cp -rf $DIR/fonts/* "$FDIR"
	fi
}

main(){
  install_fonts
}

main
