#!/bin/bash
# Arguments: 	
#		$1 - first randomgen number 
#		$2 - second randomgen number 
#		$3 - winVal
#		$4 - drawVal 
#		$5 - num generations 
#		$6 - size population  

prefix="./"; 
outputFile="OutputFiles/"; 
programOriginal="TTTEvolver.exe";  

for ((i=$1; i<=$2; i++)); do
	echo $i; 
	$prefix$programOriginal $i $prefix$outputFile $3 $4 $5 $6; 
done