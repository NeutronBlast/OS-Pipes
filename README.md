## Concurrent Programming

<!-- TABLE OF CONTENTS -->
## Table of Contents

* [Project Goals](#project-goals)
* [About the Project](#about-the-project)
  * [Built With](#built-with)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
* [Usage](#usage)
* [Implementation Details](#implementation-details)
* [Considerations](#considerations)

<!-- ABOUT THE PROJECT -->
## Project Goals
1. Use the primitives *fork*, *wait*, *exec*, *exit* for concurrent process management
2. Use pipes as communication mechanism between processes
3. Use primitives to measure the execution time between processes/threads
4. Use primitives to manage either binary or text files

## About the project
Cryptography is a set of strategies that allows us to transform the information with the goal of hiding it from non authorized third parties. The most used algorithms rely on substitution techniques to modify the original text and obtain the cyphered text. A very old and popular algorithm is *caesar's code*, that uses only one substitution and it's the following:

Every letter of the original text is translated for the letter that is 2 positions ahead in the alphabet, the letters that are in the end of the alphabet (Y, Z) are replaced by (A, B) respectively. For example

*I will only tell you tomorrow morning in the library*

Would end up as:

*K yknn qpna vgnn apw vqoqttqy oqtokpi kp vjg nkdtcta*

Another very well known algorithm is "Murcielago code", its substitution is the following:

M | U | R | C | I | E | L | A | G | O

M = 0

U = 1

R = 2

C = 3

I = 4

E = 5

L = 6

A = 7

G = 8

O = 9

This repository has a program written in C of the crypting/decrypting program, there's a version of 2 children processes and n children processes, the root will apply one crypting/decrypting method and each children will apply the other, the blank spaces will be deleted.

The decyphering program is exactly the opposite, given the cyphered text in a text file, it will obtain the clear text without blank spaces or tabs. That means that the children processes will execute the reverser Murcielago code. The output files will be received by the superior level and will apply the caesar code in reverse.

### Built With

* [C]()


<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps.

### Prerequisites

This is an example of how to list things you need to use the software and how to install them.
* [Ubuntu](https://ubuntu.com/download/desktop)

* gcc

```sh
sudo apt update
sudo apt install build-essential
sudo apt-get install manpages-dev
```

To make sure gcc was installed execute

```sh
gcc --version
```

### Usage
```sh
cript_p <-c/-d> NumberOfChildren InputFileName OutputFileName
```

## Implementation details

Initially, the root process will distribute the work between their *n* children in equal parts as long as it is possible. In any case, each children process will get a piece of text assigned to cypher/decypher.

## Considerations
1. It will be assumed that the input file is correct: Only contains letters (numbers won't be considered). 
2. The compilation of the program will be done with the help of a Makefile
3. The system calls will be validated with perror()
4. The input arguments will be verified (number of children must be a positive integer, etc) 