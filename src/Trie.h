#pragma once
#include <string>
#include <iostream>
#include <memory>

namespace TrieADT
{
	#define TRIE_MAX_CHARACTERS 26 // maximum characters we will be dealing with ( a - z )

	struct TrieNode {
		bool isWord = false; // this node terminates as a complete word, or a sub of words 
		std::shared_ptr<TrieADT::TrieNode> children[TRIE_MAX_CHARACTERS];
	};

	class Trie
	{
	public:
		Trie(std::string dictionary_file);
		~Trie();

		bool load(void);		
		bool check(const std::string& word);		
		void AddToDictionary(const std::string& new_word);

		unsigned int size(void) const { return m_DictionaryWordCount; };
		
	private:
		std::string m_DictionaryFile;		
		std::shared_ptr<TrieADT::TrieNode> m_Root;
				
		int m_DictionaryWordCount;
	};
}