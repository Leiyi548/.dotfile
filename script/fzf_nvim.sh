#!/usr/bin/env bash

fd -t f --exclude=.git | fzf --reverse --prompt=nvim\>\ --height=40% | xargs nvim
