#!/usr/bin/env bash


# check-files <file1> <file2> ...
function check-files {
	file_list="$@"
	missing_list=""
	for file in $file_list ; do
		if [ ! -f "$file" ] ; then missing_list+="$file " ; fi
	done
	if [ -n "$missing_list" ] ; then
		warning "Error! ${wh} Missing files: ${missing_list}"
		exit 1
	fi
}

# check-folders <dir1> <dir2> ...
function check-folders {
	dir_list="$@"
	missing_list=""
	for dir in $dir_list ; do
		if [ ! -d "$dir" ] ; then missing_list+="$dir " ; fi
	done
	if [ -n "$missing_list" ] ; then
		warning "Error! ${wh} Missing folders: ${missing_list}"
		exit 1
	fi
}


# remove-comments
# Remove all comments and white spaces
# Usage: remove-comments '[comment character]' <input file> (> <output file>)
function remove-comments {
	cmnt_character="$1"
	input="$2"
	if [ -z "$input" ] ; then input="/dev/stdin" ; fi
	grep -o '^[^'"$cmnt_character"']*' "$input" | sed '/^[[:space:]]*$/d'
}

# print-block
# Description: 	Print text between two different patterns
# Usage: 		print-block "<pattern1>" "<pattern2>" <input file> (> <output file>)
function print-block {
	pattern1="$1"
	pattern2="$2"
	input="$3"
	if [ -z "$input" ] ; then input="/dev/stdin" ; fi
	sed -n -r '/'"$pattern1"'/,/'"$pattern2"'/p' "$input"
}



# transpose
# Description: 	Transpose rows and columns in the file/text (SPACE separated)
# Usage: 		transpose (<input>)
# Source:       https://stackoverflow.com/a/1729980
function transpose {
	input="$1"
	if [ -z "$input" ] ; then input="/dev/stdin" ; fi
awk '
{ 
    for (i=1; i<=NF; i++)  {
        a[NR,i] = $i
    }
}
NF>p { p = NF }
END {    
    for(j=1; j<=p; j++) {
        str=a[1,j]
        for(i=2; i<=NR; i++){
            str=str" "a[i,j];
        }
        print str
    }
}' $input
}

# print-banner
# Description: 	Print centered banner on terminal
# Usage: 		print-banner "<text>"
# Source:       https://unix.stackexchange.com/a/267730
function print-banner {
	char="$1"
	text="$2"
	termwidth="$(tput cols)"
	padding="$(printf '%0.1s' ${char}{1..500})"
	if [ -z "$text" ] ; then
		printf "%*.*s\n" "$termwidth" "$termwidth" "$padding"
	else
		printf '%*.*s %s %*.*s\n' 0 "$(((termwidth-2-${#text})/2))" "$padding" "$text" 0 "$(((termwidth-1-${#text})/2))" "$padding"
	fi
}


# run-with-time
# Description: 	Run commands and print runtime at the end
# Usage: 		run-with-time <commands>
function run-with-time {
	input="$@"
	if [ -z "$input" ] ; then input="/dev/stdin" ; fi
	start_time=$( date "+%s" )
	eval "$input"
	end_time=$( date "+%s" )
	run_time_sec=$( echo "$start_time $end_time" | awk '{print $2-$1}' )
	run_time=$( date -d@$run_time_sec -u "+%H:%M:%S" )
	echo "Runtime: $run_time"
}


# printf-wrap
# Description: 	Printf with smart word wrapping for every columns.
# Usage: 		print-wrap "<format>" "<text>" "<text>" ...
function printf-wrap {
	# help info
	help_message="Usage: print-column-wrap \"<format>\" \"<text>\" \"<text>\" ..."
	if [[ "$1" =~ ^(-|--)?(h|help)$ ]] ; then echo "$help_message" ; return 0 ; fi 
	# parse argument
	format="$1"
	width=( $( echo "$format" | sed -r 's/%%|\\%//g' | sed -r 's/%/\n%/g' | sed -n -r 's/^%[^1-9]*([0-9]+).*/\1/p' ) )
	shift
	text=( "$@" )
	error_message="Error: number of input text fields (${#text[@]}) MUST NOT EXCEED number of columns specified (${#width[@]}) !"
	if (( ${#text[@]} > ${#width[@]} )) ; then echo "$error_message" ; return 1 ; fi
	# printing
	while [ -n "$( echo "${text[@]}" | sed -r 's/\s+//g' )" ] ; do
		text_cut=()
		width_cut=()
		for i in ${!text[@]} ; do
			text[$i]="$( echo "${text[$i]}" | sed -r 's/^\s+//' )"
			if [[ "${text[$i]:${width[$i]}-1:2}" =~ [a-zA-Z0-9_]{2} ]] ; then
				text_cut[$i]="$( echo "${text[$i]:0:${width[$i]}}" | sed -r 's/\w+$//' )"
			else
				text_cut[$i]="${text[$i]:0:${width[$i]}}"
			fi
				width_cut[$i]=${#text_cut[$i]}
				text[$i]="${text[$i]:${width_cut[$i]}}"
		done
		printf "$format" "${text_cut[@]}"
	done
}

# tput-colors
# Description: 	Demonstrate tput color combinations.
# Usage: 		tput-colors
# Source:		http://linuxcommand.org/lc3_adv_tput.php
function tput-colors {
	for fg_color in {0..7}; do
	    set_foreground=$(tput setaf $fg_color)
	    for bg_color in {0..7}; do
	        set_background=$(tput setab $bg_color)
	        echo -n $set_background$set_foreground
	        printf ' F:%s B:%s ' $fg_color $bg_color
	    done
	    echo $(tput sgr0)
	done
}

# git-log
# Description: 	show git log with pretty formatting
# Usage: 		git-log
# Source:		https://opensource.com/article/20/1/bash-scripts-aliases
alias git-log='git log --decorate=short --date=relative --date-order --format=format:"%C(blue)%h%C(reset) - %C(green)(%ar)%C(reset) %C(white)%s%C(reset) %C(dim white)- %an%C(reset)%C(auto)%d%C(reset)"'
