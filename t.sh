ARG="2 1 0"; ./push_swap $ARG | ./checker_linux $ARG
ARG=$(bash number.sh 3); ./push_swap $ARG | ./checker_linux $ARG
ARG="1 5 2 4 3"; ./push_swap $ARG | ./checker_linux $ARG
ARG=$(bash number.sh 5); ./push_swap $ARG | ./checker_linux $ARG
ARG=$(bash number.sh 100); ./push_swap $ARG | ./checker_linux $ARG
ARG=$(bash number.sh 100); ./push_swap $ARG | wc -l 
ARG=$(bash number.sh 500); ./push_swap $ARG | ./checker_linux $ARG
ARG=$(bash number.sh 500); ./push_swap $ARG | wc -l 
