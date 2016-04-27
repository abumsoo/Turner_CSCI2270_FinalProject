#include "MovieTree.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;
int main(int argc, char* argv[]){
	// Initializes variables and reads in the information from the file.
	ifstream inFile;
	inFile.open(argv[1]);	
	string data;
	string word="";
	MovieTree mt;
	int count=0;
	string holder="";
	string one;
	string two;
	string three;
	string four;
	int a;
	int b;
	int c;
	int storeFunds=5000;
	while (getline(inFile, word)){
		for (unsigned int i=0; i<word.length(); i++){
		if (word[i]==','){
			if (count==0){
				one=holder;
				holder="";
				count=1;
			}
			else if (count==1){
				two=holder;
				holder="";
				count=2;
			}
			else if (count==2){
				three=holder;
				holder="";
				count=3;
			}
		}
		else{
			holder=holder+word[i];
		}
	}
		four=holder;
		a=stoi(one);
		b=stoi(three);
		c=stoi(four);
		mt.addMovieNode(a, two, b, c);
		holder="";
		count=0;
	}
	int input;
	bool done=false;
	mt.initial();
	//loops through the main menu until the user is finished.
	while (done==false){
		cout << "======Main Menu======" << endl;     
		cout << "1. Find a movie" << endl;     
		cout << "2. Rent a movie" << endl;     
		cout << "3. Print the inventory" <<endl;   
		cout << "4. Delete a movie" << endl;
		cout << "5. Count the movies" << endl; 
		cout << "6. Restock movies" <<endl;
		cout << "7. Return a movie" <<endl;
		cout << "8. Print renter list" << endl;
		cout << "9. Quit" << endl;
		cin>>input;
		//Finds movie
		if (input==1){
			cout<<"Enter title:"<<endl;
			string title;
			string hold;
			getline(cin, hold);
			getline(cin, title);
			mt.findMovie(title);
		}
		//rent movie
		else if (input==2){
			string title;
			string name;
			string hold;
			getline(cin,hold);
			cout << "Enter your name:" << endl;
			getline(cin,name);
			cout << "Enter your movie title:" << endl; 
			getline(cin, title);
			int k=mt.rentMovie(title);
			mt.addRenter(name, title);
			storeFunds= storeFunds +5;
			cout<<"Current Store Funds: "<<storeFunds<<endl;
			if (k==0){
				mt.deleteMovieNode(title);
			}
		}
		//prints inventory
		else if (input==3){
			int j;
			mt.printMovieInventory();
		}
		//deletes a movie
		else if (input==4){
			cout<<"Enter title:"<<endl;
			string title;
			string hold;
			getline(cin, hold);
			getline(cin, title);
			mt.deleteMovieNode(title);
		}
		// counts the number of unique movies
		else if (input==5){
			cout<<"Tree contains: "<<mt.countMovieNodes()<<" movies." << endl; 
		}
		//restocks the movies
		else if (input==6){
			storeFunds = storeFunds - mt.stockMovies();
			cout<< "$"<<storeFunds<< " in store funds remaining."<<endl;
		}
		//returns a movie
		else if (input==7){
			string title;
			string name;
			string hold;
			getline(cin,hold);
			cout << "Enter your name:" << endl;
			getline(cin,name);
			cout << "Enter your movie title:" << endl; 
			getline(cin, title);
			mt.addReturnedMovie(title);
			mt.removeRenter(name);
		}
		//prints the list of current renters
		else if (input == 8){
			mt.printRenters();
		}
		//exits the program
		else if (input==9){
			cout<<"Goodbye!"<<endl;
			done=true;
		}
		else{
			cout<< "Not a valid input. Try again."<<endl;
		}
	}
	return 0;
}
