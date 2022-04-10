BROWSER=/usr/local/bin/chrome
EDITOR=/usr/local/bin/vim
HISTFILE=~/.ksh_history
HISTSIZE=10000
SAVEHIST=10000
export EDITOR=vim
export LANG=en_US.UTF-8
export VISUAL=vim
export FFF_OPENER=opener
export FCEDIT=$EDITOR
export LC_CTYPE=en_US.UTF-8
export BROWSER=chrome
# Aliases
alias ..='cd ..'
alias ...='cd ../..'
#alias sudo="doas"
alias cmatrix="cmatrix -s -s" 
alias xi="doas xbps-install" 
alias xr="doas xbps-remove -R" 
alias xq="doas xbps-query"
alias mc="doas make clean install"
alias disk="ncdu"
alias ls='exa -l'
alias la='exa -la'
alias df='df -h'

set -o emacs
alias __A=`echo "\020"`     # up arrow = ^p = back a command
alias __B=`echo "\016"`     # down arrow = ^n = down a command
alias __C=`echo "\006"`     # right arrow = ^f = forward a character
alias __D=`echo "\002"`     # left arrow = ^b = back a character
alias __H=`echo "\001"`     # home = ^a = start of line
alias __Y=`echo "\005"`     # end = ^e = end of line


# Add Color
alias egrep='grep --color=auto'
pokemon-colorscripts -r | sed '1,2d'
PCNAME="box"
PS1='\033[32m${USER}\033[35m@\033[34m${PCNAME} \033[33m${PWD} \033[36m\n\$\033[0m'
export PS1


#afetch 
