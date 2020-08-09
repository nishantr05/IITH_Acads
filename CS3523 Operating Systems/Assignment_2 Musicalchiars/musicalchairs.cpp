/*
 * Program: Musical chairs game with n players and m intervals.
 * Author:  Nishant and Sumadhva
 * Roll# : ES18BTECH11013, ES18BTECH11018
 */

#include <stdlib.h>  /* for exit, atoi */
#include <iostream>  /* for fprintf */
#include<thread>     /* for using threads */
#include<mutex>		 /* for using locks */
#include<condition_variable> /* for using condition varibles, a synchronization primitive */
#include <string>     
#include <errno.h>   /* for error code eg. E2BIG */
#include <getopt.h>  /* for getopt */
#include <assert.h>  /* for assert */
#include <chrono>	/* for timers */

using namespace std ;

// Initializing the required variables :

int* Pl_sleep ;
int player_count, chairs_filled, lapcount ;
mutex m_chair, m1, s_lock;
condition_variable cond_music ;
condition_variable chairs ;
bool music = true, umpire_awake, start; 

/*
 * Show usage of the program
 */


void umpire_main(int nplayers)
{
	int sleep_time, pl_id ;
	string s ;
	lapcount = 1 ;    //To keep track of the current lap.

	// Loop through each command, in every lap
	while (lapcount < nplayers)
	{
		
		cin >> s ;
		if (s == "lap_start") 
		{
			cout << "======= lap# " << lapcount << " =======" << endl ;
			chairs_filled = 0 ;
		}
		else if (s == "player_sleep")
		{
			cin >> pl_id >> sleep_time ;
			// Upadate the 'Pl_sleep' array with the player sleep times in a synchronized fashion
			s_lock.lock() ;
			Pl_sleep[pl_id] = sleep_time ;
			s_lock.unlock() ;
		}
		else if (s == "music_start") 
		{
			music = true ;
			start = true ;
		}
		else if (s == "umpire_sleep")
		{
			cin >> sleep_time ;
			this_thread::sleep_for(chrono::microseconds(sleep_time));
		}
		else if (s == "music_stop")
		{
			//When the music stops, the player threads start sitting on the chairs.
			//During this time the umpire thread wiats on the condition variable 'cond_music', till its notified by the last thread.
			unique_lock <mutex> ulock_ump(m1) ;     
			music = false ;
			cond_music.wait(ulock_ump) ;
		}
		else if (s == "lap_stop")
		{
			lapcount ++ ;
			music = true ;
			start = false ;
			player_count-- ;
			cout << "**********************" << endl ;
			chairs.notify_all();
		}
	}

	return ;
}

void player_main(int plid)
{
	int sleeptime ;

	while (1)
	{
		s_lock.lock() ;
		sleeptime = Pl_sleep[plid] ;
		s_lock.unlock() ;

		//To make the thread sleep once the music starts
		if (sleeptime && start)
		{
			this_thread::sleep_for(chrono::microseconds(Pl_sleep[plid]));
			Pl_sleep[plid] = 0 ;
		}
		//Once the music stops the player threads start grabbing a chair to sit on
		if(music == false)
		{
			unique_lock<mutex> ulock_pl(m_chair);
			// Atomically increment 'chairs_filled'
			chairs_filled ++;

            if (chairs_filled == player_count)  // The count of 'chairs_filled' has exceeded the number of available chairs, and we eliminate one player.
            {
            	ulock_pl.unlock();
            	cout << plid << " could not get chair" << endl ;
            	cond_music.notify_one() ;      // Notify the umpire to resume it's duties.
            	break ;
            }
            else
		    	chairs.wait(ulock_pl);         //While there are still empty chairs, we make the player thread wait on 'ulock_pl'.
 
		}
		else if (player_count == 1)           // The last remaining player after all the laps is declared as the winner
		{
			cout << "Winner is " << plid << endl ; 
			break ;
		}
	}

	return ;
}

unsigned long long musical_chairs(int nplayers)
{
	auto t1 = chrono::steady_clock::now();

	// Spawn umpire thread.
    thread umpire(umpire_main, nplayers) ;

	// Spawn n player threads.
	thread players[nplayers] ;
	for (int i = 0; i < nplayers; ++i)
	    players[i] = thread(player_main, i) ;
   
	umpire.join() ;
	
	for (int i = 0; i < nplayers; ++i)
	    players[i].join();

	auto t2 = chrono::steady_clock::now();

	auto d1 = chrono::duration_cast<chrono::microseconds>(t2 - t1);

	return d1.count();
}

void usage(int argc, char *argv[])
{
    cerr << "Usage:" << endl;
    cerr << argv[0] << "--nplayers <n>" << endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int c;
	int nplayers = 0;

    /* Loop through each option (and its's arguments) and populate variables */
    while (1) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
            {"help",            no_argument,        0, 'h'},
            {"nplayers",         required_argument,    0, '1'},
            {0,        0,            0,  0 }
        };

        c = getopt_long(argc, argv, "h1:", long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
        case 0:
            cerr << "option " << long_options[option_index].name;
            if (optarg)
                cerr << " with arg " << optarg << endl;
            break;

        case '1':
            nplayers = atoi(optarg);
            break;

        case 'h':
        case '?':
            usage(argc, argv);

        default:
            cerr << "?? getopt returned character code 0%o ??n" << c << endl;
            usage(argc, argv);
        }
    }

    if (optind != argc) {
        cerr << "Unexpected arguments.\n";
        usage(argc, argv);
    }


	if (nplayers == 0) {
		cerr << "Invalid nplayers argument." << endl;
		return EXIT_FAILURE;
	}
	player_count = nplayers ;
	Pl_sleep = new int[nplayers]; 
	cout << "Musical Chairs: " << nplayers << " player game with " << nplayers-1 << " laps." << endl ;

    unsigned long long game_time;
	game_time = musical_chairs(nplayers);

    cout << "Time taken for the game: " << game_time << " us" << endl;

    exit(EXIT_SUCCESS);
}



