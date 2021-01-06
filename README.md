# Password-Cracker
From Spring 2020
How to compile and run: 
	$ g++ -O0 -o PasswordCrackerV3pThreadwithCommandLineInput   PasswordCrackerV3pThreadwithCommandLineInput.cpp
        $ ./PasswordCrackerV3pThreadwithCommandLineInput passwordtocheck
	// Bash Commands to get and run test sample:
	// N = number of lines you want to randomly sellect from alleged-gmail-passwords.txt
	$ shuf -n N alleged-gmail-passwords.txt > passwordSample.txt
	//run the program for every line in passwordSample.txt
	$  while read in; do ./PasswordCrackerV3pThreadwithCommandLineInput “$in”; done < passwordSample.txt.
