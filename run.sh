#!/usr/bin/env bash

FOLDER_NAME="julia_diplo_$(date '+%b_%d_%H_%M_%S')"
mkdir -p results/$FOLDER_NAME

cd attemption_for_08/attemption_for_08
CPPS=`find . -type f -name '*.cpp' -printf "%f\n"|grep -v "^log.cpp$"`
#g++ analysis1.cpp Between_structs.cpp FifthProc.cpp FirstProc.cpp FourthProc.cpp fRand.cpp GLOBAL_CONST.cpp increase_d1.cpp Kolmqvant.cpp log.cpp main.cpp New_struct.cpp Poison.cpp Processing_Func.cpp
g++ $CPPS -o ../../results/$FOLDER_NAME/program.exe -lm

cd ../../results/$FOLDER_NAME
./program.exe