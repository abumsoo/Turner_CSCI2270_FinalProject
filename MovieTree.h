#ifndef MOVIETREE_H
#define MOVIETREE_H
#include <iostream>
#include <string>
#include <vector>
// creates the MovieNode element which stores each individual movie and its corresponding information.
struct MovieNode{
    int ranking;
    std::string title;
    int year;
    int quantity;
    MovieNode *parent;
    MovieNode *left;
    MovieNode *right;

    MovieNode(){};

    MovieNode(int in_ranking, std::string in_title, int in_year, int in_quantity)
    {
        ranking = in_ranking;
        title = in_title;
        year = in_year;
        quantity = in_quantity;
    }

};
//creates the hash table
struct HashElem{
	std::string name;
	HashElem *next;
    HashElem *previous;

	HashElem(){};
	HashElem(std::string in_name, std::string in_movie)
	{
		name = in_name;
		next = NULL;
		previous = NULL;
	}

};
class MovieTree
{
    public:
        MovieTree();
        ~MovieTree();
        void printMovieInventory();
        void addMovieNode(int ranking, std::string title, int releaseYear, int quantity);
        void addRenter (std::string name, std::string movie);
        int hashSum(std::string x, int s);
        std::string findMovie(std::string title);
        int rentMovie(std::string title);
        int countMovieNodes();
        void deleteMovieNode(std::string title);
        int stockMovies();
        void addReturnedMovie(std::string title);
        void removeRenter (std::string name);
        void printRenters();
        void initial();

    protected:
    private:
        void printMovieInventory(MovieNode * node);
        MovieNode* search(std::string title);
        MovieNode *root;
        void DeleteAll(MovieNode * node);
        MovieNode* treeMinimum(MovieNode *node);
        void countMovieNodes(MovieNode *node, int *c);
        void stockMovies(MovieNode * node, int *cost);
        int tableSize = 10;
		HashElem* hashTable[10];

};

#endif // MOVIETREE_H
