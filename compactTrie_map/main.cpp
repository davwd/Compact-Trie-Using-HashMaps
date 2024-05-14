
//  Compact Trie with HashMap version 2.
// class template based on TrieV4.

//  Created by David Holguin in May 2024.

/**
 Version #2 notes:
 - Most of the code is imported from compactTire V4
 - program is working from the most part
 - insert function could possibly be optimized.
	It seems slightly repetitive at the moment.
 - Using ordered map so that children can be accessed
	in an alphabetical ordered manner while doing traversals.
 
 */


#include <iostream>
#include <map>
#include "CompactTrie_Map.h"
using namespace std;


int main() {
	HashyCompactTrie t;
	t.insert("barato");
	t.insert("burasca");
	t.insert("beso");
	t.insert("bebesita");
	t.print();
	cout<<endl;
	t.preorder();
	cout<<"# of nodes = "<<t.nodeCount<<endl;
	cout<<"# of words = "<<t.wordCount<<endl;

	string prefix;
	cout<<"Type a prefix to match for -> ";
	cin>>prefix;
	t.maximalPrefixSearch(prefix);
	return 0;
}
