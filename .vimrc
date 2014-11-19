set number
set nowrap
set t_Co=256
set title
set list
set listchars=tab:\|\ 
set cursorline
set cursorcolumn
set noswapfile

"2 space indentings 
set expandtab
set shiftwidth=2
set softtabstop=2

syntax on
set foldmethod=syntax
"colorscheme desert
"color codeschool
color abra
set nocompatible      " We're running Vim, not Vi!
filetype on           " Enable filetype detection
filetype indent on    " Enable filetype-specific indenting
filetype plugin on    " Enable filetype-specific plugins

" Highlight after 80 characters
"highlight overlength ctermbg=red ctermfg=white guibg=#592929
"match overlength /\%81v.\+/

execute pathogen#infect()

function F(name)
execute "vim /".a:name."/gj **/*.rb"
cw
endfunction

function F_all(name)
execute "vim /".a:name."/gj **/*.*"
cw
endfunction

set runtimepath^=~/.vim/bundle/ctrlp.vim
map <S-F> :NERDTreeToggle<CR>
nmap <C-h> ^
nmap <C-l> $
nmap <C-j> <C-d>
nmap <C-k> <C-u>
"Search for word under curson in all files and show the quickfixlist
nnoremap <C-f> "zyiw :vim /<C-R>z/gj **/*.rb<CR>:cw<CR><CR>
if !exists( "*RubyEndToken" )

function RubyEndToken()
      let current_line = getline( '.' )
          let braces_at_end = '{\s*\(|\(,\|\s\|\w\)*|\s*\)\?$'
	      let stuff_without_do = '^\s*\(class\|if\|unless\|begin\|case\|for\|module\|while\|until\|def\)'
		            let with_do = 'do\s*\(|\(,\|\s\|\w\)*|\s*\)\?$'
				          if match(current_line, braces_at_end) >= 0
					          return "\<CR>}\<C-O>O"
					 elseif match(current_line, stuff_without_do) >= 0
					        return "\<CR>end\<C-O>O"
					 elseif match(current_line, with_do) >= 0
					        return "\<CR>end\<C-O>O"
					 else
					       return "\<CR>"
					endif
endfunction

endif

imap <buffer> <CR> <C-R>=RubyEndToken()<CR>
"codeschool is better for diffing
if &diff
	colorscheme codeschool
end

"Hate the trailing spaces
match ErrorMsg '\s\+$'
"Removes trailing spaces
nnoremap rtw :%s/\s\+$//e<CR>
set encoding=utf-8
