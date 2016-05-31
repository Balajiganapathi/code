set nocompatible
set cursorline
set bg=dark
set autoindent
set smartindent
set tabstop=4
set shiftwidth=4
set expandtab
set number
set smartcase
set ignorecase
set wildmenu
set backspace=indent,eol,start
set showcmd
set showmatch
set scrolloff=5
set sidescrolloff=5
set history=5000
set ttyfast
set tags=tags;/
set wrap
set formatoptions=tcrql

syn on

" Force write via sudo
cmap w!! w !sudo tee > /dev/null %

" Templates
au BufNewFile *.cpp 0r ~/code/template.cpp

filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'
Plugin 'chrisbra/histwin.vim'
Plugin 'scrooloose/syntastic'
Plugin 'Mizuchi/STL-Syntax'

call vundle#end()            " required
filetype plugin indent on    " required

" Infinite undo history
set undolevels=1000
set undoreload=10000
set undofile
set undodir=~/.vim/undodir

" For displaying undo tree
nnoremap <F5> :GundoToggle<CR>

" Syntastic
set statusline+=%#warningmsg#
set statusline+=%{SyntasticStatuslineFlag()}
set statusline+=%*

let g:syntastic_always_populate_loc_list = 1
let g:syntastic_auto_loc_list = 1
let g:syntastic_check_on_open = 1
let g:syntastic_check_on_wq = 0

let g:syntastic_cpp_compiler = 'g++'
let g:syntastic_cpp_compiler_options = ' -std=c++11 -D LOCAL'

