#include "plagiarism.h"
#include <fstream>
#include <cctype>
#include <ctype.h>

int hashFunc(string x, int hash_length)
{
   int hashVal=0;
   for(int i = 0; i<x.size(); i++)
   {
       hashVal ^= (hashVal << 5)+(hashVal << 2)+x[i];
   }
   int f = abs(hashVal % hash_length);

   return f;
}

void PreProcess(string file_name, vector<string> &s, int word, string dir)
{

    ifstream inFile("./" + dir + "/" + file_name);
    
    string t;
    string h;
    string empty;
    vector<string> f;
    inFile >> t;
    while(inFile)
    {
        inFile>>h;
        t = t + h;
        h.clear();
    }

   
    

    

    for(int i = 0; i < t.size(); i++)
    {
        

        if(isalpha(t[i]) | isdigit(t[i]))
        {
            if(isalpha(t[i]))
            {
                t[i] = tolower(t[i]);
                empty+=t[i];
            }
            else
            {
                empty += t[i];
            }
            
        }
        else if(t[i] == '\'')
        {
            empty+=t[i];
        }
        else
        {
            f.push_back(empty);
            empty.clear();
        }
        
    }

    

    empty.clear();
    if(f.size()>=word)
    {
        for(int i = 0; i < f.size()-word+1; i++)
        {
            int g = 0;
            for(int j = 0; j < word-1; j++)
            {
                g = j;
                empty+=f.at(i+j) + " ";
            }
            empty += f.at(i+g+1);
            s.push_back(empty);
            empty.clear();
        }
    }


    /*for(int i = s.size()-1; i >= 0; i--)
    {
        for(int j = i - 1; j >= 0; j--)
        {
            if(s.at(i) == s.at(j))
            {
                s.erase(s.begin()+i);
                break;

            }
        }
    }*/



}

void deleteFiles(vector<string> &s, int p, string dir)
{
    string g;
    
    for(int i = 0; i < s.size(); i++)
    {
        ifstream inFile("./" + dir + "/" + s.at(i));
        inFile >> g;
        string h;
        while(inFile)
        {
           inFile>>h;
           g = g + h;
           h = " ";
        }
        if(g.size() < p)
        {
           s.erase(s.begin()+i);
           i--;
        }
        g.clear();

    }
}

