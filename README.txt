the program is fairly simple in functionality, 
enter a string and get the vowels and non vowels in 2
seperate strings or enter 2 strings (1 of vowels and 1 of non-vowels)
and combine them into 1 string.

how to run:
option1 on csx3: 
1. login into the csx3 linux machine at uofc using ssh.
2. upload both the client.cpp and server.cpp files to the machine.
3. compile the programs in seperate commandline terminals
using the g++ command and give the 
excutables different names using the -o command.
4. run the server first and then the client.
5. enter the input 1 to envowel a string(combine 2 strings)
or 2 to devowel a string.
6. choose the version of encoding you would like to do or undo.
the basic version has 2 strings; 1 with all vowels being 
replaced with spaces and the other with all nonvowels being 
replaced with spaces.
the advanced version has 2 strings as well; 1 with all vowels completely removed
the other with only vowels and the number of characters before them
(i.e. e means their is 1 character before e).
the super advanced version is discussed later on in the bonus section.
7. enter the inputs as requested by the program.
8. after the inputs are entered and you have recieved your desired strings,
the program will ask you to if you would like to envowel or devowel again.
9. repeat the steps above if you would like to enter more strings. 
If you wish to exit press ctrl+c on windows or control+c on mac 
to terminate the client program, do the same with the server. 

option2:
1. enter the code of client.cpp and change the 
IPadresses found on lines 88 and 119 to the IP address 
of where you store the server file. 
follow steps 3-9 of option1.

the bonus:
after selecting the option for envowleling and devoweling. 
their is an option for basic advanced and super advanced.
the super advanced is my awnser to the bonus.
1)it takes in the string to be devoweled.
2)2 strings are made, all vowels are stored in the 2nd string with no spacing.
3)all characters from the input are stored in the first string.
4)all characters in the first string move down 26 places
in the ascci chart except the vowels. 
5)all vowels are replaced with the '~' character as that is the higest
character in the ascci chart (meaning that it can't be 
mistakened for something else when all other characters are 
moved down 25 places).
6) if any character is in the range of (32,58) these characters moved up to the range of (100,126)
ensuring that they won't be moved down to anything less then the ' '(empty space) 
character

testing and what works:
testing was done on the linux machines using ssh.
all basic funcitionalities that were asked for(basic and advanced split/merge)
should work but no exit to the program was designed and you have to use command 
c to stop the program. 