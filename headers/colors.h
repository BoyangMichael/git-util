#!/usr/bin/env bash

#################################################################
#####                                                       #####
#####  Utilities for Colors Using tput                      #####
#####  A bash script                                        #####
#####  Created by Boyang XU                                 #####
#####  (adpated from Julian Garrec's script)                #####
#####                                                       #####
################################################################# 


#################################################################
### Formatting by tput

# tput effects
bold=$(tput bold)
dim=$(tput setaf 8)
italic='\e[3m'
underlined_START=$(tput smul)
underlined_END=$(tput rmul)
rev=$(tput rev)
blink=$(tput blink)
invisible=$(tput invis)
standout_START=$(tput smso)
standout_END=$(tput rmso)
normal=$(tput sgr0)
# tput foreground colors
black=$(tput setaf 0)
red=$(tput setaf 1)
green=$(tput setaf 2)
yellow=$(tput setaf 3)
blue=$(tput setaf 4)
magenta=$(tput setaf 5)
cyan=$(tput setaf 6)
white=$(tput setaf 7)
# tput background colors
black_bg=$(tput setab 0)
red_bg=$(tput setab 1)
green_bg=$(tput setab 2)
yellow_bg=$(tput setab 3)
blue_bg=$(tput setab 4)
magenta_bg=$(tput setab 5)
cyan_bg=$(tput setab 6)
white_bg=$(tput setab 7)


#################################################################
### Formatting by escaped sequence

re='\e[1;31m'
ye='\e[1;93m'
gr='\e[1;32m'
grt='\e[0;32m'
bl='\e[1;34m'
cy='\e[1;36m'
OR='\e[48;5;95;38;5;214m'
or='\e[0;33m'
orb='\e[1;33m'
dre='\e[0;31m'
dye='\e[0;93m'
dgr='\e[0;32m'
dbl='\e[0;34m'
wh='\e[0m'
whb='\e[1m'
whi='\e[3m'
whu='\e[4m'
whd='\e[2m'
function pause {
        echo -e "${bl}$1"
        echo -e  "${dbl}   Ok?\n   Press any key to continue or Ctrl+C to stop me$wh"
        read -p ""
}
function pausedum {
        echo -en  "${dbl}-pause-$wh"
        read -p ""
}
function warning {
        echo -e "${re}$1${wh}"
}
function warningOR {
        echo -e "${OR}$1${wh}"
}
function note {
        echo -e "${ye}$1${wh}"
}
function error {
        me=`echo ${BASH_SOURCE[0]} | tr "/" " " | awk '{print $NF}'`
        echo -e "${re}\n\n${dre}[${me}]   ${re}${1}          ~~~ EXIT ~~~\n\n${wh}"
        exit
}
function softexit {
        echo -e "${gr}\n\n${1}          Job done.\n\n${wh}"
        exit
}
function comment {
        echo -e "${bl}${1}${wh}"
}
function commentn {
        echo -en "${bl}${1}${wh}"
}
function commentdb {
        echo -e "${dbl}${1}${wh}"
}
function commentdbn {
        echo -en "${dbl}${1}${wh}"
}
function commentcy {
        echo -e "${cy}${1}${wh}"
}
function commentg {
        echo -e "${gr}${1}${wh}"
}
function commentdg {
        echo -e "${dgr}${1}${wh}"
}
function commentdgn {
        echo -en "${dgr}${1}${wh}"
}
function commentgn {
        echo -ne "${gr}${1}${wh}"
}
function commentw {
        echo -e "${wh}${1}${wh}"
}
function commentwn {
        echo -en "${wh}${1}${wh}"
}
function highlight() {
        declare -A fg_color_map
        fg_color_map[black]=30
        fg_color_map[red]=31
        fg_color_map[green]=32
        fg_color_map[yellow]=33
        fg_color_map[blue]=34
        fg_color_map[magenta]=35
        fg_color_map[cyan]=36

        fg_c=$(echo -e "\e[1;${fg_color_map[$1]}m")
        c_rs=$'\e[0m'
        sed -u s"/$2/$fg_c\0$c_rs/g"
}


#################################################
### Symbols
symbol_check="\xE2\x9C\x94"
