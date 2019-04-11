time for (( c=1; c<=100; c++ )) do A="$($POWERLINE_EXE $0 $? $POWERLINE_CONFIG)"; done
time for (( c=1; c<=100; c++ )) do A="$($POWERLINEGO -error $?)"; done