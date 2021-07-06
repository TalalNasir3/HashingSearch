//UserQueries.h

#include<bits/stdc++.h>
#include <cstdio>
#include<stdio.h>
#ifndef USERQUERIES_H
#define USERQUERIES_H
using namespace std;


namespace UQ{




class SearchSystem{


  private:
	
	
	queue<string> uq;//queue Data Structure used 
	int queries;//query counter
    
	
	
	// private functions
	
	
	
	void deleteCurrentQuery(string query)//deleting a query from a file 
	{
		
		fstream file;
		ofstream tmp;
		string line;
		
		
		//temp file procedure used
		
		tmp.open("TEMP FILE.txt");
		file.open("User Query.txt");
		
		bool once = true;
		
		while(getline(file,line)){
		
			if(line == query && once){//once for deleting one instance out of multiple instances e.g. deleting  

				//hi
				//hi<------only deleting this one
				//hi
				once = false;
				continue;
			}
			else{
				tmp<<line<<endl;
			}
		
		
		}
		
		
		file.close();
		tmp.close();
				
		//removing old file and renaming temp to the old file
		
		
		remove("User Query.txt");
		rename("TEMP FILE.txt", "User Query.txt");
	}           
	
	
	//saving a user query into one file


	void saveUserQueries(string userQuery)
	{
		
		ofstream file("User Query.txt", ios :: app);
		
		if(file.is_open()){
			file << userQuery << endl;
		}
		else{
			cout<<"\n\n\t\tOFFLINE SEARCH ENGINE";
			cout<<"\n\n\t\tFile Couldn't be Opened\n\n\t\t";
			system("pause");
		}
		
		file.close();
	}
    
	
  public:
    
	
	// constructors and destructors
	
	
	SearchSystem() : queries(0){}
    
	
	~SearchSystem(){
		
		
		string ans;
		queries = 0;
		
		
		system("CLS");
		
		cout<<"\n\n\t\tOFFLINE SEARCH ENGINE\n\n\t\t";
        
		
		// asking user if they want to delete the query file
		
		
		cout<<"\n\n\t\tDelete All User Queries ? (Yes | No) \n\n\t\t";
        cout<<"Answer: ";
		cin>>ans;
		
		
		if(ans == "Yes" || ans == "yes" || ans == "YES"){
			remove("User Query.txt");
		}
		

	}
	
	// query functions
	
	
	
	int readSavedQueries()//for getting saved queries from file in order to use them again for searching
	{
		queries = 0;
		
		
		fstream file;
		file.open("User Query.txt");
		
		if(file.tellg()){ // file is empty 
			file.close();
			return 1;
		}
		
		
		while(!uq.empty()){
			uq.pop();
		}
		
		int c = 0;
		
		ofstream tmp;
		string line;
		
		while(getline(file,line)){
			
			uq.push(line);
			queries++;
		}
		
		
		file.close();
		
	}
	
	
	void EnterQuery(string userQuery)//pushes user query into queue and saves it to file
	{
	
		uq.push(userQuery);
		queries++;
		
		
		saveUserQueries(userQuery);//private function called to save query to file
    }
	
	
	
	void deleteQuery(int n)//function used to delete a query at position n (n is not index based)
	{
	
		//n is user's choice of query which they would like to delete
		
		int c = 1;
		
		queue<string> t;//temp queue used
		
		
		while(c<=queries)
		{
            string q = uq.front();
            uq.pop();
            if(c == n){
            	this->deleteCurrentQuery(q);//private delete function called which deletes user's query from file 
             	queries--;//query counter decremented
             	break;
			}
			
			t.push(q);//temp queue is being used to enqueue/push queries from old queue to new queue
			c++;
		}
		
		
		while(!uq.empty())//remaining queries left, if any, in old queue 
		{
			t.push(uq.front());
			uq.pop();
		}
		
		
		//at this point temp queue contains all queries without the one chosen by user
		uq = t;//temp queue becomes main queue 	 
		
	}
	
	
	
	friend istream& operator >> (istream& in, SearchSystem& rhs)//operator '>>' used for inputting a query
    {
    	string q;
        
		
		cout<<"\n\n\t\tSearch For A Word (Word Must exist in at least one document) : ";
        
		in>>q;
		
		transform(q.begin(), q.end(), q.begin(), :: tolower); // lowercase        
        
        rhs.uq.push(q);
        rhs.queries++; 
        rhs.saveUserQueries(q);//saved to file
    
	}
	
	
	int getTotalQueries()//getter
	{
		return queries;
	}
	
	
	void displayQueries()//for displaying all queries entered so far
    {
		int c = 1;
		
		
		while(c <= queries)
        {
            //to traverse the queue, front is popped and enqueued/pushed until counter catches up to no. queries
            string q = uq.front();
            cout<<"\n\n\t\tQuery "<<c<<": "<<q;
            uq.pop();
            uq.push(q);
            c++;
                    
        }

    }
	
	
	string getQuery(int i)//getter for query
    {
    	int c = 1;
        string q;
        
		queue<string> t = uq;
    	
		
		while(c <= queries)
        {
            //to traverse the queue, front is popped and enqueued/pushed until counter catches up to no. queries
            q = t.front();
			t.pop();
                    
			if(c == i)//if counter is equal to the position of query in queue (index based not assumed)
            {
                return q;//then respective string returned
            }
            
			
			c++;
    	}
        
		
		return "NO";
    }
            
             
    };
}
#endif
