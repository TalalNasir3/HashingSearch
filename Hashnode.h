//HashNode.h

#ifndef HASHNODE_H
#define HASHNODE_H

#include "Posting.h"


using namespace P;  // posting namespace 


namespace H{


	
class HashNode{
		

  public:
			
    string word; // value(used for hashing)
	PostingList *LIST; // list for multiple instances of same word
	HashNode* next; // next in the bucket list (collisions, separate chaining)
	
	friend class HashMap;
	
  
	
	// constructors
	
	
	HashNode();	
	HashNode(const string &key, const int &docID, const int &pos);
	
	// getters & setters
	
	
	string getKey() const;
	PostingNode* getListHead();
	PostingList* getList();
	
	
	void setPosting(const string& word, const int &docID, const int &pos);
	void deleteList();
    string getWord();
    HashNode* getNext();
    HashNode* getHead();
    
    
	};
}

#endif
