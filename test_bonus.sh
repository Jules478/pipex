GREEN='\e[1;32m'
PURPLE='\e[1;35m'
RED='\e[1;31m'
RESET='\033[0m'

make fclean
make bonus
make clean
clear
echo -e "test\ntest\ntest\ntest\ngood\ngood\ngood\n\ntest\n" > julestestinfile
touch julestestoutfile

echo -e "${PURPLE}
Valid Input

${RESET}"
valgrind --leak-check=full --track-fds=yes ./pipex julestestinfile "grep e" "wc -l" julestestoutfile
echo 5 > julestestfile
if diff julestestoutfile julestestfile > /dev/null; then
    echo -e "${GREEN}\nOutput Correct\n${RESET}"
else
    echo -e "${RED}\nOutput Incorrect\n${RESET}"
fi
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Outfile Doesn't Exist

${RESET}"
valgrind --leak-check=full --track-fds=yes ./pipex julestestinfile "grep e" "wc -l" julestestoutfile2
echo 5 > julestestfile
if diff julestestoutfile julestestfile > /dev/null; then
    echo -e "${GREEN}\nOutput Correct\n${RESET}"
else
    echo -e "${RED}\nOutput Incorrect\n${RESET}"
fi
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e  "${PURPLE}
Infile Doesn't Exist

${RESET}"
valgrind --leak-check=full --track-fds=yes ./pipex julestestinfile2 "grep e" "wc -l" julestestoutfile
echo 0 > julestestfile
if diff julestestoutfile julestestfile > /dev/null; then
    echo -e "${GREEN}\nOutput Correct\n${RESET}"
else
    echo -e "${RED}\nOutput Incorrect\n${RESET}"
fi
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Command 1 Doesn't Exist

${RESET}"
valgrind --leak-check=full --track-fds=yes ./pipex julestestinfile "a" "wc -l" julestestoutfile
echo 0 > julestestfile
if diff julestestoutfile julestestfile > /dev/null; then
    echo -e "${GREEN}\nOutput Correct\n${RESET}"
else
    echo -e "${RED}\nOutput Incorrect\n${RESET}"
fi
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Command 2 Doesn't Exist

${RESET}"
valgrind --leak-check=full --track-fds=yes ./pipex julestestinfile "grep e" "a" julestestoutfile
echo -n > julestestfile
if diff julestestoutfile julestestfile > /dev/null; then
    echo -e "${GREEN}\nOutput Correct\n${RESET}"
else
    echo -e "${RED}\nOutput Incorrect\n${RESET}"
fi
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Neither Command Exists

${RESET}"
valgrind --leak-check=full --track-fds=yes ./pipex julestestinfile "a" "a" julestestoutfile
echo -n > julestestfile
if diff julestestoutfile julestestfile > /dev/null; then
    echo -e "${GREEN}\nOutput Correct\n${RESET}"
else
    echo -e "${RED}\nOutput Incorrect\n${RESET}"
fi
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Multiple Commands

${RESET}"
valgrind --leak-check=full --track-fds=yes ./pipex julestestinfile "grep e" "wc -l" "wc -w" julestestoutfile
echo 1 > julestestfile
if diff julestestoutfile julestestfile > /dev/null; then
    echo -e "${GREEN}\nOutput Correct\n${RESET}"
else
    echo -e "${RED}\nOutput Incorrect\n${RESET}"
fi
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Infile Permissions Removed

${RESET}"
chmod 111 julestestinfile
valgrind --leak-check=full --track-fds=yes ./pipex julestestinfile "grep e" "wc -l" julestestoutfile
chmod 777 julestestinfile
echo 0 > julestestfile
if diff julestestoutfile julestestfile > /dev/null; then
    echo -e "${GREEN}\nOutput Correct\n${RESET}"
else
    echo -e "${RED}\nOutput Incorrect\n${RESET}"
fi
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Outfile Permissions Removed

${RESET}"
echo -n > julestestoutfile
echo -n > julestestfile
chmod 111 julestestoutfile
valgrind --leak-check=full --track-fds=yes ./pipex julestestinfile "grep e" "wc -l" julestestoutfile
chmod 777 julestestoutfile
if diff julestestoutfile julestestfile > /dev/null; then
    echo -e "${GREEN}\nOutput Correct\n${RESET}"
else
    echo -e "${RED}\nOutput Incorrect\n${RESET}"
fi
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Relative Path
 ! Change path of <cmd1> for valid test !
${RESET}"
valgrind --leak-check=full --track-fds=yes ./pipex julestestinfile "../push_swap/./push_swap '5 3 2 1 4'" "wc -l" julestestoutfile
if [ ! -s julestestoutfile ]; then
    echo -e "${RED}\nOutput Incorrect\n${RESET}"
else
    echo -e "${GREEN}\nOutput Correct\n${RESET}"
fi
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Absolute Path
 ! Change path of <cmd1> for valid test !
${RESET}"
valgrind --leak-check=full --track-fds=yes ./pipex julestestinfile "/home/mpierce/Desktop/MainWork/push_swap/./push_swap 5 3 2 1 4" "wc -l" julestestoutfile
if [ ! -s julestestoutfile ]; then
    echo -e "${RED}\nOutput Incorrect\n${RESET}"
else
    echo -e "${GREEN}\nOutput Correct\n${RESET}"

fi
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Insufficient Commands

${RESET}"
valgrind --leak-check=full --track-fds=yes ./pipex julestestinfile "wc -l" julestestoutfile
echo -n > julestestoutfile
echo -n > julestestfile
if diff julestestoutfile julestestfile > /dev/null; then
    echo -e "${GREEN}\nOutput Correct\n${RESET}"
else
    echo -e "${RED}\nOutput Incorrect\n${RESET}"
fi
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Sleep Test
${RESET}"
echo -n > julestestoutfile
echo -n > julestestfile
while true; do
    echo -ne "${PURPLE}$(date +"%T")\r${RESET}"
    sleep 1
done &
valgrind --leak-check=full --track-fds=yes ./pipex julestestinfile "sleep 10" "sleep 10" "sleep 10" "sleep 10" "sleep 10" "sleep 10" "sleep 10" "sleep 10" "sleep 10" julestestoutfile
kill $!
if diff julestestoutfile julestestfile > /dev/null; then
    echo -e "${GREEN}\nOutput Correct\n${RESET}"
else
    echo -e "${RED}\nOutput Incorrect\n${RESET}"
fi
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
here_doc

For expected output pass this input: a b c d e f EOF
${RESET}"
valgrind --leak-check=full --track-fds=yes ./pipex here_doc EOF "grep e" "wc -l" julestestoutfile
echo 1 > julestestfile
if diff julestestoutfile julestestfile > /dev/null; then
    echo -e "${GREEN}\nOutput Correct\n${RESET}"
else
    echo -e "${RED}\nOutput Incorrect\n${RESET}"
fi
echo -e "${PURPLE}
----------------------------------------
${RESET}"

rm -rf julestestinfile julestestoutfile julestestoutfile2 julestestfile