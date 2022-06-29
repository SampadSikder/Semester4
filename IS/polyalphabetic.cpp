#include <bits/stdc++.h>
using namespace std;
string encrypt(string input, char lower_table[][26], char upper_table[][26])
{
    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] >= 'a' && input[i] <= 'z')
            input[i] = lower_table[input[i] - 'a'][i % 26];
        else if (input[i] >= 'A' && input[i] <= 'Z')
            input[i] = upper_table[input[i] - 'A'][i % 26];
    }
    return input;
}
string decrypt(string input, char lower_table[][26], char upper_table[][26])
{
    for (int i = 0; i < input.length(); i++)
    {

        for (int x = 0; x < 26; x++)
        {
            if (lower_table[x][i % 26] == input[i])
            {
                input[i] = x + 'a';
                break;
            }
            else if (upper_table[x][i % 26] == input[i])
            {
                input[i] = x + 'A';
                break;
            }
        }
    }
    return input;
}

int main()
{
    char lower_table[26][26], upper_table[26][26];

    string input;
    getline(cin, input);

    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            lower_table[i][j] = ((i + 1 + j) % 26) + 'a';
        }
        for (int j = 0; j < 26; j++)
        {
            upper_table[i][j] = ((i + 1 + j) % 26) + 'A';
        }
    }
    /*for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            cout << table[i][j] << " ";
        }
        cout << endl;
    }*/
    string encrypted = encrypt(input, lower_table, upper_table);
    cout << "Encrypted message: " << encrypted << endl;
    cout << "Decrypted message: " << decrypt(encrypted, lower_table, upper_table) << endl;
}