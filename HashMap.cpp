//HashMap.cpp


#include <bits/stdc++.h>
#include "HashMap.h"
#include "HashNode.h"
#include "Hashnode.cpp" 
#include "Posting.h"


using namespace std; 
#define TABLE_SIZE 300 //this would be a large number incase of bigger datasets

using namespace HM; // hashmap namespace
using namespace P; // posting namespace
using namespace H; // hashnode namespace
				
HashMap::HashMap(){
	Table = new HashNode *[TABLE_SIZE](); // initialise table 
}
				
HashMap::~HashMap(){
	
	
	cout << "\n HashMap Destructor \n"; 
	
	
	for(int i = 0; i < TABLE_SIZE; ++i){
		
		
		HashNode *cur = Table[i]; // access the row 
		while(cur != NULL){ // iterate through the buckets in the same row (collisions)
			
			HashNode *prev = cur;
			cur->deleteList(); // deletes the posting list (multiple instances of same word)
			cur = cur->next;
			delete prev;
		}
		
		delete cur; // delete the row
		Table[i] = NULL;
	}
	delete[] Table;
}

int HashMap::HashFun(string w) // returns an integer hash value
{
    
	int sum = 0;
	
	for (int k = 0; k < w.length(); k++)
		sum = sum + int(w[k]);
	
	return  sum % TABLE_SIZE;	
}
				
PostingNode* HashMap::getPosting(const string &word){ // gets the posting list (multiple instances of same word)
	int hashVal = HashFun(word);
	HashNode *cur = Table[hashVal]; // accesses the exact row where the word was hashed
	
	
	while(cur != NULL){ // iterate through the buckets (which might have collisions)
	
		if(cur->getWord() == word){ // found the word to get 
		
			PostingNode *temp = cur->LIST->getHead(); // get that words posting list
			if(temp != NULL){
				return temp; // return the list
			}
			else{
				cout << "\n\n\t Posting List for " << word << " is empty. \n\n";
				return NULL;
			}
		}
		cur = cur->next;
	}
}
				
void HashMap::putPosting(const string &word, const int &docID, const int &pos){
	
	int hashVal = HashFun(word);
	
	
	HashNode *cur = Table[hashVal]; // the table row with that hash value is directly accessed 
	HashNode *prev = NULL;
	
	while(cur != NULL && cur->word != word){ // check if there are already words present there and are they the same word or different word
		prev = cur;
		cur = cur->next;
	}
	
	if(cur == NULL){ // at this point, there might be words present or not, this is decided in the next condition
		
		cur = new HashNode(word, docID, pos);
		if(prev == NULL){ // if there was no other word present
			Table[hashVal] = cur;
		}
		else{ // if there was another word present
			prev->next = cur;	
		}
	}
	else{ // its the same word, only posting list (multiple instances of same word) is updated
		cur->LIST->Push(word, docID, pos);
	}
}

void HashMap::remove(const string &word){
	
	unsigned int hashVal = HashFun(word);
	HashNode *cur = Table[hashVal]; // value to be removed is directly accessed
	
	HashNode *prev = NULL;
	
	while(cur != NULL && cur->word != word){ // once again we check if there is word present there and if they are the same or different word
		prev = cur;
		cur = cur->next;
	}
	
	if(cur == NULL){ // there were no word present and even if there were then it wasnt the required words
		return;
	}
	else{ // there are multiple words or just a single word
		if(prev == NULL){ // single word
			Table[hashVal] = cur->next; // just accesses the next value and assigns it. it could also be NULL
		}
		else{ // multiple words
			prev->next = cur->next; // just accesses the next value and assigns it. it could also be NULL
		}
		delete cur; // deleting also deletes the posting list
	}
}
//#endif
