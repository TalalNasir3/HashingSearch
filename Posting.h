#include <bits/stdc++.h>
using namespace std;


#ifndef POSTING_H
#define POSTING_H


namespace P{
	
	
class PostingNode{


  private:
 
	
	string word;
    int docId; // document in which the word is located
	int pos; // the position at which it is
    PostingNode* next;
	
	
	friend class PostingList;


  public:
	
	
	
	// constructors
		
	PostingNode() : next(NULL){}

	PostingNode(string w, int dId, int p){
		word = w, 
		docId = dId;
    	pos = p;
    	next = NULL;
	}

	
	// getters
		
		
		
	int getDocID()
	{		
		return docId;		
	}
		

	int getPos()
    {
        return pos;
    }
        
	PostingNode* getNext()
    {
        return next;
	}
		
	string getWord()
	{
		return word;
	}



};

class PostingList{



private:
  
  
  PostingNode* head;


public:


  
  PostingList():head(NULL){};
  
  
  void deleteAll(){ // deletes the whole list
  
  	if(head != 0){
		PostingNode* c = head;
		PostingNode* t = 0;
		while(c != 0)
		{
			t = c;
			c = c->next;
			t->next = 0;
			delete t;
			t = 0;
		}
	}
	
   }
    
	void Push(string w, int docId, int pos){ // push a node at the end of the list
	
		PostingNode* cur = head;
		PostingNode* newNode = new PostingNode(w, docId, pos);
		
		if(!head){ 
			head = newNode;
    		return; 
		} 

		while(cur->next){ 
			cur=cur->next; 
		}
		
		cur->next = newNode;
	
	}
	
	
	PostingNode* getHead()
	{
		return (head)? head : 0; 
	}
	
	   
};



}
#endif
