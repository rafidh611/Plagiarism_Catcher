
#include "plagiarism.h"

using namespace std;

int getdir (string dir, vector<string> &files) {
  DIR *dp;
  struct dirent *dirp;
  if((dp  = opendir(dir.c_str())) == NULL) {
    cout << "Error(" << errno << ") opening " << dir << endl;
    return errno;
  }
  
  while ((dirp = readdir(dp)) != NULL) {
    files.push_back(string(dirp->d_name));
  }
  closedir(dp);
  return 0;
}

int main(int argc, char *argv[]) 
{
  
  if (argc < 2) {
    cout << "ERROR: enter directory name as an argument" << endl;
    return (0);
  }
  int p = atoi(argv[2]);
  int m = atoi(argv[3]);
  string dir = argv[1];
  vector<string> files = vector<string>();
  string str;

  getdir(dir,files);

  files.erase(files.begin());
  files.erase(files.begin());

  cout << files.size() << endl;

  deleteFiles(files,p,dir);

  for(int i = 0; i < files.size(); i++)
  {
    cout << files.at(i) << endl;
  }

  HashTable table;
  LinkedList list;
  vector<string> file1;
  

  for(int i = 0; i < files.size(); i++)
  {
    PreProcess(files.at(i),file1,p,dir);
    cout << file1.size() << endl;
    for(int j = 0; j < file1.size(); j++)
    {
      table.insertData(files.at(i),file1.at(j),list);
    }
    file1.clear();
   
  }
  list.sort();
  list.printList(m);
 
			  
  return 0;
}
