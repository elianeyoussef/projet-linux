#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char**argv)
 {
  

 int listenfd,connfd,n;
 struct sockaddr_in servaddr,cliaddr;
 socklen_t clilen;
 pid_t     childpid;
 char mesg[1000];


 listenfd=socket(AF_INET,SOCK_STREAM,0);

 bzero(&servaddr,sizeof(servaddr));
  
 servaddr.sin_family = AF_INET;
 servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
 servaddr.sin_port=htons(32000);
  
 bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

 listen(listenfd,1024);


 for(;;) {
    
  clilen=sizeof(cliaddr);
  connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);
   
  if ((childpid = fork()) == 0) {
     
    close (listenfd);
    
   for(;;) {
 
     n = recvfrom(connfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&clilen);
     sendto(connfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
     printf("-------------------------------------------------------\n");
     mesg[n] = 0;
     printf("Received the following:\n");
     printf("%s",mesg);
     printf("-------------------------------------------------------\n");
	
     if(strcmp(mesg,"_who") == 0)	{

       printf("IP address is: %s\n", inet_ntoa(cliaddr.sin_addr));
	
	
       }
         
    }
         
    
  }
  
    
 close(connfd);
 

  }

}

