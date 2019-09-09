#include<bits/stdc++.h>
#include <stdlib.h>
#include<stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <wait.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <fcntl.h>
#include <dirent.h>
#include <termios.h>
#define CTRL_KEYPRESS(k) ((k)  & 0x1f)


using namespace std;

int status;
// string home,user,hostname,path;
vector<string>hist;
//queue<char*>historylist;

//char HOME[BUFSIZE], *PATH, *USER, *HOSTNAME, *currdir, *PS1;
char curpath[100];
//max size of command line
#define BUFSIZE 1024
//max no of arguments
#define ARGVSIZE  400
//while space delimiters for strtok
#define DELIM "\n\t\r "
//defining HISTSIZE FOR NOW

char HOME[BUFSIZE];
char USER[BUFSIZE];
char HOSTNAME[BUFSIZE];
char PATH[100000];
char PS1;
//char *USER,*HOSTNAME,*PATH;

void enableRawInputMode(){
  struct termios rw;
  tcgetattr(STDIN_FILENO, &rw);
  rw.c_lflag &= ~(ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &rw);
}

string printprompt(){
//  setvariables();
  string home=(string)HOME;
  int homelen = strlen(HOME);
  int userlen = strlen(USER);
  int hostnamelen = strlen(HOSTNAME);

  string user=(string)USER;
  string hostname=(string)HOSTNAME;
  string currentpath = (string)curpath;
  //string symbol;
  string ps1;
  if(strcmp(USER,"root")==0){
    ps1 = "#";

  }
  else {
    ps1 = "$";

  }

  string prompt=user+"@"+hostname+currentpath+ps1+" ";
  //cout<<prompt;
  return prompt;

}

void tstphandler(int signo){
//  cout<<"in handler\n";
	//signal(SIGTSTP, tstphandler);
	//cout<<"stop handler";
	//fprintf(stderr,"stop interrupt");
	//cout<<"\n$";
	//printprompt();
	cout<<"Exiting";
	cout<<endl;

	//cout<<"$";
	fflush(stdout);

	return;
	//takeInput();

	//takeInput();
	//exit(1);
}


void setvariables(){
  char *clargs[10000];
  char s[10000];
  FILE *fp;
  fp = fopen("bashrc.txt","r");
  while(fgets(s, sizeof(s), fp)!=NULL){
    //fscanf(fp1, "%s",s);
   fputs(s,fp);

  int n=1;

  clargs[0] = strtok(s,"=");
  while((clargs[n] = strtok(NULL,"="))!= NULL)
    n++;

  if(strcmp(clargs[0],"HOME")==0){
    //HOME = clargs[1];
    strcpy(HOME,clargs[1]);
    //printf("home = %s\n",HOME);
  }
  else if(strcmp(clargs[0],"PATH") == 0){
    strcpy(PATH,clargs[1]);
    //printf("path = %s\n",PATH);
    //PATH = clargs[1];
  }
  else if(strcmp(clargs[0],"USER")==0){
    strcpy(USER,clargs[1]);
  //  USER = clargs[1];
  }
  else if(strcmp(clargs[0],"HOSTNAME")==0){
    strcpy(HOSTNAME,clargs[1]);
    //HOSTNAME = clargs[1];
  }
  if(strcmp(USER,"root") == 0){
    PS1 = '#';
  }
  else{
    PS1 = '$';
  }

  }
  int homelen = strlen(HOME);
  int userlen = strlen(USER);
  int hostnamelen = strlen(HOSTNAME);
  HOME[homelen-1]='\0';
  USER[userlen-1]='\0';
  HOSTNAME[hostnamelen-1]='\0';
}

// void putinfile(vector <char*> historylist){
//   FILE *fp;
//   fp = fopen("history.txt","w+");
//   // while(!historylist.em)
//   // while(!historylist.empty()){
// 	// 	//cout<<" "<<Q.front();
//   //   fprintf(fp,"%s",historylist.front());
// 	// 	historylist.pop();
// 	// }
//   for(auto i=historylist.begin();i<historylist.end();i++){
//     fprintf(fp,"%s",historylist.front());
//   }
//   fclose(fp);
// }




struct Trie {
  struct Trie *children[128];
  int endNode;
};

struct Trie *getNode(){
  struct Trie *newNode = new Trie();
  for(int i=0;i<128;i++){
    newNode->children[i] = NULL;
  }
  newNode->endNode = 0;
  return newNode;
}

void insert (struct Trie *root, string s){
  int index;
  struct Trie *head = root;
  for(int i=0 ;s[i]!= '\0';i++){
      index = s[i] - ' ';
      if(index < 0){
        index = index + 65;
      }
      index = index + 32;
  //  cout<<"insertionn for string  = "<<s<<endl;

      if(head->children[index] == NULL){

        head->children[index] = getNode();
        // head->endNode = 0;
    //    cout<<"index is "<<index<<endl;
        head = head->children[index];
      }
      else{
        head = head->children[index];
      }
  }
  //cout<<"string entered="<<s<<endl;
  head->endNode = 1;
}

string search(struct Trie *root, string s){

  int index;
    struct Trie *head = root;
  //  cout<<"string buf = "<<s<<endl;
    for(int i = 0; s[i] != '\0';i++){
      index = s[i] - ' ';


      index = index + 32;
//cout<<"index after loop= "<<index<<endl;
      if(head->children[index] == NULL)
        return 0;
    //  if(head->children[index] == 1)
        head = head->children[index];
    }
    int count ;
    string word=s;
    char c;
    while(head->endNode != 1){
      count = 0;
      for(int i=0;i<128;i++){
        if(head ->children[i] != NULL){
          count++;
          if(count >= 2)
            return 0;
            c = i;
        word+=c;
        }

      }
      head = head ->children[(int)c];


    }
    //strcpy(words,word);
  //  res = word;
    cout<<word<<endl;

    if(head->endNode == 1)
      return word;
    else
      return NULL;

}
void printtrie(struct Trie *root){

int index;
  for(int i = 0 ;i<128;i++){
    struct Trie *head = root;
    index = i;
    if(head->children[index] == NULL){
      index = i;
      char s = index + ' ';
      cout<<s<<endl;
      head = head->children[index];
    }

  }

}





//struct Trie *root = getNode();

int checkforpipe(char *buf){

  int n=1;
  int i;
    char *res[BUFSIZE+1];
    for(i=0; buf[i] != '\0'; i++){
      if(buf[i] == '|')
        return 1;
    }
    return 0;
    res[0] = strtok(buf,"|");
    while((res[n] = strtok(NULL,"|")) != NULL)
      n++;

    if(res[1] == NULL)
    {
      //no pipe found
      return 0;
    }
    return 1;
}

int checkforredict(char *buf){

  int n=1;
  int i;

  for(int i =0 ; buf[i] != '\0' ;i++){
    if(buf[i] == '>' && buf[i+1] == '>')
      return 1;
    else if(buf[i] == '>')
      return 2;
  //  return 0;
  }

     return 0;


}

void parsePipe(char *buf){

  int fd[2];

  int fd_in = 0;
  int fd_out;
  int fd1;
  int pid;
  int n,k,l,i;
  int ret;
    int returnval;
    int count = 0;
  n = 1;
  k = 1;
  l = 1;
  char r1[BUFSIZE+1];
  char r2[BUFSIZE+1];
  char *res[BUFSIZE+1];
  char *temp1[BUFSIZE+1];
  char *temp2[BUFSIZE+1];
  res[0] = strtok(buf,"|");


  while((res[n] = strtok(NULL,"|")) != NULL)
    n++;
    count = 0;

    res[n]  = NULL;
  while (count < n)
    {
      pipe(fd);
      pid = fork();
      if (pid == -1)
        {
          exit(EXIT_FAILURE);
        }
      else if (pid == 0)
        {
        //  cout<<"count"<<count<<endl;
          dup2(fd_in, 0); //change the input according to the old one

          if (count+1 < n)
            dup2(fd[1], 1);

          close(fd[0]);
          strcpy(r1,res[count]);

                int check = checkforredict(res[count]);

              if(check == 1 || check == 2){
                //redirectionexists
        //         if(check == 1){
        //           //append
        //           fd1=open("opfile", O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
        //           dup2(fd1,1);
        //           temp1[0] = strtok(r1,">");
        //
        //         //  temp2[0] = strtok(r2,DELIM);
        //
        //           //push the rest of the text into the array till EOF
        //           while((temp1[k] = strtok(NULL,">")) != NULL)
        //             k++;
        //             temp1[k] = NULL;
        //
        //         }
        //         else if(check ==2){
        //           //overwrite
        //           fd1=open("opfile", O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
        //           dup2(fd1,1);
        //           temp1[0] = strtok(r1,">>");
        //
        //         //  temp2[0] = strtok(r2,DELIM);
        //
        //           //push the rest of the text into the array till EOF
        //           while((temp1[k] = strtok(NULL,">>")) != NULL)
        //             k++;
        //             temp1[k] = NULL;
        //         }
        //         if(fd1 < 0 ){
        //           printf("error while fileopening\n");
        //           exit(EXIT_FAILURE);
        //         }
        //       //  dup2(fd1,1);
        //
        //       for(int i=0;i<k;i++){
        //         temp2[i] = strtok(temp1[i],DELIM);
        //       }
        //       temp2[k] = NULL;
        //
        // execvp(temp2[0], &temp2[0]);
        //   exit(EXIT_FAILURE);
              }
              else{
                temp1[0] = strtok(r1,DELIM);

              //  temp2[0] = strtok(r2,DELIM);

                //push the rest of the text into the array till EOF
                while((temp1[k] = strtok(NULL,DELIM)) != NULL)
                  k++;
                  temp1[k] = NULL;
        execvp(temp1[0], &temp1[0]);

              }

        }
      else
        {
          //cout<<"parent"<<endl;
          waitpid(pid,&status,0);
          // close(fd[1]);
          fd_in = fd[0]; //save the input for the next command
            close(fd[1]);
          count++;
          // if(count == 1)
          //    close(fd[1]);
        }
    }


}

// void backspace(void)
// {
//
// 	char c;
// 	c = 8;
// 	write(1,&c,1);
// 	c = ' ';
// 	write(1,&c,1);
// 	c = 8;
// 	write(1,&c,1);
// }

void parsestring(char* buf){
  int i = 0, j = 0;
   while (buf[i])
   {
       if (buf[i] != ' ')
          buf[j++] = buf[i];
       i++;
   }
   buf[j] = '\0';
//   return str;
}


void printhistory()
{
  // while(!historylist.empty()){
	// 	cout<<" "<<historylist.front();
	// 	historylist.pop();
	// }
  for(auto i=hist.begin();i<hist.end();i++)
    cout<<*i<<endl;
}
void overwrite(char* buf){
  char *clargs[BUFSIZE+1];
  int n=1;
  char opfile[BUFSIZE];
  int fd1;
  //    for(int i=0;i<strlen(buf))
  printf("overwrite = %s\n",buf);
  for(int i = 0;i<strlen(buf);i++){
    if(buf[i] == '>')
      buf[i] = ' ';
  }

      clargs[0] = strtok(buf,DELIM);
      while((clargs[n] = strtok(NULL,DELIM))!= NULL)
        n++;
      clargs[n] = NULL;
      //cout<<"n= "<<n<<endl;
      parsestring(clargs[0]);
      parsestring(clargs[1]);
      strcpy(opfile,clargs[1]);
      clargs[1] =NULL;
      //cout<<"opfile = "<<opfile<<endl;
      fd1 = open(opfile,O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
      if(fd1==-1)
    {
      cout<<"UNABLE TO OPEN FILE FOR WRITING OUTPUT|n";
      exit(1);
    }

       dup2(fd1,1);
    //   clargs[1] = NULL;
      //cout<<clargs[0]<<endl;
      int pid = fork();
      if(pid == 0){
        if((execvp(clargs[0], &clargs[0])) < 0){
           cout<<"execution failed"<<endl;
             exit(200);
          //  return
        // }
        // else{
        //   return;
        // }
        close(fd1);
      }

    }
    else
      {
        waitpid(pid,&status,0);
        // close(fd[1]);
        // fd_in = fd[0]; //save the input for the next command
        //   close(fd[1]);
        // count++;
        // if(count == 1)
        //    close(fd[1]);
      }
  //  wait(NULL);
      // else{
      //   wait(NULL);
      //
      // }
}

void appending(char* buf){
  char *clargs[BUFSIZE+1];
  int flag=0;
  int n=1;
  char opfile[BUFSIZE];
  int fd1;
  //    for(int i=0;i<strlen(buf))
  for(int i = 0;i<strlen(buf);i++){
    if(buf[i] == '>' && buf[i+1]=='>'){
        buf[i] = ' ';
        flag=1;
        break;
        //buf[i+1] =' ';
    }
    if (flag == 1){
    //  int opfile;
    int m=0;
      for(int j=i+1;j<strlen(buf);j++){
        opfile[m++]=buf[j];
      }
    }

  }
  cout<<"opfile"<<opfile<<endl;

}

void media(char* buf,char* cmd){

  FILE *fp;
  char* clargs[BUFSIZE+1];
  char* temp[BUFSIZE+1];
  char buffer[BUFSIZE];
  char command[2*BUFSIZE];
  char tempcmd[2*BUFSIZE];
//  const char path[BUFSIZE];
  int n=1;
  printf("buf = %s\n",buf);
  printf("cmd = %s\n",cmd);

  const char path[] = "/home/ubuntu/Desktop/shell/unix programming/";
   clargs[0] = strtok(buf,".");
  //  printf("clargs[0=]%s",clargs[0]);
   while((clargs[n] = strtok(NULL,"."))!= NULL)
     n++;
     // printf("clargs[0]= %s\n",clargs[0]);
     // printf("clargs[1]= %s\n",clargs[1]);
  fp = fopen("media_list","r");
  if(fp == NULL){
    printf("NULL POINTER\n");
  }
  while(fgets(buffer, sizeof(buffer), fp)!=NULL){
    //fscanf(fp1, "%s",s);
  //  printf("entered here \n");
   fputs(buffer,fp);
   int n=1;

   temp[0] = strtok(buffer,":");
   while((temp[n] = strtok(NULL,":\n"))!= NULL)
     n++;



    if(strcmp(temp[0],clargs[1])==0){
      parsestring(temp[1]);
      printf("temp[0]= %s\n",temp[0]);
      printf("temp[1]= %s\n",temp[1]);
      strcpy(command,buf);
      strcat(command,".");
      strcat(command,temp[0]);
      printf("command = %s\n",command );
      strcpy(tempcmd,path);
      printf("tempcmd = %s\n",tempcmd );
      strcat(tempcmd,command);
      printf("temp path = %s\n",tempcmd );
//      path = "/usr/bin/xdg-open";



    string strp=(string)temp[1];
    cout<<"string: "<<strp<<endl;
    char *bine=(char*)strp.c_str();


     execl(bine, "xdg-open", tempcmd, (char*)0);
    cout<<"abc"<<endl;


    }


 }

}




int main(int argc, char **argv){

  int i,n;
  pid_t pid;
  //buffer for storing the entered commandline
  char buf[BUFSIZE+1];
  char histinput[BUFSIZE+1];
  char command[BUFSIZE+1];
  char args[BUFSIZE+1];
  //stores the argument strings
  char *clargs[ARGVSIZE+1];
  char *temp[ARGVSIZE+1];
  //+1 fornulll
  char olddir[BUFSIZE+1];
  char newdir[BUFSIZE+1];
 char opfile[10];
 string word;
  //used by sleep
  int returnval;
  int res,k;
  int flag;
  int check;
  int fd1=0;
  FILE *fp;
  DIR *d;
  struct dirent *dir;
  // int i=0;
  char s[1024];
  char ip[1024];
  string a;
  // int res;
  string lists[1024];
i=0;
setvariables();

FILE *filehist;
filehist = fopen("history.txt","w");
if(filehist == NULL)
{
  cout<<"error while opening"<<endl;
}
getcwd(curpath,sizeof(curpath));
//printf("%s\n", curpath);
d = opendir(curpath);
if(d){
  //directory succcessfully opened
  while((dir = readdir(d)) != NULL){
    lists[i++] = dir->d_name;
  }

  closedir(d);
}


//cout<<"count = "<<i<<endl;

  struct Trie *root = getNode();

for(int j= 0 ; j<i;j++){
  insert(root,lists[j]);
}


 //res = search(root,"pas");
enableRawInputMode();
//char predict[400];
//  struct Trie *root = getNode();
while(1){
  signal(SIGTSTP,tstphandler);
  if(signal(SIGTSTP,tstphandler) == 0)
      return 1 ;
    n = 1;


    //display prompt
  //  write(STDOUT_FILENO, "Shell> ",7);
  string prompt = printprompt();
  cout<<prompt;
    //getchar
    int i=0;
    int j=1;
    int k=1;
    char temp[1000];
    char c;

    while( (c = getchar()) != '\n' ){
      if(c == 26){
        return 0;
      }
      if (c == 18) {
        // cout<<"c = "<<c<<endl;
        // cout<<"buf = "<<buf<<endl;
        struct Trie *root = getNode();
        if(root == NULL)
          printf("hello it is null\n");

      for(int j=0;j < hist.size();j++){
      //  cout<<hist[j]<<endl;
        insert(root,hist[j]);
      }
      printf("\n" );
    //  printf("%s\n",buf );
      word = search(root,buf);
      memset(buf, 0, sizeof(BUFSIZE));
      char* t= (char*)word.c_str();
      strcpy(buf,t);

    //  printf("buf =%s",buf);
      continue;
    //  break;
  }
      signal(SIGTSTP,tstphandler);
      if(signal(SIGTSTP,tstphandler) == 0)
        return 1;
        if(c==127){
          printf("\r                                                                                                              ");
          buf[i-1] = '\0';
          i--;
          string prompt = printprompt();
        //  cout<<prompt;
        prompt = prompt+(string)buf;
          printf("\r%s",prompt.c_str());
          continue;
        }

         else if(c == 9){
         buf[i] = '\0';
         int n=1;
         clargs[0] = strtok(buf," ");
         while((clargs[n] = strtok(NULL," "))!= NULL)
           n++;
         clargs[n] = NULL;
         //cout<<clargs[n-1]<<endl;
         string halfcmd = clargs[n-1];

          word = search(root,halfcmd);

          j=0;

          int m=0;
          int lenofhalfcmd = strlen(clargs[n-1]);

          int l = i - lenofhalfcmd;
        //  cout<<"l = "<<buf[l]<<endl;
          strcpy(s, word.c_str());

          for(i=l;i<(l+strlen(s));i++){
            buf[i] = s[m++];
      //      cout<<buf[i]<<" "<<s[m]<<endl;
          }
          cout<<endl;
          int z;
          for( z = l;z<i;z++){
            cout<<buf[z];
          }
          buf[z]='\0';

          for(int i=0;i<z;i++){
            if(buf[i] == '\0')
              buf[i] = ' ';
          }
          //cout<<"%s"<<buf<<endl;
           //break;
        }
        else{
              buf[i] = c;
              i++;
        }
    }
// cout<<"buffer = "<<buf<<endl;

strcpy(histinput,buf);

hist.push_back(histinput);
//putinfile(hist);


//-------------------pipe starts and ends here -------
        //checkforpipe
        if(checkforpipe(buf) == 1){
          //pipe present
          //act accordingly
          parsePipe(buf);
      //    return 0;
        }
//-------------pipe ends here ---------
        else if (checkforredict(buf) > 0){
          //redirectionexists
          // histinput = buf
          check  = checkforredict(buf);
          printf("check value = %d\n", check);

          if(check == 2){
            //overwrite
            printf("buf = %s\n",buf);
            int pid = fork();
            if(pid == 0){
              overwrite(buf);
            printf("out\n");
            continue;
          }
          else
            {
              waitpid(pid,&status,0);
              // close(fd[1]);
              // fd_in = fd[0]; //save the input for the next command
              //   close(fd[1]);
              // count++;
              // if(count == 1)
              //    close(fd[1]);
            }
          }
          else if(check == 1){
            //appending
            int pid = fork();
            if(pid == 0){
              appending(buf);
            printf("out\n");
            }
            else
              {
                waitpid(pid,&status,0);
                // close(fd[1]);
                // fd_in = fd[0]; //save the input for the next command
                //   close(fd[1]);
                // count++;
                // if(count == 1)
                //    close(fd[1]);
              }

          }
        //  else{}
      }

else{


clargs[0] = strtok(buf,DELIM);

//push the rest of the text into the array till EOF
while((clargs[n] = strtok(NULL,DELIM)) != NULL)
  n++;

clargs[n] = NULL;

if(strcmp(clargs[0],"exit")==0)
{
//  putinfile(hist);
  cout<<"bye"<<endl;
  return 0;
}

int pid = fork();
switch(pid){
  case 0:

      //struct Trie *root;
    if(strcmp(clargs[0],"cd") == 0){
      //printf("%s\n", );

      char *directory = clargs[1];
    //  printf("pwd =%s\n",clargs[1] );

    //  chdir (directory);
      getcwd(curpath,sizeof(curpath));
      if(clargs[1] == NULL || (strcmp(clargs[1],"~")==0)){
        clargs[1] = HOME;
        //strcpy(curpath,HOME);
      }
      //printf("%s\n", curpath);
    res =   chdir(clargs[1]);
    if(res == 0){


      getcwd(curpath,sizeof(curpath));

      i=0;
       d = opendir(curpath);
      if(d){
        //directory succcessfully opened
        while((dir = readdir(d)) != NULL){
          lists[i++] = dir->d_name;
        }

        closedir(d);
      }
    //  cout<<"count = "<<i<<endl;
        if(root == NULL)
          printf("hello it is null\n");
        struct Trie *root1 = getNode();
        if(root1 == NULL)
          printf("hello it is null\n");

      for(int j= 0 ; j<i;j++){
        insert(root1,lists[j]);
      }

      root = root1;
    }else
       printf("command unsuccessful\n" );
    }
    else if(strcmp(clargs[0],"look")==0){
      string a;
  		cin >> a;
  		word = search(root,a);
    }
    else if(strcmp(clargs[0],"exit") == 0)
        exit(0);
    else if(strcmp(clargs[0],"echo") == 0)
      {
        strcpy(command,clargs[0]);
        strcpy(args,clargs[1]);
      //  callecho(command,args);
        parsestring(args);
        if(strcmp(args,"$$") == 0){
          pid = getpid();
            cout<<pid<<endl;
            // strcpy(histinput,buf);
            // hist.push_back(histinput);
        }
        else if(strcmp(args,"$?") == 0){
          if ( WIFEXITED(status) )
          {
        int exit_status = WEXITSTATUS(status);
        printf("Exit status of the child was %d\n",
                                     exit_status);
          }
      //    cout<<returnval<<endl;
          // strcpy(histinput,buf);
          // hist.push_back(histinput);
        }
        else if(strcmp(args,"$PATH")==0){
          FILE *fppath;
          char buffer[BUFSIZE+1];
            char *temp1[BUFSIZE+1];
          fppath = fopen("bashrc.txt","r");
          while(fgets(buffer, sizeof(buffer), fppath)!=NULL){
            //fscanf(fp1, "%s",s);
           fputs(buffer,fppath);


          int n=1;

          temp1[0] = strtok(buffer,"=");

          while((temp1[n] = strtok(NULL,"="))!= NULL)
            n++;

          if(strcmp(temp1[0],"PATH")==0){
            //HOME = clargs[1];
          //  strcpy(HOME,clargs[1]);
          printf("%s",temp1[1]);
            //printf("home = %s\n",HOME);
          }

          }
          fclose(fppath);

        }
      else if(strcmp(args,"$HOME")==0){
        printf("%s\n",HOME );
      }
      else if(strcmp(args,"$USER")==0){
        printf("%s\n",USER );
      }
      else if(strcmp(args,"$HOSTNAME")==0){
        printf("%s\n",HOSTNAME );
      }
      else if(strcmp(args,"$PS1")==0){
        printf("%c\n",PS1);
      }
      else{
        flag=0;

          char arr[BUFSIZE+1];
          strcpy(arr,args);
          //printf("arr= %s\n",arr );
          if(arr[0] == '$'){
            //printf("entered in $\n");
            for(int i=0;i<strlen(arr);i++){
              arr[i]= arr[i+1];
            }
            arr[i]='\0';
            fp = fopen("bashrc.txt","r");
            while(fgets(s,sizeof(s),fp) != NULL){
            //  printf("enteed in file\n" );
            fputs(s,fp);
             int n=1;

              clargs[0] = strtok(s,"=");
            //  printf("clargs[0=]%s",clargs[0]);
              while((clargs[n] = strtok(NULL,"="))!= NULL)
                n++;
                if(strcmp(arr,clargs[0])==0){

            //      printf("enteed\n");
                  printf("%s\n",clargs[1]);
                }
                flag=1;
            }

          }
          //printf("arr= %s\n",arr );
                  // else{
          if(flag == 0)
              printf("%s\n",args);
          //}
          fclose(fp);
        //  else printf("%s\n",args);
          // strcpy(histinput,buf);
          // hist.push_back(histinput);
        }


      }
      else if(strcmp(clargs[0],"export")==0){
        //export variable there

        char arr[BUFSIZE+1];
        strcpy(arr,clargs[1]);
        if(arr[0] == '$'){
          for(int i=0;i<strlen(arr);i++){
            arr[i]= arr[i+1];
          }
          arr[i]='\0';
        }
      //  printf("export = %s",arr);
      fp = fopen("bashrc.txt","a+");
      fputs(arr, fp );
      fclose(fp);


      }
      else if(strcmp(clargs[0],"history") == 0){
        //hist.push_back(clargs[0]);
        // fclose(filehist);
        printhistory();
        // filehist = fopen("history.txt","w+");
      }
      else if(strcmp(clargs[0],"open")==0){
        printf("entered open\n" );
        media(clargs[1],buf);
      }
    else {
      if((execvp(clargs[0], &clargs[0])) < 0)
      exit(200);

  }
    //break;
  default:
      waitpid(pid,&status,0);

        memset(clargs, 0, 1024);

      for(i =0 ;i<BUFSIZE ;i++)
        buf[i] = '\0';
      }

}        //ls gets over



  }
  fclose(filehist);
  return 0;

}
