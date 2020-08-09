/*
 * Copyright (C) 1998-2020 Maruthi Seshidhar Inukonda - All Rights Reserved.
 * maruthi.inukonda@gmail.com
 *
 * This file is released under the LGPL v2.
 *
 * This file may be redistributed under the terms of the Lesser GNU Public
 * License.
 */

/*
 *
 * Authors : Sumadhva Sridhar and S.Nishant Reddy
 * Roll no : ES18BTECH11018, ES18BTECH11013
 *
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <cstring>

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <getopt.h>

#include <mydev.h>

#define MAP_LEN 1048576	  //defining the length of our mmap segment as 1MB

using namespace std;

void print_help(const char *, int);

typedef enum operation { OP_NONE, OP_MAPREAD, OP_MAPWRITE } operation_t;
#define OP_MAX 10
operation_t op[OP_MAX];
int op_cnt = 0;

char *dev_file = NULL;
int dev_fd = -1;
char *dev_mem = NULL;
int dev_oflag = 0;

char *msg = NULL;
int msg_len = 0;
int msg_buf_len = 0;

int main(int argc, char *argv[])
{
	int c;
	bool read_flag = false, write_flag = false;
	int mmap_flags = 0;
	int ret = 0;

	while (1) {
		int this_option_optind = optind ? optind : 1;
		int option_index = 0;
		static struct option long_options[] = {
			{"help", 1, 0, 'h'},
			{"ptype", 1, 0, 'p'},
			{"message", 1, 0, 'm'},
			{"operation", 1, 0, 'o'},
			{0, 0, 0, 0}
		};

		c = getopt_long(argc, argv,"hp:m:o:" , long_options, &option_index);
		if (c == -1)        //end of the command, getopt semantics
			break;

		switch (c) {
			case 'h':
				print_help(argv[0], -1);
				break;  

			case 'm':
				if (!optarg) {
					print_help(argv[0], -1);
				}
				if (msg) {
					cerr << "Duplicate message options\n";
					print_help(argv[0], -1);
				}

				msg = optarg;
				msg_len = strlen(optarg);
				break;

			case 'p':
				if (!optarg) {
					print_help(argv[0], -1);
				}

				if (strcmp("demand", optarg) == 0) {
				  	mmap_flags = MAP_SHARED;
				} else if (strcmp("prefetch", optarg) == 0) {
					mmap_flags = MAP_SHARED | MAP_POPULATE ;	//MAP_POPULATE flag included to implement prefetching
				} else {
					cerr << "Invalid operation: " << optarg << "\n";
					print_help(argv[0], -1);
				}
				break;

			case 'o':
				if (!optarg) {
					print_help(argv[0], -1);
				}
				if (op_cnt == OP_MAX) {
					cerr << "Too many operations\n";
					print_help(argv[0], -1);
				}

				if (strcmp("mapread", optarg) == 0) {
					op[op_cnt] = OP_MAPREAD;
					op_cnt++;
					read_flag = true;
				} else if (strcmp("mapwrite", optarg) == 0) {
					op[op_cnt] = OP_MAPWRITE;
					op_cnt++;
					write_flag = true;
				} else {
					cerr << "Invalid operation: " << optarg << "\n";
					print_help(argv[0], -1);
				}
				break;

			case ':':
				cerr <<  "Argument missing for option " << long_options[option_index].name << "\n";
				print_help(argv[0], -1);
				break;

			case '?':
				cerr << "Error, No such option\n";
				print_help(argv[0], -1);
				break;

			default:
				cerr <<  "?? getopt returned character code " << c << "\n";
		}
	}

	if (optind > argc - 1) {
		cerr << "Need devicemem argument\n";
		print_help(argv[0], -1);
	} else if (optind < argc - 1) {
		cerr <<  "Too many arguments\n";
		print_help(argv[0], -1);
	}
	dev_file = argv[optind];

	// --message is not required with read alone
	// --message is must along with write
	if (write_flag) {
		if (msg_len == 0 || msg == NULL) {
			cerr << "Need message argument along with read/write\n";
			print_help(argv[0], -1);
		}
	}

	// Figure out appropriate oflag from --op
	if (write_flag) {
		dev_oflag = O_RDWR;
	} else if (read_flag) {
		dev_oflag = O_RDONLY;
	} else { // just read or no operation
		dev_oflag = O_RDONLY;
	}

	dev_fd = open(dev_file, dev_oflag, 0700);
	if (dev_fd < 0) {
		perror("mydev_open failed");
		exit(-2);
	}

	for (int i=0; i < op_cnt; i++) {
		switch (op[i]) {

			case OP_MAPREAD: {
				char dummy_read;
				off_t off = 0;
				size_t len = MAP_LEN;
				// memory map the devicemem's kernel buffer into user-space segment.
				dev_mem = (char *) mmap(NULL, len, PROT_READ, mmap_flags, dev_fd, off);
				//check if the call to mmap failed:
				if (dev_mem == MAP_FAILED) { 
					perror("mmap has failed");
					return -1;
				}
				// Comparing the data read from devicemem with msg
				//If msg len is zero, we simply access the mapped memory, and do no comparisons
				if (msg_len == 0 || msg == NULL){
					for (int i = 0; i < len; i++){

						dummy_read = dev_mem[i]; 	//Reading the memory (no comparing)
					}
					break ;
				}
				for (int i = 0; i < len; i++){
					if (dev_mem[i] != msg[i % msg_len]) {
						//Error msg printed if the read content doesn't match msg, and we exit.
						perror("File content read does not match 'msg'");
						return -1;
					}
				}
				
				// unmap the devicemem's kernel buffer.
				munmap(dev_mem, len);
				break;
			}

			case OP_MAPWRITE: {
				off_t off = 0;
				size_t len = MAP_LEN;
				// memory map the devicemem's kernel buffer into user-space segment.
				dev_mem = (char *) mmap(NULL, len, PROT_WRITE, mmap_flags, dev_fd, off);
				//check if the call to mmap failed:
				if (dev_mem == MAP_FAILED) { 
					perror("mmap has failed");
					return -1;
				}
				// Write the message to ENTIRE devicemem from msg.
				for (int i = 0; i < len; i++){
					dev_mem[i] = msg[i % msg_len];
				}
				// unmap the devicemem's kernel buffer.
				munmap(dev_mem, len);
				break;
			}
		} // end switch
	} // end for(ops)
	
	close(dev_fd);

	return ret;
}

void print_help(const char *name, int exit_value)
{
	cerr << "Usage: " << name << " [options] <devname>\n";
	cerr << "Options:\n";
	cerr << "--operation <optype> : Where optype can be mapread, mapwrite\n";
	cerr << "--message <message>  : Message to be written/read-compare to/from the device memory\n";
	cerr << "--paging <ptype>     : Where ptype can be prefetch or demand\n";
	cerr << "--help               : Show this help\n";

	exit(exit_value);
}

