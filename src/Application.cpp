#include <iostream>
#include "Trie.h"

#include <fstream>
#include <string>
#include <vector>
#include <list>

/*
	Example of Trie Data structure and usage 
	GeekforGeeks: https://www.geeksforgeeks.org/trie-insert-and-search/
	Michael Grieco : https://www.youtube.com/watch?v=XEXxN5Kumgk
	Vaidehi Joshi : https://medium.com/basecs/trying-to-understand-tries-3ec6bede0014


	what is a Trie : 
		A search tree ADT that is used to search for pattern in text (eg. word spelling, sentence stucture) specific for strings

*/

int main(int argc, char* argv[])
{
	// process the input command line arguments 
	const char* filename = (argc == 2) ? argv[1] : "res/data/test.txt";
	std::cout << "file to be checked: " << filename << std::endl;

	// create Trie and load dictionary 
	TrieADT::Trie Dictionary("res/data/dictionary.txt");	

		
	// open the text file 
	std::ifstream inFile;
	
	inFile.open(filename);
	if (!inFile.is_open())
	{
		std::cout << "application:: could not load file " << filename << std::endl;
		return 1;
	}
	else
	{		
		int idx = 0, misspellings = 0, wordcount = 0;

		std::string line;
		std::list<std::string> badWords;	
		
		while (std::getline(inFile, line))
		{
			// line contains multiple worlds 		
			// grab word for a word and test, we check a word when we find a space else we contactinate it all. 
			// this can be imrpoved 
			std::string nword;
			for (char& c : line)
			{	
 				if (c == ' ')
 				{
 					if (nword.size() > 1)
 						if (Dictionary.check(nword))
 							wordcount += 1;
 						else				
 						{
 							misspellings += 1;
 							badWords.push_back(nword);
 						}
 					nword.clear();
 				}
 				if (isalpha(c))				
 					nword.push_back(c);
			}			
		}

		std::cout << "Printing misspellings: " << std::endl;
		for (std::string& s : badWords)
		{
			std::cout << s << ", ";
		}
		std::cout << "\n\n\n"
				  << "Total incorrect spellings: " << misspellings << std::endl 
				  << "Total words checked : " << wordcount << std::endl
		          << "Total words in Dictionary: " << Dictionary.size() << std::endl;
	}
	inFile.close();
	return 0;
}