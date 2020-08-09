											Assignment -2
											 README FILE




LIST OF FILES SUBMITTED :
* musicalchairs.cpp - Main code for the assignment, which implements a multithreaded approach to the classical musical chairs problem.
* Report.pdf - Report for the above program, which explains the steps involved in implementing the above program and provides an analysis of the observed results.
* README.txt (current file).

COMPILING THE CODE :
The code can be compiled by running the command :
g++ -std=c++11 -pthread musicalchairs.cpp

RUNNING THE CODE :
The code can be run with the command :
./a.out --np <n> < <Input file>
 Where the number of players is entered in place of  ‘<n>’ and ‘<Input file >’ contains user input from stdin.
For example ./a.out --np 4 < input_nosleep.txt will run the program with 4 players and input will be taken from the ‘input_nosleep.txt’  file.


  

SAMPLE TEST CASES :
1. Neither Umpire nor players sleep  :

nishant@nishant-Inspiron-5370:~/OS_Assignments$ cat input_nosleep.txt
lap_start
music_start
music_stop
lap_stop
lap_start
music_start
music_stop
lap_stop
lap_start
music_start
music_stop
lap_stop
nishant@nishant-Inspiron-5370:~/OS_Assignments$ g++ -std=c++11 -pthread musicalchairs.cpp
nishant@nishant-Inspiron-5370:~/OS_Assignments$ ./a.out --np 4 < input_nosleep.txt
Musical Chairs: 4 player game with 3 laps.
======= lap# 1 =======
2 could not get chair
**********************
======= lap# 2 =======
3 could not get chair
**********************
======= lap# 3 =======
1 could not get chair
**********************
Winner is 0
Time taken for the game: 873 us



2. The umpire sleeps but the players remain awake :

nishant@nishant-Inspiron-5370:~/OS_Assignments$ cat input_umpsleep.txt
lap_start
music_start
umpire_sleep 200
music_stop
lap_stop
lap_start
music_start
umpire_sleep 200000
music_stop
lap_stop
lap_start
music_start
umpire_sleep 800000
music_stop
lap_stop
nishant@nishant-Inspiron-5370:~/OS_Assignments$ g++ -std=c++11 -pthread musicalchairs.cpp
nishant@nishant-Inspiron-5370:~/OS_Assignments$ ./a.out --np 4 < input_umpsleep.txt
Musical Chairs: 4 player game with 3 laps.
======= lap# 1 =======
3 could not get chair
**********************
======= lap# 2 =======
1 could not get chair
**********************
======= lap# 3 =======
0 could not get chair
**********************
Winner is 2
Time taken for the game: 1001099 us
  


3. Both the players and the umpire sleep :

nishant@nishant-Inspiron-5370:~/OS_Assignments$ cat input_sleep.txt 
lap_start
player_sleep 0 1000
player_sleep 1 2000
player_sleep 2 3000
player_sleep 3 4000
music_start
umpire_sleep 200
music_stop
lap_stop
lap_start
player_sleep 0 1000
player_sleep 1 2000
player_sleep 2 3000
music_start
umpire_sleep 200000
music_stop
lap_stop
lap_start
player_sleep 0 1000
player_sleep 1 2000
music_start
umpire_sleep 800000
music_stop
lap_stop
nishant@nishant-Inspiron-5370:~/OS_Assignments$ ./a.out --np 4 < input_sleep.txt
Musical Chairs: 4 player game with 3 laps.
======= lap# 1 =======
3 could not get chair
**********************
======= lap# 2 =======
2 could not get chair
**********************
======= lap# 3 =======
1 could not get chair
**********************
Winner is 0
Time taken for the game: 1005251 us

