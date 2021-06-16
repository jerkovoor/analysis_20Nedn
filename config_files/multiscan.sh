#!/bin/bash


if [ $# -lt 2 ]
then
        echo "Usage: multiScan FILE_STRING <OUTNAME> <CONFIGNAME> <NUMFILES>"
        exit 0
fi

FILE_NAME=$1
OUT_NAME="root_files/"$2
CONFIG_NAME=$3
LDF_DIR="data/"
TAIL="\ngo\n"
NUM_FILES=$4

if [ $# -lt 2 ]
then
        echo Using Default Config and OutputName
	OUT_NAME="./rootfiles"
	CONFIG_NAME="./Config_11Mods.xml"
     	NUM_FILES="9999" 
fi
if [ $# -lt 3 ]
then
        echo Using Default Config
	CONFIG_NAME="./Config_11Mods.xml" 
     	NUM_FILES="9999" 
fi
if [ $# -lt 4 ]
then
     	NUM_FILES="9999" 
fi



echo FileString $FILE_NAME
echo OutName: $OUT_NAME
echo ConfigName: $CONFIG_NAME

#OUTPUT_DIR="${HOME}/offline_root_files"
nF=0
#cmd="file $FILE_NAME.ldf$TAIL"
for i in `ls -rt $LDF_DIR$FILE_NAME*`
#for i in {1..$2}
do
	if [ $nF -lt $NUM_FILES ]; then
#    	echo $nF $NUM_FILES
	cmd=$cmd"file $i$TAIL"
	fi
((nF++))
done
cmd=$cmd"end\n"

echo Running command : $cmd
echo Kill Now if Anything is Wrong
sleep 10s

echo -e $cmd | utkscanor ./$OUT_NAME -c $CONFIG_NAME
