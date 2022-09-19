#include<bits/stdc++.h>
using namespace std;
#define BLOCK_SIZE 1024
string input;
int bufferSize;
void takeInput(){
    getline(cin,input);
}
void appendLength(int length, uint64_t hi, uint64_t lo){
    lo=length;
    hi=0x00ULL;
}
uint64_t** padding(unsigned char *input){
    int len=strlen((const char*) input);
    int l=len<<3;
    int k=(896-1-l) % BLOCK_SIZE;
    bufferSize= (l+1+k+128) / BLOCK_SIZE;

    //initialize input buffer
    uint64_t** buffer = new uint64_t*[bufferSize];//total n

	for(int i=0; i<bufferSize; i++){
		buffer[i] = new uint64_t[16]; //64 bits er 16 ta array lagbe
	}
    uint64_t in;
	int index;

    // Either copy existing message, add 1 bit or add 0 bit
	for(int i=0; i<bufferSize; i++){
		for(int j=0; j<8; j++){
			in = 0x0ULL;
			for(int k=0; k<8; k++){
				index = i*128+j*8+k;
				if(index < len){
					in = (uint64_t)input[index];//if less than len take from input
				}else if(index == len){
					in = 0x80ULL; //if equal to len use 1
				}else{
					in = 0x0ULL; //if greater pad 0
				}
			}
			buffer[i][j] = in;
		}
	}
    appendLength(l, buffer[bufferSize-1][7], buffer[bufferSize-1][6]);//last er duita bit length
    return buffer;
}
string padding(){
    uint64_t** buffer;//pura message ta etay rakhbo total 16*64bits
    uint64_t w[8];//512 bit word 8 ta 8 bit

    buffer = padding((unsigned char*) input.c_str()); // prepared n*16*64 bit blocks using padding
}
int main(){
    takeInput();
    string x;
    x=padding();
}