#include "Trie.h"
#include <fstream> //ifstream
namespace TrieADT
{
	Trie::Trie(std::string dictionary_file)
		:m_DictionaryFile(dictionary_file),m_Root(), m_DictionaryWordCount(0)
	{		
		m_Root = std::make_shared<TrieADT::TrieNode>();
		m_Root->isWord = false;

		if (!load())
		{
			std::cout << "TrieADT::Trie::Trie could not load dictionary. " << std::endl;
			exit(1);
		}
	}

	Trie::~Trie()
	{		
	}

	bool Trie::load(void)
	{		
		m_Root->isWord = false;
		for (int i = 0; i < TRIE_MAX_CHARACTERS; i++) // i think this step is redundant
		{
			m_Root->children[i] = NULL;
		}

		// open the file 
		std::ifstream inFile; // input stream for file reading 
		inFile.open(m_DictionaryFile);
		if ( ! inFile.is_open())
		{
			std::cout << "TrieADT::Trie::load can't find dictionary " << m_DictionaryFile << std::endl;
			return false;
		}
		
		/*
			Read a word from the file, add it to the TRIE data structure 
		*/
		std::string line; 
		m_DictionaryWordCount = 0;
		while (std::getline(inFile, line))					
			AddToDictionary(line);			
		
		inFile.close();
		std::cout << "TrieADT::Trie::load completed loading dictionary." << std::endl;		
		return true;
	}

	/*
		Trie::AddToDictionary(new_word)
		adds a new word into the dictionary by iterating through the Trie and adding new children as it gets to the end.
	*/
	void Trie::AddToDictionary(const std::string& new_word)
	{		
		std::shared_ptr<TrieADT::TrieNode> child = m_Root;
		int idx; // store the character's numerical value 
		for (int i = 0; i < new_word.size(); i++)
		{
			idx = (int)new_word[i] - (int)('a');
			
			if (child->children[idx] == NULL) // the character does not exist so create it . 
			{
				child->children[idx] = std::make_shared<TrieADT::TrieNode>();
				child->children[idx]->isWord = false;
			}
			child = child->children[idx]; // set the new child node;
		}
		child->isWord = true; // at the end, so we can make it a word.

		m_DictionaryWordCount += 1;
	}
	
	/*
		check if a given word is in the Trie
		use first char->childre[second char] .... is not null 
	*/
	bool Trie::check(std::string& word)
	{
		std::shared_ptr<TrieADT::TrieNode> child = m_Root; // current node that is being checked 
		int idx; 
		for (char& c : word) 
		{
			idx = (int)std::tolower((c))-(int)('a'); // get ascii code of character 

			child = child->children[idx]; // get next node

			if ( child == NULL)
				return false;			
		}		
		return child->isWord;
	}
}