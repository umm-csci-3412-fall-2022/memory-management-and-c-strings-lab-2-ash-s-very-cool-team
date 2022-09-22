gcc -Wall -g -o main main.c palindrome.c
g++ -Wall -g -o run_test palindrome.c palindrome_test.cpp -lgtest -pthread -std=c++0x

