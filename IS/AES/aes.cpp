#include<bits/stdc++.h>
#include "constants.h"
using namespace std;
const int N=1024;
string message;
string keyString;
char key[16];

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

void expandKey(char expandedKey[]){
    	for (int i = 0; i < 16; i++) {
		expandedKey[i] = key[i];
	}

	int bytesGenerated = 16; 
	int rconIteration = 1; 
	unsigned char tmpCore[4]; 

	while (bytesGenerated < 176) {
		
		for (int i = 0; i < 4; i++) {
			tmpCore[i] = expandedKey[i + bytesGenerated - 4];
		}

		// Perform the core once for each 16 byte key
		if (bytesGenerated % 16 == 0) {
			KeyExpansionCore(tmpCore, rconIteration++);
		}

		for (unsigned char a = 0; a < 4; a++) {
			expandedKey[bytesGenerated] = expandedKey[bytesGenerated - 16] ^ tmpCore[a];//4 ghor ager tar sathe xor 1 ghor ager ta xor
			bytesGenerated++;
		}

	}
}



string encryption(string message, int index, char expandedKey[]){
    char state[16];
    int j = index;
    for(int i=0;i<16;i++){
        state[i]=message[j++];//copying first 16 blocks into state
    }
    // for(int i=0; i<16; ++i)
    //     cout << hex << state[i];

    int nR=10;//number of rounds
    char roundKey[16];
    addRoundKey(state, expandedKey);//initial addroundkey
    for(int i=0;i<nR-1;i++){
            subBytes(state);
            shiftRows(state);
            mixColumn(state);
            getRoundKey(roundKey,expandedKey,i);
            addRoundKey(state,roundKey);
    }
    subBytes(state);
	shiftRows(state);
    getRoundKey(roundKey,expandedKey,9);
	addRoundKey(state, key);
    
    string encStream;

    for(int i=0;i<16;i++){
        encStream+=state[i];
    }
    return encStream;

}

int main(){
    printf("Enter message: ");
    getline(cin,message);
    padMessage();
    printf("Enter the 128 bit key: ");
    getline(cin,keyString);
    convertToHex();
    /*for(int i=0; i<16; ++i)
        cout << hex << (int)key[i];*/
    //input done
   
    char expandedKey[176];
    expandKey(expandedKey);
//    for(int i=0; i<176; ++i)
//         cout << hex << (int)expandedKey[i];
    string encryptedMessage;
    for(int i=0;i<message.length();i+=16){//16 kore kore nibo
        encryptedMessage += encryption(message, i, expandedKey);
    }
    printf("Encrypted message: ");

    cout<<encryptedMessage<<endl;
}

