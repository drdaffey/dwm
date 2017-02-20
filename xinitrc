while true; do dwm-xsetroot; done &
xrandr --output VGA-0 --auto --right-of DVI-0 &
setxkbmap -layout us,bg -variant ,phonetic -option grp:sclk_toggle &
compton -bcCGf -i 0.6 -e 0.8 --inactive-dim 2 --focus-exclude "x = 0 && y = 0" --backend glx --vsync opengl-swc --paint-on-overlay &
sh -c 'while true; do xfce4-clipman; done' &
feh --bg-tile ~/Pictures/tile1.jpg &
xset b off &
xmodmap -e "keycode 108 = Super_L" -e "remove mod1 = Super_L"
xmodmap -e "keycode 108 = Super_L" -e "remove mod1 = Super_L"

#case "$1" in
#awesome) awesome;;
#dwm) /home/dach/bin/dwm-start;;
#xfce) exec startxfce4;;
#i3) i3;;
#*) /home/dach/bin/dwm-start;;
#esac
/home/dach/bin/dwm-start
