#include <iostream>
#include <fstream>
#include <cstring>
#include "MovieTree.h"
using namespace std;
MovieTree::MovieTree(){
	root = NULL;
}
MovieTree::~MovieTree(){
	DeleteAll(root);
}
void MovieTree::DeleteAll(MovieNode *node){
	if (node->left!=NULL){
		DeleteAll(node->left);
	}
	if (node->right!=NULL){
		DeleteAll(node->right);
	}
	cout<<"Deleting: "<<node->title<<endl; 
	delete node;
}
void MovieTree::printMovieInventory(){
	printMovieInventory(root);
}
void MovieTree::printMovieInventory(MovieNode * node){
	if (node->left!=NULL){
		printMovieInventory(node->left);
	}
	cout<<"Movie: "<< node->title<<" "<<node->quantity<<endl;
	if (node->right!=NULL){
		printMovieInventory(node->right);
	}
}
int MovieTree::countMovieNodes(){
	int *c;
	int c2=0;
	c=&c2;
	countMovieNodes(root, c);
	return *c;
} 
void MovieTree::countMovieNodes(MovieNode *node, int *c){
	if (node->left!=NULL){
		countMovieNodes(node->left, c);
	}
	*c=*c+1;
	if (node->right!=NULL){
		countMovieNodes(node->right,c);
	}
}
void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity){
	MovieNode *node=new MovieNode;
	MovieNode *temp=root;
	MovieNode *parent=NULL;
	node->parent=NULL;
	node->left=NULL;
	node->right=NULL;
	node->ranking=ranking;
	node->title=title;
	node->year=releaseYear;
	node->quantity=quantity;
	if (root==NULL){
		root=node;
	}
		while (temp!=NULL){
			parent=temp;
			if (node->title.compare(temp->title)<0){
				temp=temp->left;
			}
			else{
				temp=temp->right;
			}
		}
		if (parent==NULL){
            root=node;
		}
		else if (node->title.compare(parent->title)<0){
			parent->left=node;
			node->parent=parent;
		}
		else {
			parent->right=node;
			node->parent=parent;
		}
}
string MovieTree::findMovie(std::string title){
	MovieNode *node=root;
	while (node!=NULL){			//root is NULL in an empty tree, left and right child NULL at bottom of tree
		if (node->title.compare(title)>0){
			node=node->left;
		}
		else if (node->title.compare(title)<0) {
			node=node->right;
		}
		else {
			cout << "Movie Info:" << endl;         
			cout << "===========" << endl;         
			cout << "Ranking:" << node->ranking << endl;       
			cout << "Title:" << node->title << endl;         
			cout << "Year:" << node->year << endl;         
			cout << "Quantity:" << node->quantity << endl; 
			return title;
		}
	}
	cout<<"Movie not found."<<endl;
	return title;
}
void MovieTree::deleteMovieNode(string title){
	MovieNode *node = root;
	bool found=false;
	while (node!=NULL){
		if (node->title.compare(title)>0){
			node=node->left;
		}
		else if (node->title.compare(title)<0) {
			node=node->right;
		}
		else {
			found=true;
			if (node->right==NULL && node->left==NULL){
				if (node->parent->left==node){		//true when node is left child
					node->parent->left=NULL;
				}
				else{
					node->parent->right=NULL;
				}
				delete node;
				break;
			}
			else if (node->right==NULL && node->left!=NULL){
				MovieNode *temp=node->left;
				if (node->parent->left==node){
					node->parent->left=temp;
					temp->parent=node->parent;
					delete node;
				}
				else{
					node->parent->right=temp;
					temp->parent=node->parent;
					delete node;
				}
			}
			else if (node->right!=NULL && node->left==NULL){
				MovieNode *temp=node->right;
				if (node->parent->left==node){
					node->parent->left=temp;
					temp->parent=node->parent;
					delete node;
				}
				else{
					node->parent->right=temp;
					temp->parent=node->parent;
					delete node;
				}
			}
			else if (node->right!=NULL && node->left!=NULL){
				MovieNode *min=treeMinimum(node->right);
				if (min==node->right){
					node->parent->left=min;
					node->left->parent=min;
					min->parent=node->parent;
					min->left=node->left;
					delete node;
				}
				else{
					min->parent->left=min->right;
					min->parent=node->parent;
					min->right->parent=min->parent;
					node->parent->left=min;
					min->left=node->left;
					min->right=node->right;
					node->right->parent=min;
					node->left->parent=min;
					delete node;
				}
			}
		}
	}
	if (found==false){
		cout<<"Movie not found"<<endl;
	}
}
MovieNode* MovieTree::treeMinimum(MovieNode *node){
	while (node->left!=NULL){
		node=node->left;
	}
	return node;
}
int MovieTree::rentMovie(string title){
	MovieNode *node=root;
	int a=0;
	while (node!=NULL){		
		if (node->title.compare(title)>0){
			node=node->left;
		}
		else if (node->title.compare(title)<0) {
			node=node->right;
		}
		else {
			if (node->quantity!=0){
				node->quantity=(node->quantity)-1;
				cout<<"Movie has been rented."<<endl;
				cout << "Movie Info:" << endl;         
				cout << "===========" << endl;         
				cout << "Ranking:" << node->ranking << endl;       
				cout << "Title:" << node->title << endl;         
				cout << "Year:" << node->year << endl;         
				cout << "Quantity:" << node->quantity << endl; 
			}
			a=1;
			break;
		}
	}
	if (a==0){
		cout<<"Movie not found."<<endl;	
		return -1;
	}
	return node->quantity;
}
int MovieTree::stockMovies(){
	int *cost;
	int cost2=0;
	cost= &cost2;
	stockMovies(root, cost);
	cout<<"The total cost of replacing the movies is: $"<<*cost<<endl;
	cost2=*cost;
	cost=0;
	return cost2;
}
void MovieTree::removeRenter(string name){
	int index=hashSum(name, tableSize);
	bool done =false;
	if (hashTable[index]!=NULL){
		HashElem *temp = hashTable[index];
		if (temp->previous==NULL &&temp->next==NULL && temp->name==name){
			delete temp;
			hashTable[index]=NULL;
		}
		else if (temp->name==name){
			hashTable[index]=temp->next;
			delete temp;
		}
		else{
			temp=temp->next;
			while (temp->next!=NULL){
				if (temp->name==name){
					temp->previous->next=temp->next;
					temp->next->previous=temp->previous;
					delete temp;
					done = true;
					break;
				}
				temp=temp->next;
			}
			if (done==false){
				if (temp->name==name){
					temp->previous->next=NULL;
					delete temp;
				}
			}
		}
	}
}
void MovieTree::addReturnedMovie(string title){
	MovieNode *node=root;
	while (node!=NULL){		
		if (node->title.compare(title)>0){
			node=node->left;
		}
		else if (node->title.compare(title)<0) {
			node=node->right;
		}
		else {
			node->quantity=(node->quantity)+1;
			cout<<"Movie has been returned."<<endl;
			cout << "Movie Info:" << endl;         
			cout << "===========" << endl;         
			cout << "Ranking:" << node->ranking << endl;       
			cout << "Title:" << node->title << endl;         
			cout << "Year:" << node->year << endl;         
			cout << "Quantity:" << node->quantity << endl; 
			break;
		}
	}

}
void MovieTree::initial(){
	for (int x=0; x<tableSize; x++){
		hashTable[x]=NULL;
	}
}
void MovieTree::addRenter(string name, string movie){
	HashElem* node = new HashElem;
	node->name = name;
	int index=hashSum(name, tableSize);
	if (hashTable[index]==NULL){
		node->previous=NULL;
		node->next=NULL;
		hashTable[index]=node;
	}
	else{
		HashElem *temp = hashTable[index];
		while(temp->next!=NULL){
			temp = temp->next;
		}
		node->next=NULL;
		temp->next=node;
		node->previous = temp;
	}
}
int MovieTree::hashSum(string x, int s){
	int sum = 0;
	for (unsigned int z=0; z<x.length(); z++){
		sum = sum + x[z];
	}
	sum = sum % s;
	return sum;
}
void MovieTree::stockMovies(MovieNode *node, int *cost){
	if (node->left!=NULL){
		stockMovies(node->left, cost);
	}
	if (node->right!=NULL){
		stockMovies(node->right, cost);
	}
	if (node->quantity<10){
		cout<<node->title<<" quantity increased by "<< 10-node->quantity<<endl;
		*cost=*cost+(5*(10-node->quantity));
		node->quantity=10;
	}
}
void MovieTree::printRenters(){
	HashElem *temp;
	bool done = false;
	for (int i=0; i<tableSize; i++){
		if (hashTable[i]!=NULL){
			temp = hashTable[i];
			while (temp->next!=NULL){
				cout<<temp->name<<endl; 
				temp=temp->next;
			}
			cout<<temp->name<<endl; 
			done=true;
		}
	}
	if (done==false){
		cout<<"empty"<<endl;
	}
}
