# 🔐 Forking-Semaphores-Shared-Memory

[![Open Source Love svg1](https://badges.frapsoft.com/os/v1/open-source.svg?v=103)](#)
[![GitHub Forks](https://img.shields.io/github/forks/harismuneer/Forking-SharedMemory-Semaphores_Example.svg?style=social&label=Fork&maxAge=2592000)](https://www.github.com/harismuneer/Forking-SharedMemory-Semaphores_Example/fork)
[![GitHub Issues](https://img.shields.io/github/issues/harismuneer/Forking-SharedMemory-Semaphores_Example.svg?style=flat&label=Issues&maxAge=2592000)](https://www.github.com/harismuneer/Forking-SharedMemory-Semaphores_Example/issues)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat&label=Contributions&colorA=red&colorB=black	)](#)


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

------------------------------

## Author
You can get in touch with me on my LinkedIn Profile: [![LinkedIn Link](https://img.shields.io/badge/Connect-harismuneer-blue.svg?logo=linkedin&longCache=true&style=social&label=Connect
)](https://www.linkedin.com/in/harismuneer)

You can also follow my GitHub Profile to stay updated about my latest projects: [![GitHub Follow](https://img.shields.io/badge/Connect-harismuneer-blue.svg?logo=Github&longCache=true&style=social&label=Follow)](https://github.com/harismuneer)

If you liked the repo then kindly support it by giving it a star ⭐!

## Contributions Welcome
[![forthebadge](https://forthebadge.com/images/badges/built-with-love.svg)](#)

If you find any bug in the code or have any improvements in mind then feel free to generate a pull request.

## Issues
[![GitHub Issues](https://img.shields.io/github/issues/harismuneer/Forking-SharedMemory-Semaphores_Example.svg?style=flat&label=Issues&maxAge=2592000)](https://www.github.com/harismuneer/Forking-SharedMemory-Semaphores_Example/issues)

If you face any issue, you can create a new issue in the Issues Tab and I will be glad to help you out.

## License
[![MIT](https://img.shields.io/cocoapods/l/AFNetworking.svg?style=style&label=License&maxAge=2592000)](../master/LICENSE)

Copyright (c) 2018-present, harismuneer                                                        
