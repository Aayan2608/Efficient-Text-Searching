#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#define MAX_CHAR 256
using namespace std;

vector<long long> v1;
int count_trie = 0;

// Class representing a node in the suffix trie
class SuffixTrieNode
{
private:
	SuffixTrieNode *children[MAX_CHAR];
	list<int> *indexes; // List to store indexes of occurrences of the suffix

public:
	SuffixTrieNode()
	{
		indexes = new list<int>;
		for (int i = 0; i < MAX_CHAR; i++)
			children[i] = NULL;
	}

	// Function to insert a suffix into the trie
	void insertSuffix(string suffix, int index);

	// Function to search for a pattern in the trie
	list<int> *search(string pat);
};

// Class representing a suffix trie
class SuffixTrie
{
private:
	SuffixTrieNode root;

public:
	// Constructor to build the suffix trie from the given text
	SuffixTrie(string &txt)
	{
		// Insert all suffixes into the trie starting from each character of the text
		for (int i = 0; i < txt.length(); i++)
			root.insertSuffix(txt.substr(i), i);
	}

	// Function to search for a pattern in the suffix trie
	void search(string pat);
};

// Function to insert a suffix into the trie
void SuffixTrieNode::insertSuffix(string s, int index)
{
	indexes->push_back(index);

	// If the suffix is not empty, continue inserting the rest of the suffix
	if (s.length() > 0)
	{
		char cIndex = s.at(0);
		if (children[cIndex] == NULL)
			children[cIndex] = new SuffixTrieNode();
		children[cIndex]->insertSuffix(s.substr(1), index + 1);
	}
}

// Function to search for a pattern in the trie
list<int> *SuffixTrieNode::search(string s)
{
	// If the pattern is empty, return the list of indexes
	if (s.length() == 0)
		return indexes;

	// If the pattern is not empty and the current character has a corresponding child node,
	// continue searching the rest of the pattern in the child node
	if (children[s.at(0)] != NULL)
		return (children[s.at(0)])->search(s.substr(1));
	else
		return NULL;
}

// Function to search for a pattern in the suffix trie
void SuffixTrie::search(string pat)
{
	// Search for the pattern in the trie starting from the root
	list<int> *result = root.search(pat);

	// If the pattern is found, display the line number and position of occurrences
	if (result != NULL)
	{
		list<int>::iterator i;
		int patLen = pat.length();
		for (i = result->begin(); i != result->end(); ++i)
		{
			// Calculate the line number and position of the occurrence
			long long it = lower_bound(v1.begin(), v1.end(), *i - patLen) - v1.begin();
			int c;
			if (it == 0)
			{
				c = *i - patLen;
			}
			else
			{
				c = *i - patLen - v1[it - 1];
			}
			if (it == 0)
			{
				c++;
			}
			
			// Increment the count of pattern occurrences and display the result
			count_trie++;
			cout << "Found at line: " << it + 1 << " and position " << c << endl;
		}
	}
}

int main()
{
	// Open the input text file "sherlock2.txt"
	ifstream newfile;
	newfile.open("sherlock2.txt");
	string s1;
	if (newfile.is_open())
	{
		string tp;
		while (getline(newfile, tp))
		{
			s1 += tp;
			s1 += ' ';

			// Store the positions of line breaks in the vector v1
			if (v1.size() == 0)
			{
				v1.push_back(tp.size());
			}
			else
			{
				v1.push_back(v1.back() + tp.size() + 1);
			}
		}
		newfile.close();
	}

	// Create a suffix trie for the input text
	SuffixTrie S(s1);

	// Get user input for the pattern to search
	string s2;
	cout << "Enter pattern to search: ";
	getline(cin, s2);

	// Search for the pattern in the suffix trie and display the results
	S.search(s2);

	// Output the total number of occurrences of the pattern
	
	cout << "Number of occurrences: " << count_trie;

	return 0;
}
