time for (( c=1; c<=200; c++ )) do A="$($LE_PROMPT_EXE $0 $? $LE_PROMPT_CONFIG)"; done
time for (( c=1; c<=100; c++ )) do A="$($POWERLINEGO -error $?)"; done
