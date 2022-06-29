#include <bits/stdc++.h>
using namespace std;
string encrypt(string input, int key)
{
    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] >= 'A' && input[i] <= 'Z')
        {
            input[i] = (((input[i] - 'A') + key) % 26) + 'A';
        }
        else if (input[i] >= 'a' && input[i] <= 'z')
        {
            input[i] = (((input[i] - 'a') + key) % 26) + 'a';
        }
        else
        {
            continue;
        }
    }
    return input;
}
string decrypt(string input, int key)
{
    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] >= 'A' && input[i] <= 'Z')
        {
            input[i] = input[i] - key;
            if (input[i] < 'A')
            {
                input[i] = input[i] + 26;
            }
        }
        else if (input[i] >= 'a' && input[i] <= 'z')
        {
            input[i] = input[i] - key;
            if (input[i] < 'a')
            {
                input[i] = input[i] + 26;
            }
        }
        else
        {
            continue;
        }
    }
    return input;
}

int main()
{
    printf("Enter text and key:\n");
    string input;
    getline(cin, input);
    int key;
    cin >> key;
    string encrypted = encrypt(input, key);
    cout << encrypted << endl;
    string decrypted = decrypt(encrypted, key);
    cout << decrypted << endl;
}