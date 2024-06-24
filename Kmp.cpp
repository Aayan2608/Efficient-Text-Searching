#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// Vector to store positions of line breaks in the input text file
vector<long long> v1;

// Variable to count the occurrences of the pattern using KMP algorithm
int count_kmp = 0;

// Function to compute the Longest Prefix Suffix (LPS) array for the pattern
void computeLPSArray(string pat, int M, int *lps)
{
	// 'len' keeps track of the length of the previous longest prefix suffix
	int len = 0;

	// The longest prefix suffix for the first character is always 0
	lps[0] = 0;

	// 'i' starts from 1 and iterates through the pattern to compute LPS values
	int i = 1;
	while (i < M)
	{
		if (pat[i] == pat[len])
		{
			len++;
			lps[i] = len;
			i++;
		}
		else
		{
			if (len != 0)
			{
				// If there is a mismatch, update 'len' to the value at previous index in lps
				len = lps[len - 1];
			}
			else
			{
				// If 'len' is 0 and there is a mismatch, set lps[i] to 0 and move to the next character
				lps[i] = 0;
				i++;
			}
		}
	}
}

// Function to perform pattern search using KMP algorithm
void KMPSearch(string &pat, string &txt)
{
	int M = pat.length(); // Length of the pattern
	int N = txt.length(); // Length of the text

	int lps[M]; // LPS array for the pattern

	// Compute the LPS array for the given pattern
	computeLPSArray(pat, M, lps);

	int i = 0; // Index for text[]
	int j = 0; // Index for pat[]

	// Loop through the text and pattern until a match is found
	while ((N - i) >= (M - j))
	{
		if (pat[j] == txt[i])
		{
			// If characters match, move both pointers forward
			j++;
			i++;
		}

		if (j == M)
		{
			// If the pattern is completely matched, calculate the line and position
			long long it = lower_bound(v1.begin(), v1.end(), i - j) - v1.begin();

			int c;
			if (it == 0)
			{
				c = i - j;
			}
			else
			{
				c = i - j - v1[it - 1];
			}
			if (it == 0)
			{
				c++;
			}
			
			count_kmp++; // Increment the count of pattern occurrences
			cout << "Found at line: " << it + 1 << " position: " << c << endl;

			// Update 'j' using LPS array for the next possible match
			j = lps[j - 1];
		}
		else if (i < N && pat[j] != txt[i])
		{
			// If characters do not match and 'j' is not at the beginning, update 'j' using LPS array
			if (j != 0)
				j = lps[j - 1];
			else
				i = i + 1; // Move 'i' to the next position in text
		}
	}
}

int main()
{
	// Open the input text file "sherlock.txt"
	ifstream newfile;
	newfile.open("sherlock.txt");
	string s1;

	// Read the content of the file line by line and store it in s1
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

	string s2;
	cout << "Enter pattern to search: ";
	getline(cin, s2); // Get user input for the pattern to search

	// Perform pattern search using KMP algorithm
	KMPSearch(s2, s1);

	// Output the total number of occurrences of the pattern
	cout << "Number of Occurrences: " << count_kmp << endl;
}
