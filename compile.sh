#!/bin/bash 
OBJS="make_fsu.cxx  "      
OBJS+="check_pid.cxx " 
OBJS+="check_time.cxx " 
OBJS+="fill_tree.cxx " 
OBJS+="output.cxx "
OBJS+="input.cxx " 
OBJS+="save_output.cxx " 
OBJS+="process_hits.cxx "


#echo "g++ -g -o fsu_output $OBJS `grutinizer-config --cflags --all-libs --root`" 
g++ -g -o REDUCT $OBJS `grutinizer-config --cflags --all-libs --root` 


