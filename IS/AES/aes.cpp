#include<bits/stdc++.h>
#include "constants.h"
using namespace std;
const int N=1024;
string message;
string keyString;
unsigned char key[16];
unsigned char state[16];
void padMessage(){
    int len=message.size();
    int newLen=len;
    //padding to make divisible by 4
    if(len%16!=0){
        newLen=(len/16 + 1)*16;
    }

    for(int i=0;i<newLen;i++){
        if(i<len){
            message[i]=message[i];
        }
        else{
            message.append("0");
        }
    }
}
void convertToHex(){
     for(int i=0;i<16;i++){
        if(i<keyString.length()){
            key[i]=(int)keyString[i];
        }
        else{
            key[i]=0;
        }
    }
}

void expandKey(unsigned char expandedKey[]){
    for (int i = 0; i < 16; i++) {
		expandedKey[i] = key[i];
	}

	int bytesGenerated = 16; //done so far
	unsigned char tmpCore[4]; 

	while (bytesGenerated < 176) {
		
		for (int i = 0; i < 4; i++) {
			tmpCore[i] = expandedKey[i - 4 + bytesGenerated];//prothom 4 ta temporary save
		}
        //cout<<bytesGenerated<<endl;
		// Perform the core once for each 16 byte key
		if (bytesGenerated % 16 == 0) {
			KeyExpansionCore(tmpCore, (bytesGenerated/16)-1);
            //cout<<"Roundkey number:  "<<(bytesGenerated/16)-1<<endl;
		}

		for (int a = 0; a < 4; a++) {
			expandedKey[bytesGenerated+a] = tmpCore[a]^expandedKey[bytesGenerated - 16+ a] ;//4 ghor ager tar sathe xor 1 ghor ager ta xor
		}
        bytesGenerated+=4;

	}
}


void encryption(string message, int index, unsigned char expandedKey[]){
    
    int j = index;
    for(int i=0;i<16;i++){
        state[i]=message[j++];//copying first 16 blocks into state
    }
   

    int nR=10;//number of rounds
    unsigned char roundKey[16];
    addRoundKey(state, expandedKey);//initial addroundkey
    for(int i=0;i<9;i++){
            subBytes(state);
            shiftRows(state);
            mixColumn(state);
            getRoundKey(roundKey,expandedKey,i);
            addRoundKey(state,roundKey); 
    }
    subBytes(state);
	shiftRows(state);
    getRoundKey(roundKey,expandedKey,9);
	addRoundKey(state, roundKey);
}

int main(){
    printf("Enter message: ");
    getline(cin,message);
    padMessage();
    printf("Message in hex:\n");
    for (int i = 0; i < message.length(); i++) {
		cout << hex << (int) message[i];
		cout << " ";
	}
    cout<<endl;
    printf("Enter the 128 bit key: ");
    getline(cin,keyString);
    convertToHex();
    printf("Key string in hex:\n");
    for (int i = 0; i < keyString.length(); i++) {
		cout << hex << (int) keyString[i];
		cout << " ";
	}
    cout<<endl;
    /*for(int i=0; i<16; ++i)
        cout << hex << (int)key[i];*/
    //input done
   
    unsigned char expandedKey[176];
    expandKey(expandedKey);
//     printf("Expanded key:\n");
//    for(int i=0; i<176; ++i)
//         cout << hex << (int)expandedKey[i];
//     cout<<endl;
    printf("Encrypted message: ");
    for(int i=0;i<message.length();i+=16){
        encryption(message, i, expandedKey);
        for (int j = 0; j < 16; j++) {
		    cout << hex << (int) state[j];
		    cout << " ";
	    }
    }
}

