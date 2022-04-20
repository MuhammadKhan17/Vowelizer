#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
using namespace std;
#define PORT	 8085

//methods for envoweling
string envowel1(string str1, string str2);
string envowel2(string str1,string str2);
string envowel3(string str1,string str2);
//methods for devoweling
string dVowel(string inp,int flag);
string dVowel2(string inp,int flag);
string dVowel3(string og, int flag);
//getting messages from the client
string getUDP(ssize_t sockUDP);
string getTCP(int sockTCP);
//sending messages to the server
void sendTCP(int sockTCP,char* inp);
void sendUDP(ssize_t sockUDP,char* inp);
//creating the initial sockets and socket adder structures
void listenTCP(int* TCPlisten,struct sockaddr_in* connectTCP);
void udpsetUp(struct sockaddr_in* connectUDP,ssize_t* sockUDP);


int main(){
    //fork for multiple clients
    pid_t pid;
    //UDP
    
    //creating the udp scoket
    ssize_t sockUDP;
    struct sockaddr_in connectUDP;
    //initializing and binding with the method
    udpsetUp(&connectUDP,&sockUDP);

    //TCP
    //to establish connection
    int TCPlisten;
    struct sockaddr_in connectTCP;
    //initializing and binding with the method
    listenTCP(&TCPlisten,&connectTCP);

    //the main TCP socket for communication after connection
    int sockTCP;
    struct sockaddr_in recvTCP;
    //length of the structure
    socklen_t stuLen=sizeof(struct sockaddr_in);

    //litsening for client
    listen(TCPlisten, 5);
    cout<<"listening"<<endl;
    if(TCPlisten<0){
            perror("failed to accpet");
    }
    //accpeting the connection, initialising main socket for communication and starting the loop
    while((sockTCP=accept(TCPlisten,(struct sockaddr*)&recvTCP,&stuLen))>0){
    //just indicating that the connection was accpeted, also confirms successful inputs
        cout<<"success"<<endl;
        //creating the fork to handel multiple processes
        pid=fork();
        if(pid<0){
            perror("fork failed ");
            exit(1);
        }
        //child process
        if(pid==0){
            //for my error checking
            cout<<"entered the child process"<<endl;
            
            while(1){
                //to store the options (option1 is encvowel or devowel)(option 2 is to do basic or advanced)
                char option[1024];
                char option2[1024];
                //asking client for option1
                if(recv(sockTCP, option, 1024, 0)<0)
                    perror("error in recieving");
                //sending confirmation   
                if(send(sockTCP,"option sent",1024,0)<0)
                    perror("error in sending confirmation of option: "); 
                cout<<"the 1st option selected was: "<<option<<endl;
                //asking client for option2
                if(recv(sockTCP, option2, 1024, 0)<0)
                    perror("error in recieving");
                cout<<"the 2nd option selected was: "<<option2<<endl;
                //sending confirmation   
                if(send(sockTCP,"option 2 sent",1024,0)<0)
                    perror("error in sending confirmation of option: "); 

                //devowel and basic
                if(option[0]=='2'&&option2[0]=='1'){
                    //getting the string to be seperated via TCP
                    string msg=getTCP(sockTCP);
                    //devoweling and getting the vowels
                    string vowels=dVowel(msg,0);
                    //devoweling and getting the nonvowels
                    string nonVowels=dVowel(msg,1);
                    cout<<"the vowels are: "<<vowels<<endl;
                    cout<<"the nonvowels are: "<<nonVowels<<endl;
                    //sending vowels via UDP
                    sendUDP(sockUDP,(char*)vowels.c_str());
                    //sending nonvowels via TCP
                    sendTCP(sockTCP,(char*)nonVowels.c_str());
                
                //devowel and advanced
                }else if(option[0]=='2'&&option2[0]=='2'){
                    //geting the string to be seperated via TCP
                    string msg=getTCP(sockTCP);
                    //devoweling and getting the vowels
                    string vowels=dVowel2(msg,0);
                    //devoweling and getting the nonvowels
                    string nonVowels=dVowel2(msg,1);
                    cout<<"the vowels are: "<<vowels<<endl;
                    cout<<"the nonvowels are: "<<nonVowels<<endl;
                    //sending vowels via UDP
                    sendUDP(sockUDP,(char*)vowels.c_str());
                    //sending nonvowels via TCP
                    sendTCP(sockTCP,(char*)nonVowels.c_str());
                //envowel and basic
                }else if(option[0]=='1'&&option2[0]=='1'){
                    //getting the nonVowels over TCP
                    string nonVowels=getTCP(sockTCP);
                    //getting the vowels over UDP
                    string vowels=getUDP(sockUDP);
                    //combining
                    string msg=envowel1(nonVowels,vowels);
                    cout<<"the combined string is: "<<msg<<endl;
                    //sending combinded string over TCP
                    sendTCP(sockTCP,(char*)msg.c_str());
                //envowel and advanced
                }else if(option[0]=='1'&&option2[0]=='2'){
                    //getting the nonvowels over TCP
                    string nonVowels=getTCP(sockTCP);
                    //getting the vowels over UDP
                    string vowels=getUDP(sockUDP);
                    //combining
                    string msg=envowel2(nonVowels,vowels);
                    //sending combinded string over TCP
                    sendTCP(sockTCP,(char*)msg.c_str());
                //envowel but super advanced
                }else if(option[0]=='1'&&option2[0]=='3'){
                    //getting the nonvowels over TCP
                    string nonVowels=getTCP(sockTCP);
                    //getting the vowels over UDP
                    string vowels=getUDP(sockUDP);
                    //combining
                    string msg=envowel3(nonVowels,vowels);
                    //sending combinded string over TCP
                    sendTCP(sockTCP,(char*)msg.c_str());
                //devowel and super advanced
                }else if(option[0]=='2'&&option2[0]=='3'){
                     //geting the string to be seperated via TCP
                    string msg=getTCP(sockTCP);
                    //devoweling and getting the vowels
                    string vowels=dVowel3(msg,0);
                    //devoweling and getting the nonvowels
                    string nonVowels=dVowel3(msg,1);
                    cout<<"the vowels are: "<<vowels<<endl;
                    cout<<"the nonvowels are: "<<nonVowels<<endl;
                    //sending vowels via UDP
                    sendUDP(sockUDP,(char*)vowels.c_str());
                    //sending nonvowels via TCP
                    sendTCP(sockTCP,(char*)nonVowels.c_str());
                }

            }
            //making sure we dont get forked bombed
            close(sockTCP);
            exit(0);

        //parent process
        }else{
            //for my error checking
            cout<<"entered the parent process"<<endl;
            //closing unneeded socket
            close(sockTCP);
        }
    }
    
    return 0;
}

//setting up the litsening socket
void listenTCP(int* TCPlisten,struct sockaddr_in* connectTCP){
    //creating socket
    *TCPlisten=socket(AF_INET,SOCK_STREAM,0);
    if(*TCPlisten<0)
        perror("failed to create tcp socket");
    
    //creating the socket adder structure
    memset(connectTCP,0,sizeof(struct sockaddr_in));
	(*connectTCP).sin_family = AF_INET;
	(*connectTCP).sin_addr.s_addr = INADDR_ANY;
	(*connectTCP).sin_port = htons(11124);

    //binding the structure and the socket
    if(bind(*TCPlisten,(struct sockaddr*) connectTCP, sizeof(struct sockaddr_in))<0)
        perror("error in binding the tcp");
}

//setup the udp socket
void udpsetUp(struct sockaddr_in* connectUDP, ssize_t* sockUDP){
    //initializing the socket
    *sockUDP=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(*sockUDP<0)
        perror("udp socket failed");
    //creating the socket adder structure
    memset(connectUDP,0,sizeof(struct sockaddr_in));
	(*connectUDP).sin_family = AF_INET;
	(*connectUDP).sin_port = htons(PORT);
	(*connectUDP).sin_addr.s_addr = INADDR_ANY;
    //binding the socket
    if( bind(*sockUDP,(struct sockaddr*) connectUDP, sizeof(struct sockaddr_in))<0)
        perror("udp bind failed");
}

//send a message to the client via UDP
void sendUDP(ssize_t sockUDP,char* inp){
    //creating structure to send to client
    struct sockaddr_in client;
	memset(&client, 0, sizeof(struct sockaddr_in));
	socklen_t len = sizeof(client);
    
    //storing the message from the client
    char msg[1024];
    //recieving the message		
	if(recvfrom(sockUDP,msg,1024,MSG_WAITALL,(struct sockaddr*)&client,&len)<0)
        perror("error in reciving");
    cout<<"the message was: "<<msg<<endl;
    
    //sending inp to client
	strcpy(msg, inp);
	if(sendto(sockUDP, msg, 1024, 0, (struct sockaddr* ) &client, len)<0)
        perror("error in sending to client");  
}

//get a message from the client via UDP
string getUDP(ssize_t sockUDP){
    //creating structure to send to client
    struct sockaddr_in client;
	memset(&client, 0, sizeof(struct sockaddr_in));
	socklen_t len = sizeof(client);
    
    //storing the message frin the client
    char buff[1024];	
    //recieving the message
	if(recvfrom(sockUDP,buff,1024,MSG_WAITALL,(struct sockaddr*)&client,&len)<0)
        perror("error in reciving");
    //putting the message in a string to be used later
    string msg=buff;
    cout<<"the message sent over UDP was: "<<msg<<endl;
    //sending confiramtion to client
	strcpy(buff, "message sent");
	sendto(sockUDP, buff, 1024, 0, (struct sockaddr* ) &client, len);
    return msg;
}

//to get information from client via TCP
string getTCP(int sockTCP){
    //variable to store the input
    char input[1024];
    //getting the input
    if(recv(sockTCP, input, 1024, 0)<0)
        perror("error in recieving");
    cout<<"the message sent over TCP was: "<<input<<endl;
    //sending confirmation   
    if(send(sockTCP,"message sent",1024,0)<0)
        perror("error in sending confirmation of option: ");
    //returning input to main
    return input; 
}

//to send infromation to client via TCP
void sendTCP(int sockTCP,char* inp){
    //variable to store and send information
    char input[1024];
    //recieving input
    if(recv(sockTCP, input, 1024, 0)<0)
        perror("error in recieving");
    cout<<"the message sent over TCP was: "<<input<<endl; 
    //sending information to client
    strcpy(input,inp); 
    if(send(sockTCP,input,1024,0)<0)
        perror("error in sending confirmation of option: ");

}

//basic envoweling
string envowel1(string str1, string str2){
    //string of the combined phrase
    string comb="";
    //equating the nonvowels to combined string
    comb+=str1;
    
    for(int i=0;i<str2.length();i++){
        //replacing any space with the proper vowel
        if(str1.at(i)==' ' && str2.at(i)!=' '){
            comb.at(i)=str2.at(i);   
        }
    }
    //returning the combined string
    return comb;
    //note: can probably work with vowels and novowals switched
}

//advanced envoweling
string envowel2(string str1,string str2){
    //creating string to store answer
    string ans="";

    for(int i=0;i<str2.length();i++){
        //getting a number
        if(i%2==0){
            //adding that many spaces
            for(int z=0;z<str2.at(i)-48;z++)
                ans+=" ";
        }else{
            //adding vowel if no number is found
            ans+=str2.at(i);
        }
    }
    //now ans has all the vowels and spaces for the nonvowels but no spaces after the last vowel
    int z=0;
    for(int i=0;i<ans.length();i++){
        //adds in all the nonvowels until the last vowel
        if(ans.at(i)==' '){
            ans.at(i)=str1.at(z);
            z++;
        }
    }
    //adds the last remaining nonvowels
    while(z<str1.length()){
        ans+=str1.at(z);
        z++;
    }
    //returns the combined string
    return ans;
}

//devoweling a string, flag is to determine if you want vowels or nonvowels
string dVowel(string inp,int flag){
    //strings for answers
    string wAns="";
    string nAns="";
    string og=inp;
    for(int i=0;i<og.length();i++){
        //if its a vowel, it is added to wAns
        if(og.at(i)=='a'||og.at(i)=='A'||og.at(i)=='e'||og.at(i)=='E'||og.at(i)=='i'||og.at(i)=='I'||og.at(i)=='o'||og.at(i)=='O'||og.at(i)=='u'||og.at(i)=='U'){
            wAns+=og.at(i);
            nAns+=" ";
        //if its a space it is added to both strings
        }else if(og.at(i)==' '){
            nAns+=" ";
            wAns+=" ";
        //if it is a nonvowel it is added to nAns
        }else{
            nAns+=og.at(i);
            wAns+=" ";
        }
    }
    //if the flag is 1 then we return the nonvowels. anything else is a vowel
    if(flag==1)
        return nAns;
    else
        return wAns;
    
}

//advanced devoweling
string dVowel2(string inp,int flag){
    //strings for answers
    string wAns="";
    string nAns="";
    //counter to store the characters before a vowel
    int counter=0;
    string og=inp;
    for(int i=0;i<og.length();i++){
        //if it is a vowl we first add the counter value (number of characters before) and then the vowel
        if(og.at(i)=='a'||og.at(i)=='A'||og.at(i)=='e'||og.at(i)=='E'||og.at(i)=='i'||og.at(i)=='I'||og.at(i)=='o'||og.at(i)=='O'||og.at(i)=='u'||og.at(i)=='U'){
            //add the counter
            wAns+=to_string(counter);
            //reset the counter
            counter=0;
            //add the vowel
            wAns+=og.at(i);
        }else{
            //adds the character to the nonvowel string
            nAns+=og.at(i);
            //adds to the counter to
            counter++;
        }
    }
    
    //if the flag is 1 then we return the nonvowels. anything else is a vowel
    if(flag==1)
        return nAns;
    else
        return wAns;
    
}


//BONUS CONTENT

//super advanced envoweling
string envowel3(string str1,string str2){
    //string for combining the variables
    string comb="";
    //counter for the z index
    int z=0;
    for(int i=0;i<str1.length();i++){
        //adding ~ to all the spots with vowels
        if(str1.at(i)=='~'){
            comb+=str2.at(z);
            //increasing the index for vowels
            z++;
        }
        //adding all characters between ' ' and ':'
        else if(str1.at(i)>'d'){
            //essentially moving a character from the reange of(100,126) to (32,58)
            comb+=(char)(str1.at(i)-'d'+' ');
        }else{
            //adding 26 to bring back the orignal letter
            comb+=(char)(str1.at(i)+26);
        }
    }
    //returning the combined string
    return comb;

}
//super advanced devoweling
string dVowel3(string og, int flag){
    //strings to be returned wAns is vowels and nAns is nonvowels
    string nAns="";
    string wAns="";
    for(int i=0;i<og.length();i++){
        //if a vowel is found
        if(og.at(i)=='a'||og.at(i)=='A'||og.at(i)=='e'||og.at(i)=='E'||og.at(i)=='i'
        ||og.at(i)=='I'||og.at(i)=='o'||og.at(i)=='O'
        ||og.at(i)=='u'||og.at(i)=='U'){
            //add ~ for every vowel in the nonvwoel
            nAns+='~';
            //add vowel to the vowel string
            wAns+=og.at(i);
        //moves all characters that are greater than 58 down 26 places
        }else if(og.at(i)>=':'){
            nAns+=(char)(og.at(i)-26);
        //all other characters are moved to range (100,126)
        }else{
             nAns+=(char)(og.at(i)+'d'-' ');
        }
    }
    //if 1 this method will return nonvowels and will return vowels in all other cases 
    if(flag==1)
        return nAns;
    else
        return wAns;

}