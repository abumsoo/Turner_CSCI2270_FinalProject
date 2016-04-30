# Turner_CSCI2270_FinalProject
## Project Summary
The purpose of this project is to expand upon assignments 6 and 7 by introducing new features and utilizing different data structures.
The increased funcionality includes a new money systeme that is used for movie rentals, the ablility to restock the available movies, the ability to
return movies, and a hash function was included in the program that allows the renters information to be stored.
The program works by reading in a list of movies and information about them and storing them in a binary search tree. From, there a number of different
things can be done in terms of altering and changing the stored data.

## How to Run
To run the program you must first download the FinalProject.cpp, MovieTree.cpp, MovieTree.h, and Movie.txt files.
Open the files with code in geany and compile the MovieTree.cpp file
```
g++ -std=c++11 MovieTree.cpp
```
Once this has been compiled you want to run that program and compile the
FinalProject.cpp file with the line
```
g++ -std=c++11 FinalProject.cpp MovieTree.o
```
Then run the program with the included text file with the line
```
./a.out Movie.txt
```
This should run the program and you will see a menu displayed in the terminal. Input 1 will prompt you for a user name, and if a
movie title that is in the text file is entered will return information about this movie including its ranking, title, year, and number available. 
Input 2 allows you to rent a movie. You will be prompted for you name and the title of the movie you will notice that this will increase the stores 
money by five dollars. Input 3 prints the entire movie inventory. Input 4allows you to delete a movie from the binary search tree. You will be 
prompted for a movie title and the corresponding film will be removed. Input 5 counts the total number of movies in the tree and will display the 
number. Input 6 restocks the movies, making sure that there are at least ten copies of each movies. The number of each movie that was added is 
displayed as well as the total cost and how much money the store has remaining. Input 7 returns a movie that has been rented, you will once again
be prompted for your name and the movie you rented and if the name is in the hash table the movie will be returned and the name will be removed.
Input 8 prints the names of all of the people who are currently renting a movie. Input 9 quits the program and deletes all of the movies from the
binary search tree.

## Dependencies
Only the FinalProject.cpp, MovieTree.cpp, MovieTree.h, and Movie.txt files are required to run this program.

## System Requirements
My program is written for Linux using geany.

## Contributors
No partners.

## Open issues/bugs
None that are known.