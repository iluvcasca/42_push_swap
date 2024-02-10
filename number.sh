# Define the number of unique random numbers to generate
num=$1

# Initialize an empty array
random_numbers=()

# While the length of the array is less than num
while [[ ${#random_numbers[@]} -lt $num ]]; do
    # Generate a random number
    random_number=$(( RANDOM % 5000 + 1 ))

    # If the random number is not already in the array, add it
    if ! [[ " ${random_numbers[@]} " =~ " ${random_number} " ]]; then
        random_numbers+=(${random_number})
    fi
done

# Print the array of unique random numbers
echo "${random_numbers[@]}"

