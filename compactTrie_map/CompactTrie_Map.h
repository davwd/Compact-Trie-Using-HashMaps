//
//  CompactTrie.h
//  This is a definition of the base class of Compact Trie with Hash Map

//  Created by David Holguin on 5/8/24.
//

#include <iostream>
using namespace std;


#ifndef CompactTrie_Map_h
#define CompactTrie_Map_h

struct Node {
	string label;
	Node* parent;
	map<char, Node*> children; //using ordered map to have ordered children.
	bool isWord = 0;
	
	Node(string s) {
		label = s;
		isWord = false;
	}
};

//none of the members of this base class have thrown errors during tests.
class HashyCompactTrie {
	
	Node* root = nullptr;
	
	Node* insert (Node* node, string s) {
		
		if (node==nullptr)
		{
			node = new Node(s);
			node->isWord = true;
			return node;
		}
		
		string tag=node->label;
		char c = s[0];
	
		int i=0;
		while (s[i]==tag[i] && s[i]!='\0')
			i++;
		
		if (i==0 && node==root && !tag.empty()) //first char mismatch happened at the non-empty root
		{
			Node* tmp = new Node("");
			tmp->children[tag[i]] = node;
			tmp->children[c] = insert(nullptr, s);
			node->parent = tmp;
			tmp->children[c]->parent = tmp;
			return tmp; //the input node was the root so we must return the new root.
		}
		
		s = s.substr(i,s.size()-i);    // cut the prefix of input s that has already been matched
		c = s[0];
		
		if (s.empty())  //we already matched everything, no need for insertion
		{
			node->isWord=true;
			return node;
		}
		
		else if (tag[i] == '\0') //we have a suffix left to store, current node is done.
		{
			if (node->children.find(c) == node->children.end())
			{
				node->children[c] = insert(nullptr, s); //insert new child
				node->children[c]->parent = node;
			}
			else
				node->children[c] = insert(node->children[c], s);  //keep traversing down
			return node;
		}
		
		else
		{
			//we have a suffix left to store, but current node is not done.
			//we must split the current node --> create bubble with prefix and rewire
			Node* newParent = new Node(tag.substr(0,i));
			if (node->parent)
				node->parent->children[node->label[0]] = newParent; //substituting newParent into map were node was
			node->label = tag.substr(i,tag.size()-i);
			//insert both node and remaining s as children of NewParent:
			newParent->children[node->label[0]] = node;
			node->parent = newParent;
			newParent->children[c] = insert(nullptr, s);
			newParent->children[c]->parent = newParent;
			return newParent;
		}

	}
	
	
	/**
	 @discussion List of possible cases while reading a node:
	 Case 1: node.label is empty or was fully compared, move to child.
	 Case 2: prefix done or mismatch happened within node.
	 
	 @param node  non-null pointer to a node in the Trie
	 @param prefix input prefix to max match for
	 @param wordSoFar  concatenation of the characters found in search path.
	 @param p  pointer to a char in prefix
	 @return node with max match to input string
	 
	 @note Null pointers will only be handled by findChild() function and by main callee function.
	 @version #4.  current version is highly simplified from past version
	 */
	
	Node* PrefixSearch(Node* node, string prefix, string &wordSoFar, int &p) {
		
		string label = node->label;
		
		//loop within node label until mismatch
		int l = 0;
		while (prefix[p]==label[l] && prefix[p]!='\0')
		{ p++; l++; }
		
		if(label[l] == '\0' && prefix[p]!='\0')  //case 1: node.label done, move to child
		{
			wordSoFar += label;
			if (node->children.find(prefix[p])==node->children.end())
				return node;  //no children matching next character. So current node is max match
			else
				return PrefixSearch(node->children[prefix[p]], prefix, wordSoFar, p);
		}
		
		else //case 2:  prefix done or mismatch happened within node.
		{
			wordSoFar += label;
			return node;
		}
	}
	
	
	
	
	//simple inorder traversal
	void preorder(Node* node) {
		if (node==nullptr)
			return;
		nodeCount++;
		if (node->isWord)
			wordCount++;
		for (const auto &[_,n] : node->children)
			preorder(n);
	}
	
	
	///will print anything to the right and below the input node.
	///@discussion printing method : variation of preorder traversal
	///@param s string to which to append visited node labels.
	void print(Node* node, string s) {
		if (node==nullptr)
			return;
		if (node->isWord)
			cout<<s+node->label<<" ";
		for (auto n : node->children)
			print(n.second, s+node->label);
			
	}
	
public:
	int nodeCount=0;
	int wordCount=0;
	
	///public function to call from main
	void insert(string s) { root = insert(root, s); }
	void print() { print(root, ""); }
	void preorder() { preorder(root);  }
	
	
	
	///public function to call from main
	///prints stored words with max match to input string
	void maximalPrefixSearch (string & prefix) {
		if (root==nullptr)
			return;
		string wordSoFar;
		int p=0;
		Node* n = PrefixSearch(root, prefix, wordSoFar, p);
		if (n)
		{
			cout<<endl<<"The node with max match with prefix '"<<prefix<<"' is: ";
			if (n==root)
				cout<<"The root node."<<endl;
			else
				cout<<n->label<<endl;
			
			cout<<endl<<"List of words that maximally match the query prefix:"<<endl;
			if (n->isWord)
				cout<<wordSoFar<<" ";
			for (auto p : n->children)
				print(p.second, wordSoFar);
		}
		cout<<endl<<endl<<endl;
	}
	
	
};

#endif
