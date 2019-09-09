
#include<bits/stdc++.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <fcntl.h>
#include <fstream>
#define ARGVSIZE  400
#define DELIM "\n\t\r "

// uid_t getuid(void);
// uid_t geteuid(void);
using namespace std;

void parsestring(char *s){

}

int main(){

  FILE *fp,*fp1;
  ifstream inFile;
  const char *homedir;
  const char *user;
   char path[1024];
   char *clargs[ARGVSIZE+1];
  char hostname[200];
  char s[100],temp[100];
  const char *end="\n";
  char *data;
  int flag=1;
//   fp = fopen("bashrc.txt","w+");
  homedir = getpwuid(getuid())->pw_dir;
//   cout<<homedir;
// //  path="HOME=";
//   fprintf(fp ,"HOME=%s\n",homedir);
//   //fclose(fp);
//   //close(fp);
//   //fp = fopen("bashrc.txt","w+");
   user = getpwuid(getuid())->pw_name;
//     cout<<user;
//   //path = "USER=";
//   fprintf(fp ,"USER=%s\n",user);
  int res = gethostname(hostname, sizeof(hostname));
//  fprintf(fp,"HOSTNAME=%s\n",hostname);
// fclose(fp);
 //open manpath.config file
 fp1 = fopen("/etc/manpath.config","r");
  while(fgets(s, sizeof(s), fp1)!=NULL){
    //fscanf(fp1, "%s",s);
   fputs(s,fp1);
  // cout<<s<<endl;
//  cout<<s<<endl;
  int n=1;

  clargs[0] = strtok(s,DELIM);
  while((clargs[n] = strtok(NULL,DELIM))!= NULL)
    n++;

  if(strcmp(clargs[0],"MANPATH_MAP")==0){
    flag = 0;
    strcat(path,clargs[1]);
    strcat(path,":");
    //cout<<path<<endl;
  }

  }
  fclose(fp1);
  fp = fopen("bashrc.txt","w+");

    fprintf(fp, "HOME=%s\n",homedir);
    fprintf(fp, "USER=%s\n",user);
    fprintf(fp, "HOSTNAME=%s\n",hostname);
    if(flag == 0)
      fprintf(fp, "PATH=%s\n",path);
  fclose(fp);



return 0;
}
