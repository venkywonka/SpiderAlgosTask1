#include<stdio.h>
#include<string.h>
#include<fstream>
#include<iostream>
#include<vector>
using namespace std;
vector<string> lines;
char query[100];
int pgno,lineno;


//computelps() function
void computelps(int M,int *lps){// length of the previous longest prefix suffix

    int len = 0;
 
    lps[0] = 0; // lps[0] is always 0
 
    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M)
    {
        if (query[i] == query[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else // (query[i] != query[len])
        {
            
            // to search step. 
            if (len != 0)
            {
                len = lps[len-1];
 
                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    } 
	}



//string searching using kmp algorithm
void KMPSearch()
{
   int M = strlen(query);
    int N = strlen(lines[lineno].c_str());
 
    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];
 
    // Preprocess the pattern (calculate lps[] array)
    computelps(M, lps);
 
    int i = 0;  // index for line[]
    int j  = 0;  // index for query[]
    while (i < N)
    {
        if (query[j] == lines[lineno][i])
        {
            j++;
            i++;
        }
 
        if (j == M)
        {	j = lps[j-1];
        	int index = i-j;
        	if(index==0){
        		if(lines[lineno][M]==' '||lines[lineno][M]=='\0'){   //checking if its a word and not a subword of the required query
					if(1){                   //updating into output textfile
						cout<<"\npage:"<<pgno<<", line:"<<lineno+1;
						}
            	}
			}
			else if((lines[lineno][index-1]==' '&&lines[lineno][index+M]==' ')||(lines[lineno][index-1]==' '&&lines[lineno][index+M]=='\0')){     //checking if its a word and not a subword of the required query
					if(1){                           //updating into output textfile
						cout<<"\npage:"<<pgno<<", line:"<<lineno+1;
						}
            }
            
        }
 
        // mismatch after j matches
        else if (i < N && query[j] != lines[lineno][i])
        {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j-1];
            else
                i = i+1;
        }
    }
    if(1){                   //updating into output textfile
		cout<<"\nnone";
		}
}


//readPage function
void readPage(int pageno){
	ifstream p;
	string filename = "page_1.txt";
	string l;
	if(pageno<=9)filename[5]=(char)pageno;
	else { filename[5]= (char) pageno/10;
	       filename[6]= (char) pageno%10;
		   filename[7]='.';
		   filename[8]='t';
		   filename[9]='x';
		   filename[10]='t';
		   }
	p.open(filename.c_str());
	
	while(getline(p,l)){
		lines.push_back(l);
		
	}
	p.close();
}

//main function
int main(){
	ifstream q;
	q.open("queries.txt");
	while(q>>query){
		if(1){
			cout<<"\nword:"<<query;
			cout<<"\noccurrences:";
				}	
		for(pgno=1;pgno<=10;++pgno){
			lines.clear();			
			readPage(pgno);	
			for(lineno=0; lineno<lines.size();++lineno)	
				KMPSearch();
		}			
	}		
	q.close();
	return 0;		
}





