

#ifndef HASHMAP_H
#define HASHMAP_H

#include "Posting.h"
#include "Hashnode.h"
using namespace P;
using namespace H;
// #include "PostingList.h" 
// #include "PostingNode.h" 
// using names
namespace HM{
	

class HashMap{
	
		
	private:
		
		HashNode **Table; // 2d table
		
		friend class HashNode;
			
	public:
				
		HashMap(); // constructor
		~HashMap(); // destructor
			
			
			
		int HashFun(string w); // hasher
		
		
		PostingNode* getPosting(const string &word); // gets posting list head	
		void putPosting(const string &word, const int &docID, const int &pos); // inserts posting in hash table
		
		void remove(const string &word); // remove a word
	
	
	};
}
#endif
