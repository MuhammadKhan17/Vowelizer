/*
so the plan will be to use the vector method for envoweling

*/
#include <string>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
using namespace std;
vector<string> getInp();
void sendViaUDP(char* inp);
void sendViaTCP(int clientTCP,char* msg);
void setupTCP(int* clientTCP,struct sockaddr_in* tStruct);
int main(){
    //tcp client
    int clientTCP;
    char tBuffer[1024];
    struct sockaddr_in tStruct;
    setupTCP(&clientTCP,&tStruct);
    
    //recieve client
    int rec;
    char rBuffer[1024];

    
    if( connect(clientTCP,(struct sockaddr*)&tStruct, sizeof(struct sockaddr_in))<0){
        perror("failed to connect");
        exit(EXIT_FAILURE);
    }

    while(1){

        char msg[1024];
        char msg2[1024];
        cout<<"woud you like to envowel(1) or devowel(2)?\n(enter option 1 or 2): ";
        cin.getline(msg,1024,'\n');
        sendViaTCP(clientTCP,msg);
        cout<<"would you lie the basic version(1), the advanced version(2) or the super advanced(3)?\n(enter option 1, 2 or 3): ";
        cin.getline(msg2,1024,'\n');
        sendViaTCP(clientTCP,msg2);
        if(msg[0]=='2'&& (msg2[0]=='1'||msg2[0]=='2'||msg2[0]=='3')){
            cout<<"please enter a string you would like encoded: ";
            cin.getline(msg,1024,'\n');
            sendViaTCP(clientTCP,msg);
            cout<<"the vowels are: "<<endl;
            char inp[1024];
            strcpy(inp,"i want my vowels");
            sendViaUDP(inp);
            strcpy(inp,"i want my nonVowels");
            cout<<"the nonvowels are:"<<endl;
            sendViaTCP(clientTCP,inp);

        }else if(msg[0]=='1'&& (msg2[0]=='1'||msg2[0]=='2'||msg2[0]=='3')){
            cout<<"please enter the nonvowels: ";
            char inp[1024];
            cin.getline(inp,1024,'\n');
            sendViaTCP(clientTCP,inp);
            cout<<"please enter the vowels: ";
            cin.getline(inp,1024,'\n');
            sendViaUDP(inp);
            strcpy(inp,"i want my decoded string");
            cout<<"the combinded string is: "<<endl;
            sendViaTCP(clientTCP,inp);
        }
        
    }
    return 0;
}
void setupTCP(int* clientTCP,struct sockaddr_in* tStruct){
    *clientTCP=socket(AF_INET, SOCK_STREAM, 0);
	if (*clientTCP == -1)
	{
		printf("Could not create socket\n");
	}
    memset(tStruct,0,sizeof(struct sockaddr_in));
	(*tStruct).sin_family = AF_INET;
	(*tStruct).sin_addr.s_addr = inet_addr("136.159.5.27");
	(*tStruct).sin_port = htons(11124);
}
void sendViaTCP(int clientTCP,char* msg){
    char a[1024]={0};
    stpcpy(a,msg);
    if(send(clientTCP,a,1024,0)<0){
        perror("error in sending");
    }
    if(recv(clientTCP,a,1024,0)<0){
        perror("error in recieving from server: ");
    }
    cout<<a<<endl;
    
}
void sendViaUDP(char* inp){
    //UDP client
    ssize_t clientUDP;
    char uBuffer[1024];
    struct sockaddr_in uStruct;

     socklen_t reL=sizeof(uStruct);
    clientUDP = socket(AF_INET, SOCK_DGRAM, 0);
    if( clientUDP < 0 ){
        perror("socket creation failed");
		exit(EXIT_FAILURE);
    }

    memset(&uStruct, 0, sizeof(uStruct));
    uStruct.sin_family = AF_INET;
	uStruct.sin_port = htons(8085);
	inet_pton(AF_INET,"136.159.5.27",&uStruct.sin_addr);
    

    char buff2[1024] = {0};
    stpcpy(buff2,inp);
	if(sendto(clientUDP, buff2, 1024, 0, (struct sockaddr* )&uStruct, sizeof(struct sockaddr_in))<0)
        perror("sending the udp message");
	if(recvfrom(clientUDP,buff2,1024,MSG_WAITALL,NULL,NULL)<0)
        perror("failed to recive");		
    printf("%s\n", buff2);
}


vector<string> getInp(){
    vector<string> cmd;
    cout<<"please enter the nonvowels: ";
    cmd.push_back("");
    getline(cin,cmd.at(0));

    cout<<"please enter the vowels: ";
    cmd.push_back("");
    getline(cin,cmd.at(1));
    
    return cmd;

}
