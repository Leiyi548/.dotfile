syntax on
set nu
set rnu
set hlsearch
set incsearch
set ignorecase
set noswapfile
set so=8
set mouse=a

let mapleader=" "
set timeoutlen=500

" I hate click this key
nnoremap H ^
nnoremap L $
vnoremap H ^
vnoremap L $
nnoremap > >>
nnoremap < <<

nnoremap Y y$
nnoremap <leader>h :nohl<cr>
nnoremap <leader>q :qa!<cr>

" use system clipboard
nnoremap <leader>Y "+Y
nnoremap <leader>P "+P
nnoremap <leader>y "+y
nnoremap <leader>p "+p

" auto change input method fcitx5
autocmd InsertLeave * :silent !fcitx5-remote -c " 退出插入模式时禁用输入法
autocmd BufCreate *  :silent !fcitx5-remote -c " 创建 Buf 时禁用输入法
autocmd BufEnter *  :silent !fcitx5-remote -c " 进入 Buf 时禁用输入法
autocmd BufLeave *  :silent !fcitx5-remote -c " 离开 Buf 时禁用输入法

