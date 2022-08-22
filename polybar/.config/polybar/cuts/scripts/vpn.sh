#!/usr/bin/env bash

pgrep openvpn >/dev/null && printf "online\n" || printf "offline\n"
