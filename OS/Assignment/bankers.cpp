#include <bits/stdc++.h>
using namespace std;

int main()
{
    int r, p; // r-> number of resources, p-> number of processes

    cin >> r >> p;

    int maxNeed[p][r];
    int allocated[p][r];

    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            cin >> allocated[i][j];
        }
    }

    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            cin >> maxNeed[i][j];
        }
    }

    int availableResources[r];

    for (int i = 0; i < r; i++)
    {
        cin >> availableResources[i];
    }

    int needs[p][r];

    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            needs[i][j] = maxNeed[i][j] - allocated[i][j];
        }
    }

    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            needs[i][j] = maxNeed[i][j] - allocated[i][j];
        }
    }
    cout << "Needs matrix:\n";
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            cout << needs[i][j] << " ";
        }
        cout << endl;
    }

    bool safestate[p] = {false};
    int safeStateCount = 0;
    int currIndex = 0;
    for (int i = 0;;)
    {
        if (safestate[i] == false)
        {
            cout << "Checking state " << i << endl;
            int count = 0;
            for (int j = 0; j < r; j++)
            {

                if (availableResources[j] >= needs[i][j])
                {
                    count++;
                    // cout << count;
                }
            }
            if (count == r)
            {
                cout << "Confirming state " << i << endl;
                safestate[i] = true;
                for (int j = 0; j < r; j++)
                {
                    availableResources[j] += allocated[i][j];
                }
                // cout << "Current available resources: " << endl;
                // for (int j = 0; j < r; j++)
                // {
                //     cout << availableResources[j] << " ";
                // }
                // cout << endl;
                safeStateCount++;
            }
        }
        if (safeStateCount == p)
        {
            break;
        }
        i++;
        if (i == currIndex)
        {
            break;
        }
        currIndex = i;
        if (i == p)
            i = i % p;
    }

    if (safeStateCount == p)
    {
        cout << "All states are safe" << endl;
    }
    else
    {
        for (int i = 0; i < p; i++)
        {
            if (safestate[i] == false)
            {
                cout << "State " << i << " unsafe" << endl;
            }
        }
    }
}