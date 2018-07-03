# Forking-Semaphores-Shared-Memory
An example demonstrating the concepts of process forking, use of semaphores and shared memory by solving an interesting problem.

## Problem Statement

You are given an input file named *Assign-2.ip*. The file has n number of columns. Each column represents a separate process (not a thread). The input file is a comma separated file forming a table like following. Note that the ... here represent that there can be any number of such columns here. What you have to do is, read the input file, determine how many columns are there in the file, and then fork that many processes. 

You have to write the code in a way using semaphores, that each process runs in order mentioned in the input file.  Each process will print as many lines in its respective column as the size of quantum.

![table 1](../master/images/i.png)

When user will start you program it will ask the user to enter the length of the quantum as following

```[pc@user ~ ]$ Enter the length of the quantum [1-1000]:```

When a user enters any value between 1 to 1000. Suppose user enters 990. It means that 990 elements in the first column will be printed on the screen and saved in the file named P-1.op. Then 990 elements from the second column will be printed on screen and saved in P-2.op
, so on and so forth. Until the nth process will print its 990 elements and saves them in P-<n>.op. Then the control goes back to the first process, and prints next 990 elements in first column. The process continues until the EOF is reached.This also means that as output there will be as many files created as the number of columns in the file. Each containing the output of each column separately. In addition
there will be another output file named *Assign-2.op* which will contain the stdout of the program. It will save the output of the program as it happened.
  
## How to Run

Download the Code folder and using Ubuntu Bash or Windows or Linux Terminal, change current working directory to the Code folder.
Then on the terminal, type

```
make
```

Then type this command:

```
./Assign-2.out
```


## Contact
You can get in touch with me on my LinkedIn Profile: [Haris Muneer](https://www.linkedin.com/in/harismuneer/)

## Issues
If you face any issue, you can create a new issue in the Issues Tab and I will be glad to help you out.

## License
[MIT](../master/LICENSE)
Copyright (c) 2018-present, harismuneer
