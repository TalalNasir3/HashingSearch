/*
MADE BY: Talal Nasir

REQUIREMENTS TO RUN THIS PROGRAM:
C += 11;


THE PROGRAM WORKS ON THE BASIS OF USING INVERTED INDEXING ON HASHMAP IN WHICH IT CONSISTS OF TWO KINDS OF LISTS, BUCKETLIST AND POSTINGLIST. THE BUCKETLIST REPRESENTS THE
BUCKETS WHICH ARE USED TO STORE VALUES, BY BUCKET LIST WE MEAN THAT THERE MIGHT BE POTENTIAL COLLISIONS SO WE RESOLVE THE COLLISIONS BY
SEPARATE CHAINING. THE BUCKETS ARE INDEXED BY USING A HASH FUNCTIONS. ON THE OTHER HAND, EACH BUCKET CONTAINTS A VALUE, THE WORD ITSELF,
NOW THIS WORD HAS ITS OWN POSTING, POSTING IS THE POSITION AND THE DOCUMENT ID IN WHICH THIS WORD IS LOCATED. SO IF THE DATASET IS VERY LARGE
THEN WE CAN EASILY KNOW THE POSITION OF THE WORD IN THE DOCUMENT IN O(1) TIME. THE POSTING LIST REPRESENTS ALL THE MULTIPLE INSTANCES OF THE SAME
WORD. SO THE HASH TABLE CAN BE SEEN AS 3D, 2D BEING THE TABLE OF BUCKET AND INDEX, AND THE POSTING LIST BEING THE 3RD DIMENSION. 

*/


#include <bits/stdc++.h> 
#include <windows.h> 
#include<string>
#include<sstream>

#include "HashMap.h"
#include "HashMap.cpp"
#include "Posting.h"
#include "UserQueries.h"


using namespace P;
using namespace HM;
using namespace std;
using namespace UQ;



SearchSystem S; // searching system

HashMap hm; // the hash map

int queries = 0; // queries counter


// checking values


bool readOnce = true;
bool wordExists = false, wordExisted = false;



// highlighting word 


string Color(int color=7, string Message = ""){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    return Message;
}


// stop words are not to be hashed


bool isStopWord(string word){
	return(word == "the" || word == "of" || word == "is" || word == "a" || word == "an" || word == "in" || word == "it" || word == "with" 
	|| word == "has" || word == "by" || word == "to" || word == "and" || word == "also" || word == "that" || word == "was" || word == "later" 
	|| word == "," || word == "." || word == "-" || word == "" || word == "as" || word == "because" || word == "since" || word == "for" 
	|| word == "but" || word == "which" || word == "what" || word == "why" || word == "how" || word == "when" || word == "all" || word == "are" 
	|| word == "have" || word == "now" || word == "continues");
}




// reading paragraph from the doc file and hashing it



void readParagraph(const int& docID){
	
	fstream file;
	file.open("PakistanParagraph" + std::to_string(docID) + ".txt");
	
	
	string line, word;	
	int count = 0; // count number of words to find position
	
	
	if(file.is_open()){
	
		while (getline(file, line)){
			
			istringstream iss(line);
			
			
			while(iss>>word){
				
				++count;
				if(!isStopWord(word)){
					hm.putPosting(word, docID, count); // hashes the words	
				}
			} 
    	} 	
	}
	else{
		cout << "\n\n\t File couldn't open. \n\n";
	}
	
}

// displaying paragraph


void displayParagraph(string keyWord, const int& docID, const int& pos){	
	
	
	fstream file;
	file.open("PakistanParagraph" + std::to_string(docID) + ".txt");
	
	
	string line, word;	
	int count = 0;
	
	
	if(file.is_open()){
	
		while (getline(file, line)){ 
			istringstream iss(line);
			while(iss>>word){
				if(word == keyWord){
					cout << Color(10, word) << " ";
				}
				else{
					Color();
					cout << word << " ";
				}
			}
			cout << endl << endl << endl ; 
    	}
		
		system("pause"); 	
	}
	else{
		cout << "\n\n\t File couldn't open. \n\n";
	}
}


// displaying the position and docID



void displayPosting(string word, int curDoc){
	
	
	PostingNode* temp;
	
	
	temp = new PostingNode();
	temp = hm.getPosting(word); // gets posting values
	PostingNode* temp2 = temp; // store for later as temp will change
	
	
	wordExists = false;
	bool displayOnce = true;
	
	
	while(temp){
	
	
		if(temp->getDocID() == curDoc)
		{
		
			if(displayOnce)
			{
				cout << "\n\n\n\t\t " << word << " is located as such: \n\n ";
				displayOnce = false;
			}
			
			wordExists = true;
			wordExisted = true;
				
				
			system("pause");
			cout << "\n\n\t\t Document " << temp->getDocID() << " at the Position : " << temp->getPos(); 
				
		}
			
		temp = temp->getNext();
				
	}
	
	
	while(temp2)
	{
	
		if(temp2->getDocID() == curDoc)
		{
			cout<<temp2->getWord();

			wordExists = true;
			wordExisted = true;
			system("pause");
			break;
			
		}
		
		temp2= temp2->getNext();
	}
	
	if(wordExists)
	{
		cout<<"\n\n\t\tDOCUMENT "<<curDoc<<": ";
		cout << "\n\n\tIt is highlighted in the paragraph below: \n\n\n";
		displayParagraph(temp2->getWord(), curDoc, temp2->getPos());
	}
	
	
	system("pause");
	
}


// console interface



void displayOptions()
{
	cout<<"\n\n\t\t1) Search For A Word.\n\n\t\t";
	cout<<"2) Search Using Previous Queries (HISTORY).\n\n\t\t";
	cout<<"3) Delete Previous Query.\n\n\t\t";
	cout<<"4) Search For Sentence.\n\n\t\t";
	cout<<"5) Exit Program.\n\n\t\t";
}



string exitAnswer()
{
	string ans;
	
	system("CLS");
	cout<<"\n\n\t\tOFFLINE SEARCH ENGINE\n\n\t\t";
	cout<<"Would You Like To Exit The Program ? (Yes | No)\n\n\t\t";
	
	cin>>ans;
	
	return ans;
}



string MainMenu()
{
	system("CLS");
	
	
	cout<<"\n\n\t\tOFFLINE SEARCH ENGINE\n\n\t\t";
		
	displayOptions();
	
	
	int ans;
	cin>>ans;
	
	
	
	switch(ans){
		
		
		case 1:{
			
			
			cin>>S;
			queries = S.getTotalQueries();
			string q = S.getQuery(queries);
				
			for(int i = 1; i<=4; i++)
				displayPosting(q, i);
				
				
			system("pause");
			
			
			if(!wordExisted )
			{
				wordExisted = false;
				cout<<"\n\n\t\tThe word: "<<q<<" doesn't exist in any document.\n\n\t\t";
				system("pause");
			}
			
			
			break;
			
		}
		
		
		case 2:{
			
			
			system("CLS");
			cout<<"\n\n\t\tOFFLINE SEARCH ENGINE\n\n\t\t";
			
			
			int i = 0;
			
			
			if(readOnce)
			{
				i = S.readSavedQueries();
				readOnce = false;
			}
			
			
			
			S.displayQueries();		
			
			
			int q = S.getTotalQueries();
			
			
			if(q > 0 || !(i == 1))
			{
			
				int n = 0;
				
				
				cout<<"\n\n\t\tChoose a Query (1 For Query No. 1): ";
				cin>>n;
				
				
				
				while(q)
				{
					if( n == q)
					{
						S.EnterQuery(S.getQuery(n));
						break;
					}
					
					q--;
					
				}
				
				
				
				queries = S.getTotalQueries();
				string a = S.getQuery(queries);
				
				
				for(int i = 1; i<=4; i++)
					displayPosting(a, i);
			
			
			
					
				if(!wordExisted )
				{
					wordExisted = false;
					cout<<"\n\n\t\tThe word: "<<q<<" doesn't exist in any document.\n\n\t\t";
					system("pause");
				}
					
					break;
					
					
			}
			else
			{
			
				system("CLS");
				
				cout<<"\n\n\t\tOFFLINE SEARCH ENGINE";
				cout<<"\n\n\t\tNo History Searches Available!\n\n\t\t";
				system("pause");
			}
				
				
			break;
			
			
		}
			
		case 3:{
				
			system("CLS");
			cout<<"\n\n\t\tOFFLINE SEARCH ENGINE\n\n\t\t";	
			
			
			int q = S.getTotalQueries();
			
			
			if(q > 0)
			{
				int n =0;
				cout<<"\n\n\t\tChoose a Query To Delete: \n\n\t\t";
				S.displayQueries();
				
				
				cin>>n;
				
				while(q)
				{
					if( n == q)
					{
						queries--;
						
						
						cout<<n<<endl<<q<<endl;
						system("pause");
						
						S.deleteQuery(n);
						
						break;
					}
					
					
					q--;
				}
	
			}
			
			
			else
			{
				cout<<"\n\n\t\tNo History!\n\n\t\t";
				system("pause");
			}
			
			
			break;
			
		}
		
		case 4:{
			
			//if user decides to enter a sentence 
			system("CLS");
			cout<<"\n\n\t\tOFFLINE SEARCH ENGINE\n\n\t\t";	
			
			string str;  //sentence
			cout<<"\n\n\t\tEnter Sentence: ";

			getline(cin >> std::ws, str); // getline with white space
			
			
			
			system("pause");
			
			
			istringstream ss(str); // read sentence
			string word = "";
			
			while(ss>>word) // word by word
			{
				system("pause");
				queries++;
				S.EnterQuery(word);
				
				string	q = S.getQuery(queries);
				
				for(int i = 1; i<=4; i++)
					displayPosting(q, i);
		
				system("pause");
				
				
				
				if(!wordExisted)
				{
				
					wordExisted = false;
					cout<<"\n\n\t\tThe word: "<<q<<" doesn't exist in any document.\n\n\t\t";
					system("pause");
				}
				
			}
			
					
			break;
		}
		
		
		case 5:{
			
			return exitAnswer();
			break;
			
		}
		
		default:{
			
			cout<<"\n\n\t\tERROR!!!\n\n\t\tWrong Input!!!";
			system("pause");
			
		}
		
	}
	
	return "NO";
}


int main(){
	
	for(int i = 1; i<=4; ++i)
	{
		readParagraph(i); // read paragraph for hashing
	}
	
	string ans = "NO", q;
	
	
	// if user answers yes then program is exited

	while(ans == "No" || ans == "no" || ans == "NO")
	{
		ans = MainMenu();
	}	

	return 0;
}
