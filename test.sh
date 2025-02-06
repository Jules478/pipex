GREEN='\e[1;32m'
PURPLE='\e[1;35m'
RESET='\033[0m'

echo -e "${PURPLE}
Valid Input

${RESET}"
valgrind --leak-check=full ./pipex infile "grep srcs" "wc -l" outfile
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Outfile Doesn't Exist

${RESET}"
valgrind --leak-check=full ./pipex infile "grep srcs" "wc -l" outfile2
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e  "${PURPLE}
Infile Doesn't Exist

${RESET}"
valgrind --leak-check=full ./pipex infile2 "grep srcs" "wc -l" outfile
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Command 1 Doesn't Exist

${RESET}"
valgrind --leak-check=full ./pipex infile "a" "wc -l" outfile
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Command 2 Doesn't Exist

${RESET}"
valgrind --leak-check=full ./pipex infile "grep srcs" "a" outfile
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Neither Command Exists

${RESET}"
valgrind --leak-check=full ./pipex infile "a" "a" outfile
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Multiple Commands

${RESET}"
valgrind --leak-check=full ./pipex infile "grep srcs" "wc -l" "wc -w" outfile
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Infile Permissions Removed

${RESET}"
chmod 111 infile
valgrind --leak-check=full ./pipex infile "grep srcs" "wc -l" outfile
chmod 777 infile
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Outfile Permissions Removed

${RESET}"
chmod 111 outfile
valgrind --leak-check=full ./pipex infile "grep srcs" "wc -l" outfile
chmod 777 outfile
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Relative Path

${RESET}"
valgrind --leak-check=full ./pipex infile "../push_swap/./push_swap '5 3 2 1 4'" "wc -l" outfile
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Absolute Path

${RESET}"
valgrind --leak-check=full ./pipex infile "/home/mpierce/Desktop/MainWork/push_swap/./push_swap 5 3 2 1 4" "wc -l" outfile
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Insufficient Commands

${RESET}"
valgrind --leak-check=full ./pipex infile "wc -l" outfile
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Sleep Test
${RESET}"
while true; do
    echo -ne "$(date +"%T")\r"
    sleep 1
done &
valgrind --leak-check=full ./pipex infile "sleep 10" "sleep 10" "sleep 10" "sleep 10" "sleep 10" "sleep 10" "sleep 10" "sleep 10" "sleep 10" outfile
kill $!
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
here_doc

${RESET}"
valgrind --leak-check=full ./pipex here_doc EOF "grep a" "wc -l" outfile
echo -e "${PURPLE}
----------------------------------------
${RESET}"