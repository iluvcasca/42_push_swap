#!/bin/bash

nb=$1
list=$2
# Initialize an empty array
results=()

# Assume 'command' is the command whose results you want to average
for ((i=1; i<=$nb; i++)); do
  # Replace 'command' with the actual command you want to execute
  result=$(ARG=$(bash number.sh $list); ./push_swap "$ARG" | wc -l)
  results+=($result)
done
# Calculate the sum of the results
sum=0
for num in "${results[@]}"; do
  let sum+=num
done

# Calculate the average
length=${#results[@]}
average=$(echo "scale=0; $sum/$length" | bc -l)

# Print the average
echo "The average for $1 runs on $2 numbers is: $average"

