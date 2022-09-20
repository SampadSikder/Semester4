void KeyExpansionCore(unsigned char * in, int i); 
void addRoundKey(unsigned char state[], unsigned char roundKey[]);
void subBytes(unsigned char state[]);
void shiftRows(unsigned char state[]);
void mixColumn(unsigned char state[]);
void getRoundKey(unsigned char roundKey[], unsigned char expandedKey[], int round);
