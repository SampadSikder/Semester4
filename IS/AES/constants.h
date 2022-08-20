void KeyExpansionCore(unsigned char * in, unsigned char i); 
void addRoundKey(char state[], char roundKey[]);
void subBytes(char state[]);
void shiftRows(char state[]);
void mixColumn(char state[]);
void getRoundKey(char roundKey[], char expandedKey[], int round);