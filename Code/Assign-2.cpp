#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <unistd.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>

using namespace std;


//------------------helper function----------------------//

// trim from start (in place)
static inline void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))));
}



//----------------------------------Assumptions------------------------------------------------------------------------------//

// 1) Assuming each proccess has atleast one line to be printed for it.
// 2) The proccess files generated will have exactly the same name as given in the input file.
// 3) If an empty line is present in a proccess' column and after that line another line is present in that proccess' column, then
//	  the empty line will not be counted. (Provided the given scenario exists) e.g

//	  P1, P2
//    hello, world1
//		   , world2
//	  hello1,world3

//	  In this scenario, P1 has two lines because the empty line is ignored. It isn't counted.
//----------------------------------------------------------------------------------------------------------------------------//



int main()
{

	//-----------Getting the length of the quantum-----------//

	cout << "\n\nEnter the length of the quantum [1-1000]: ";

	int quantum = 0;

	cin >> quantum;

	//Check for invalid quantum size
	while (quantum < 1 || quantum > 1000)
	{
		cout << "\nInvalid Length. Enter a valid quantum length in [1-1000]: ";
		cin >> quantum;
	}

	cout << endl;


	//-----------Now calculating the total number of proccesses and the total lines possessed by each proccess-----------//

	ifstream fin("Assign-2.ip");

	if (fin.is_open())
	{
		string buffer = "";

		//Getting the first line which will help us calculate the total proccesses

		getline(fin, buffer);

		//A vector which will contain the names of the proccesses given in the input file
		vector <string> proccessNames;

		string temp = "";

		int totalProccesses = 0;

		for (int i = 0; buffer[i] != '\0'; i++)
		{
			if (buffer[i] == ',' || buffer[i + 1] == '\0')
			{
				if (buffer[i + 1] == '\0' && buffer[i] != ',')
					temp.push_back(buffer[i]);

				ltrim(temp);					//Removing the leading spaces and tabs
				proccessNames.push_back(temp);
				temp = "";

				totalProccesses++;
			}
			else
				temp.push_back(buffer[i]);
		}


		//Now storing the lines of each proccess in a 2D String Vector

		vector<vector<string> > arrLines;
		arrLines.resize (totalProccesses);

		while (!fin.eof())
		{
			getline(fin, buffer);

			//check in case an empty line comes in the file
			if (!buffer.empty())
			{
				string token = "";
				int currentP = 0;

				for (int i = 0; buffer[i] != '\0'; i++)
				{
					if (buffer[i] == ',' || buffer[i + 1] == '\0')
					{
						if (buffer[i + 1] == '\0')
							token.push_back(buffer[i]);

						//Removing the leading spaces and tabs
						ltrim(token);

						if (!token.empty())
						{
							arrLines[currentP].push_back(token);
						}

						currentP++;
						token = "";
					}
					else
						token.push_back(buffer[i]);
				}
			}
		}

		fin.close();

		//Placing a string containing only "\0" at the end of every proccess' lines
		for (int i = 0; i < totalProccesses; i++)
		{
			arrLines[i].push_back("\0");
		}


		//-----------------------------------------------------------------------------------------------------//
		//-----------------------------------------PROCCESSING-------------------------------------------------//
		//-----------------------------------------------------------------------------------------------------//


		//Array which will contain the IDs of the shared semaphores
		vector<int>	arrIDs;
		arrIDs.resize(totalProccesses+1);

		//Array which will contain the pointers to the shared semaphores
		sem_t** arrSem = new sem_t* [totalProccesses + 1];

		for (int i = 0; i < totalProccesses+1; i++)
		{
			arrSem[i] = NULL;
		}

		int memKey = 9279267;


		//A shared bool array whose corresponding indices tell if the process has become dead (finished printing its lines) or not
		int id_bArr = shmget(memKey++, 1024, 0666 | IPC_CREAT | IPC_EXCL);

		if (id_bArr == -1)
		{
			cout << "\nERROR creating a memory segment !\n";
			return 1;
		}

		bool* bArr = (bool*)shmat(id_bArr, NULL, 0);

		//Initializing the bool array (to be on the safe side)
		for (int i = 0; i < totalProccesses; i++)
		{
			bArr[i] = 0;
		}


		//Creating "Assign-2.op" here so that each proccess can have access to it after forking is done
		ofstream fassign("Assign-2.op");

		if (!fassign.is_open())
		{
			cout << "\nThe main output file Assign-2.op could not be created. So exiting.\n";
			return 1;
		}

		pid_t  pid1;

		sem_t* semaphoreC;
		sem_t* semaphoreP;


		int k = 0;

		for (k = 0; k < totalProccesses+1; k++)
		{
			arrIDs[k] = shmget(memKey, 1024, 0666 | IPC_CREAT | IPC_EXCL);

			if (arrIDs[k] == -1)
			{
				cout << "\nERROR creating a memory segment !\n";
				return 1;
			}

			memKey++;

			arrSem[k] = (sem_t*)shmat(arrIDs[k], NULL, 0);

			//Initializing with 0
			sem_init(arrSem[k], 1, 0);

			if (k!=0)
			{
				semaphoreC = arrSem[k];		//Just for the purpose that each child has its own semaphore.
				semaphoreP = arrSem[0];

				pid1 = fork();

				//Whenever a child is created, he goes out of the loop and the parent keeps on creating the other children
				if (pid1 == 0)
					break;
			}
		}



		//Code for Child (Proccess)
		if (pid1 == 0)
		{
			//When a child breaks the loop above, then the value of k helps to determine the child number
			semaphoreC = (sem_t*) shmat(arrIDs[k], NULL, 0);
			semaphoreP = (sem_t*) shmat(arrIDs[0], NULL, 0);

			sem_wait(semaphoreC);

			int currentProccess = k - 1;

			//Copying the File Name

			string fName = proccessNames[currentProccess];

			const char* fileName = fName.c_str();


			//Creating the output file of each proccess
			ofstream fout(fileName);

			if (!fout.is_open())
			{
				cout << "\nThe output file " << fileName << " could not be created. So exiting.\n";
				return 1;
			}

			int i = 0;

			int count = 0;

			while (arrLines [currentProccess][i] != "\0")
			{
				cout	<< arrLines [currentProccess][i] << endl; 		//On Console
				fout	<< arrLines [currentProccess][i] << endl; 		//In proccess' own file
				fassign << arrLines [currentProccess][i] << endl; 		//In main output file

				count++;

				//If count is a multiple of quantum
				if (count % quantum == 0)
				{
					fassign << "\n----------" << endl;	//In main output file
					cout 	<< "\n----------" << endl;	//On Console

					if (arrLines [currentProccess][i +1] != "\0")
					{
						sem_post(semaphoreP);
						sem_wait(semaphoreC);
					}
				}

				i++;
			}


			if (count % quantum != 0)
			{
				fassign << "\n----------" << endl;	//In main output file
				cout 	<< "\n----------" << endl;	//On Console
			}

			fout.close();

			bArr[currentProccess] = 1;		//Mark as dead

			sem_post(semaphoreP);

			shmdt(semaphoreP);
			shmdt(semaphoreC);
			shmdt(bArr);

			exit(EXIT_SUCCESS);
		}



		//Code for Parent which basically synchronizes all the processes in the order given in the input file
		else if (pid1 > 0)
		{
			bool stop = false;

			while (!stop)
			{
				for (int j = 0; j < totalProccesses; j++)
				{
					stop = true;

					if (bArr[j] == 0)
						stop = false;
				}

				for (int i = 1; i < totalProccesses+1 && !stop; i++)
				{
					//If the proccess is not dead
					if (bArr[i - 1] == 0)
					{
						sem_post(arrSem[i]);
						sem_wait(arrSem[0]);
					}
				}
			}

			fassign.close();
		}

		//Deleting the shared memory objects
		for (int i = 0; i < totalProccesses+1; i++)
		{
			sem_destroy(arrSem[i]);
			shmdt(arrSem[i]);
			shmctl(arrIDs[i], IPC_RMID, NULL);
		}

		delete[] arrSem;


		shmdt(bArr);
		shmctl(id_bArr, IPC_RMID, NULL);

		cout << "\nSuccessfully deleted the shared memories. Now Exiting.\n\n";
	}

	else
		cout << "\nAssign-2.ip could not be opened. Exiting.\n";

	return 0;
}


