# Void Linux dots

My Void Linux setup with customized DWM suckless UI and scripts. Awesome picom animations and black theme experience!!

## Installation

1. You will need a minimal Void Linux installation.  
2. Clone the repo `git clone https://github.com/unixobserver/voidlinuxdots.git' and run `sudo xbps-install oksh`
3. Run `chsh -s /bin/oksh` logout and relogin
4. cd on  ***voidlinuxdots*** folder and `chmod +x install_progs` and run it `./install_progs`
5. `cd ~/voidlinuxdots/.local/suckless` and `doas make clean install`  inside on each folder (dwm, dmenu, st, dwmblocks)
6. Copy all files from ~/voidlinuxdots to your home directory ~/
7. Run `chmod +x ~/.local/bin/*` and `xdg-user-dirs-update`. Put your songs in the Music folder and `mkdir ~/Videos/movies` and put inside your movies. 
8. Enjoy!!


## Basic Shortcuts

- **mod4 + enter        :** launch terminal
- **mod4 + shift +enter :** scratchpad term
- **mod4 + d            :** dmenu app launcher 
- **mod4 + shift +d     :** disk utility  
- **mod4 + q            :** close apps 
- **mod4 + f            :** fullscreen
- **mod4 + shift + f    :** floating windows mode
- **mod4 + t            :** tabbed windows mode
- **mod4 + space        :** swap windows
- **mod4 + shift + q    :** reboot-poweroff-logout-lock 
- **mod4 + e            :** launch fff file manager
- **mod4 + shift + e    :** launch pcmanfm file manager
- **mod4 + p            :** launch nsxiv picture browser
- **mod4 + shift + p    :** launch pulsemixer
- **mod4 + ]            :** increase volume
- **mod4 + shift + ]    :** dmenu wallpaper selector
- **mod4 + [            :** decrease volume
- **mod4 + n            :** launch newsboat news
- **mod4 + shift + n    :** launch notes preview
- **mod4 + i            :** launch htop
- **mod4 + shift + i    :** launch top
- **mod4 + o            :** launch Orca-C sequencer
- **mod4 + shift + o    :** launch lmms DAW
- **mod4 + m            :** launch ncmpcpp player
- **mod4 + shift +m     :** launch dmenu movies playlist
- **mod4 + v            :** play random song with mpv 
- **mod4 + F5           :** mount usb flashdrive
- **mod4 + F6           :** ffmpeg sreen + audio recording
- **mod4 + F7           :** kill ffmpeg
- **mod4 + `            :** scrot screenshot 
- **mod4 + w            :** launch web browser (install ublock-origin, dark-reader plugins and complete black chrome theme)
