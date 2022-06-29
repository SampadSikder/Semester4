#include <bits/stdc++.h>
using namespace std;
string encrypt(string input, char table[][128])
{
    for (int i = 0; i < input.length(); i++)
    {

        input[i] = table[input[i]][i % 128];
    }
    return input;
}
string decrypt(string input, char table[][128])
{
    for (int i = 0; i < input.length(); i++)
    {

        for (int x = 0; x < 128; x++)
        {
            if (table[x][i % 128] == input[i])
            {
                input[i] = x;
                break;
            }
        }
    }
    return input;
}

int main()
{
    char table[128][128];

    string input;
    getline(cin, input);

    for (int i = 0; i < 128; i++)
    {
        for (int j = 0; j < 128; j++)
        {
            table[i][j] = ((i + 1 + j) % 128);
        }
    }
    string encrypted = encrypt(input, table);
    cout << "Encrypted message: " << encrypted << endl;
    cout << "Decrypted message: " << decrypt(encrypted, table) << endl;
}