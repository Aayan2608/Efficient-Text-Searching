#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
vector<long long> v1;
#define NO_OF_CHARS 256
int count_fa = 0;
int getNextState(string &pat, int M, int state, int x)
{
	if (state < M && x == pat[state])
		return state + 1;
	int ns, i;
	for (ns = state; ns > 0; ns--)
	{
		if (pat[ns - 1] == x)
		{
			for (i = 0; i < ns - 1; i++)
				if (pat[i] != pat[state - ns + 1 + i])
					break;
			if (i == ns - 1)
				return ns;
		}
	}
	return 0;
}

void computeTF(string &pat, int M, int TF[][NO_OF_CHARS])
{
	int state, x;
	for (state = 0; state <= M; ++state)
		for (x = 0; x < NO_OF_CHARS; ++x)
			TF[state][x] = getNextState(pat, M, state, x);
}

void search(string &pat, string &txt)
{
	int M = pat.length();
	int N = txt.length();

	int TF[M + 1][NO_OF_CHARS];

	computeTF(pat, M, TF);

	int i, state = 0;
	for (i = 0; i < N; i++)
	{
		state = TF[state][txt[i]];
		if (state == M)
		{
			long long it = lower_bound(v1.begin(), v1.end(), i - M + 1) - v1.begin();
			int c;
			if (it == 0)
			{
				c = i - M + 1;
			}
			else
			{
				c = i - M + 1 - v1[it - 1];
			}
			if (it == 0)
			{
				c++;
			}
			count_fa++;
			cout << "Found at line: " << it + 1 << " position: " << c << endl;
		}
	}
}

int main()
{
	ifstream newfile;

	newfile.open("sherlock.txt");

	string s1;
	if (newfile.is_open())
	{

		string tp;
		while (getline(newfile, tp))
		{
			s1 += tp;
			s1 += ' ';
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
	getline(cin, s2);
	search(s2, s1);
	cout << "Number of Occurences: " << count_fa;
	return 0;
}
