#include <iostream>
#include <string>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

//signal handlers

void alarm_handler(int signal);
void signal_handler(int signal);

// variable declarations

unsigned second = 5;
bool interrupt = false;
string message = "Annoying~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";

int main(int argc, char* argv[])
{
	//for loop that parses the input strings and set the switches
	for( unsigned i = 1; i < argc; i++){
		if (string(argv[i]) == "-i"){
			interrupt = false;
		} else if(string(argv[i]) == "+i"){
			interrupt = true;
		} else if(string(argv[i]) == "+t"){
			if(i+1 >= argc){
				cout << "Error! Invalid time input!\nExiting the Program." << endl;
				exit(0);
			}
			second = atoi(argv[i+1]);
			if(second == 0){
				cout << "Error! Invalid time input!\nExiting the Program." << endl;
				exit (0);
			}
			i++;
		} else if(string(argv[i]) == "-m"){
			if(i+1 == argc){
				cout << "Error! Invalid input!\n Exiting the Program." << endl;
				exit(0);
			}
			message = argv[i+1];
			i++;
		} else {
			cout << "Error! You have typed wrong command. Exiting the program." << endl;
			exit (0);
		}
	}
	 // Install a signal handler for alarm.
	if (signal(SIGALRM, alarm_handler) == SIG_ERR)
  	 {
	      	 cout << "Error while setting up a signal handler.\n" << endl;
      		 exit(0);
  	 }
	// Install a signal handler for ctrl-c when interrupt is set to true.
	if(interrupt){
		if (signal(SIGINT, signal_handler) == SIG_ERR)
		{
			cout << "Error while setting up a signal handler.\n" << endl;
			exit(0);
		}
	}

	//call alarm signal
	alarm(second);

	// while loop that pauses the program until a signal is encountered
	while(true){
		pause();
	}	

	cout << "Exiting the program" << endl;
	return 0;
}

/* alarm_handler handles the alarm signal that is created by alarm() system call.
 * param: int signal, is the integer value that identifies which signal it is. It is not used
 * result: it prints an annoying message and resets the alarm.
 */
void alarm_handler(int signal)
{
	cout << message << endl;
	alarm(second);
}
/* signal_handler handles the SIGINT signal produced by ctrl-c
 * param: int signal, is the integer value that identifies which signal it is. It is not used
 * result: it prints annoying messages.
 */
void signal_handler(int signal)
{
	cout << "\nYou can't ctrl-C out~~!" << endl;
	cout << message << endl;
}


