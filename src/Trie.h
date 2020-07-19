#pragma once
#include <string>
#include <iostream>

namespace TrieADT
{
	#define TRIE_MAX_CHARACTERS 26 // maximum characters we will be dealing with ( a - z )
	#define TRIE_LONGEST_WORD 45

	struct TrieNode {
		bool isWord = false; // this node terminates as a complete word, or a sub of words 
		TrieADT::TrieNode* children[TRIE_MAX_CHARACTERS];
	};

	class Trie
	{
	public:
		Trie(std::string dictionary_file);
		~Trie();

		bool load(void);		
		bool check(std::string& const word);
		void unload(void);
		void AddToDictionary(const std::string& new_word);

		unsigned int size(void) const { return m_DictionaryWordCount; };
		
	private:
		std::string m_DictionaryFile;
		TrieADT::TrieNode* m_Root = NULL;
		bool m_DictionaryLoaded;
		int m_DictionaryWordCount;

		void unloadNode(TrieADT::TrieNode* top);

	};
}