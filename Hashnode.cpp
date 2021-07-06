//HashNode.cpp
#include <bits/stdc++.h>
using namespace std;

#include "HashNode.h" 
#include "Posting.h" 

using namespace H;
using namespace P;
	
HashNode::HashNode() { 
	next = NULL;
}
			
				
HashNode::HashNode(const string &key, const int &docID, const int &pos){
	word = key;
	next = NULL;
	LIST = new PostingList();
	LIST->Push(key, docID, pos);
}
			
				
string HashNode::getKey() const{
	return word;
}


string HashNode::getWord(){
	return word;
}



PostingNode* HashNode::getListHead() {
	return LIST->getHead();
}

				
PostingList* HashNode::getList() {
	return LIST;
}
	
				
void HashNode::setPosting(const string& word, const int &docID, const int &pos){
	LIST->Push(word, docID, pos);
}


void HashNode::deleteList(){
	LIST->deleteAll(); 
}


HashNode* HashNode::getNext(){
	return next;
}
