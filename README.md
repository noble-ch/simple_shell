<h1 align="center">
  0x16. C - Simple Shell
</h1>

<p align="center">
   📄 🚀
</p>

<p align="center">
  <strong>
   Description
  </strong>
</p>

<p align="center">
This project represents a milestone in the C code curriculum at ALX Africa Software Engineering, focusing on the implementation of a shell. </br>Referred to as the "Gates of Shell," this project is a part of the first trimester and serves as a valuable learning experience for students to delve into advanced concepts such as processes, system calls, bit manipulation, file management, and error handling. </br>The shell created in this project mimics the functionalities of a basic UNIX command interpreter (sh).</br> The entire program has been crafted using the C programming language.






</p>

## COPYRIGHT
Copyright (C) 2024 by [**Noble Biru**](https://github.com/noble-ch) and [**brian Wagura**](https://github.com/brian-wagura) </br>
All rights reserved

 ## Description :
This is a shell written in [C](https://en.wikipedia.org/wiki/C_(programming_language)).
It is based on [the Thompson Shell](https://en.wikipedia.org/wiki/Thompson_shell).

## Environment :

the shell was built and tested on  Ubuntu 14.04 LTS.

## Features
* Display a prompt and wait for the user to type a command. A command line always ends with a new line.
* If an executable cannot be found, print an error message and display the prompt again.
* Handle errors.
* Hndling the “end of file” condition (Ctrl+D)
* Hanling the command line with arguments
* Handle the PATH
* Support the exit features


## Builtins
Our shell has support for the following built-in commands:

| Command             | Definition                                                                                |
| ------------------- | ----------------------------------------------------------------------------------------- |
| exit                | Exit the shell                                                                            |
| env                 | Print the environment.                                                                    |
| setenv [var][value] | Set an environment variable and value. If the variable exists, the value will be updated. |
| alias[name[='value]]| Reads aliases name                                                                        |
| unsetenv [var]      | Remove an environment variable.                                                           |
| cd [dir]            | Change the directory.                                                                     |
| help [built-in]     | Read documentation for a built-in.                                                        |


 ## Installation : Getting HSH
 
Clone the below repository and compile the files into an executable using the GCC compiler.
```
https://github.com/noble-ch/simple_shell.git
```

### Basic usage :bulb:
- First, Fork this Repository [Learn how to fork repo](https://docs.github.com/en/github/getting-started-with-github/fork-a-repo).
- Then Clone [Learn how to clone ](https://docs.github.com/en/github/creating-cloning-and-archiving-repositories/cloning-a-repository).
- Create an executable by running the following command:
- `gcc -Wall -Werror -Wextra -pedantic *.c -o hsh`
- From there, type in the following command and press your enter button.
- `./hsh`
- Final step: ENJOY!


## Example :computer:
```
ls -la
```
![114757753-e50c2180-9d64-11eb-95ea-fb9bba776c8c](https://user-images.githubusercontent.com/57016982/186711943-65abad4d-eedf-4d65-947d-3710e189bdee.png)

## Contributors :
* [**noble biru**](https://github.com/noble-ch)
* [**brian biru**](https://github.com/brian-wagura)

## Acknowledgments :
- The creators of the C language.
- Our software engineer-in-residence.
- Betty Holberton | Alx-Africa .