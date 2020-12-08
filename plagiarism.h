#include <string>
#include <cstring>
#include <math.h>
#include <vector>
#include <array>
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#define SIZE 25107
using namespace std;

//made everything lower case and picks out list of word-length strings and puts them in vector s
void PreProcess(string file_name, vector<string> &s, int word, string dir);



// hash function to pick right index on hash table
int hashFunc(string x, int hash_length);

void deleteFiles(vector<string> &s, int p, string dir);

class Node
{
    public:
    Node()
    {
        number = 0;
        file1 = "sfdsf";
        file2 = "sffwfg";
    }

    string getFirstFile()
    {
        return file1;
    }

    string getSecondFile()
    {
        return file2;
    }

    int getNumber()
    {
        return number;
    }


    void setFirstFile(string x)
    {
        file1 = x;
    }

    void setSecondFile(string y)
    {
        file2 = y;
    }

    void setNumber(int f)
    {
        number = f;
    }
    
   

    private:
     string file1;
     string file2;
     int number;
    

};

class LinkedList
{
    public:
    void addData(string x, string y)
    {
        cout << "addData" << endl;
        int flag = 0;
        for(int i = 0; i < list.size(); i++)
        {
            if(list.at(i).getFirstFile()==x  & list.at(i).getSecondFile()==y )
            {
                int d = list.at(i).getNumber();
                int g = d+1;
                list.at(i).setNumber(g);
                flag=1;
                break;
            }
        }
        if(flag == 0)
        {
            Node t;
            t.setFirstFile(x);
            t.setSecondFile(y);
            t.setNumber(1);
            list.push_back(t);
        }
    }

    void sort()
    {
        cout << "sort" << endl;
        for(int i = 0; i < list.size(); i++)
        {
            for(int j = 0; j < list.size()-1; j++)
            {
                if(list.at(j).getNumber() < list.at(j+1).getNumber())
                {
                    Node r;
                    r.setFirstFile(list.at(j).getFirstFile());
                    r.setSecondFile(list.at(j).getSecondFile());
                    r.setNumber(list.at(j).getNumber());
                    Node t;
                    t.setFirstFile(list.at(j+1).getFirstFile());
                    t.setSecondFile(list.at(j+1).getSecondFile());
                    t.setNumber(list.at(j+1).getNumber());
                    list.at(j)=t;
                    list.at(j+1)=r;
                }
            }
        }
    }

    void printList(int m)
    {
        cout << "printList"<< endl;
        for(int i = 0; i < list.size(); i++)
        {
            cout << list.at(i).getNumber() << endl;
            if(list.at(i).getNumber() > m)
            {
                cout<<list.at(i).getNumber()<<" : "<<list.at(i).getFirstFile()<<" , "<<list.at(i).getSecondFile()<<endl;
            }
            
        }
    }

    private:
    vector<Node> list;
};

class HashTableNode
{
    public:
    HashTableNode()
    {
        file = "Blah";
        input = "Blah1";
        next =  nullptr;
    }
    string getFile()
    {
        return file;
    }

    HashTableNode* getNext()
    {
        return next;
    }

    string getString()
    {
        return input;
    }
    
    void setFile(string x)
    {
        file = x;
    }

    void setNext(HashTableNode* t)
    {
         next = t;
    }

    void setString(string g)
    {
        input = g;
    }

    private:
    string file;
    string input;
    HashTableNode* next;

};

class HashTable
{
    public:
    HashTable()
    {
        for(int i = 0; i < SIZE; i++)
        {
            HashTableNode f;
            myarr[i].setFile(f.getFile());
            myarr[i].setString(f.getString());
            myarr[i].setNext(f.getNext());

        }
    }

    void countCollisions(string currFile,LinkedList &t,int x, string f)
    {

        cout << "Collisions" << endl;
        HashTableNode* r = &myarr[x];
        
        while(r!=nullptr)
        {
           if(r->getFile()!=currFile & r->getString()==f)
           { 
            if(currFile < r->getFile())
            {
                t.addData(currFile,r->getFile());
            }
            else
            {
                t.addData(r->getFile(),currFile);
            }
            
             
           }
           r = r -> getNext();

        }


    }
    
    void insertData(string currFile,string x,LinkedList &t)
    {
        cout << "insertData" << endl;
        int index = hashFunc(x,SIZE);
        
        if(myarr[index].getFile()=="Blah" & myarr[index].getString()=="Blah1")
        {
            
            myarr[index].setFile(currFile);
            myarr[index].setString(x);
        }
        else
        {
            
            int flag = 0;
            HashTableNode* r = &myarr[index];
            if(r->getFile()==currFile & r->getString()==x)
            {
                flag = 1;
            }
            else
            {
               while(r->getNext() != nullptr)
               {
                if(r->getNext()->getFile()==currFile & r->getNext()->getString()==x)
                {
                    flag = 1;
                    break;
                }
                r = r->getNext();
               }
            }
            
            
            if(flag == 0)
            {
               HashTableNode* f = new HashTableNode;
               f->setFile(currFile);
               f->setString(x);
               f->setNext(nullptr);
               r->setNext(f);
               countCollisions(currFile,t,index,x);
            }
            
            
        }

        
        

      
    }

   

    private:
    array<HashTableNode,SIZE> myarr;
};
