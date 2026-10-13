#include <iostream>
#include <vector>
using namespace std;

// Check whether position is a power of 2
bool isPowerOfTwo(int n)
{
    return (n & (n - 1)) == 0;
}

// Generate Hamming Code
vector<int> generateHammingCode(string data)
{
    int m = data.length();
    int r = 0;

    // Find number of parity bits
    while ((1 << r) < (m + r + 1))
    {
        r++;
    }

    int totalBits = m + r;

    // Index 0 is unused
    vector<int> hamming(totalBits + 1, 0);

    // Place data bits
    int j = 0;

    for (int i = 1; i <= totalBits; i++)
    {
        if (!isPowerOfTwo(i))
        {
            hamming[i] = data[j++] - '0';
        }
    }

    // Calculate parity bits (EVEN PARITY)
    for (int p = 1; p <= totalBits; p *= 2)
    {
        int parity = 0;

        for (int i = p; i <= totalBits; i += 2 * p)
        {
            for (int j = i; j < i + p && j <= totalBits; j++)
            {
                parity ^= hamming[j];
            }
        }

        hamming[p] = parity;
    }

    return hamming;
}

// Display code from left to right
void displayCode(vector<int> code)
{
    for (int i = code.size() - 1; i >= 1; i--)
    {
        cout << code[i];
    }

    cout << endl;
}

// Detect and correct error
void detectAndCorrect(vector<int>& code)
{
    int n = code.size() - 1;
    int errorPosition = 0;

    // Check parity bits
    for (int p = 1; p <= n; p *= 2)
    {
        int parity = 0;

        for (int i = p; i <= n; i += 2 * p)
        {
            for (int j = i; j < i + p && j <= n; j++)
            {
                parity ^= code[j];
            }
        }

        if (parity != 0)
        {
            errorPosition += p;
        }
    }

    if (errorPosition == 0)
    {
        cout << "No error detected." << endl;
    }
    else
    {
        cout << "Error detected at position: "
             << errorPosition << endl;

        // Correct the error
        code[errorPosition] ^= 1;

        cout << "Error corrected successfully." << endl;

        cout << "Corrected Hamming Code: ";
        displayCode(code);
    }
}

int main()
{
    string data;

    cout << "Enter data bits: ";
    cin >> data;

    // Check binary input
    for (char c : data)
    {
        if (c != '0' && c != '1')
        {
            cout << "Invalid input. Enter only 0 and 1." << endl;
            return 0;
        }
    }

    // Generate Hamming code
    vector<int> code = generateHammingCode(data);

    cout << "\nGenerated Hamming Code: ";
    displayCode(code);

    // Introduce error
    int errorPosition;

    cout << "\nEnter position to introduce error";
    cout << " (0 for no error): ";
    cin >> errorPosition;

    if (errorPosition != 0)
    {
        if (errorPosition >= 1 && errorPosition < code.size())
        {
            code[errorPosition] ^= 1;

            cout << "Code after introducing error: ";
            displayCode(code);
        }
        else
        {
            cout << "Invalid error position." << endl;
            return 0;
        }
    }

    // Receiver side
    cout << "\nReceiver checking..." << endl;

    detectAndCorrect(code);

    return 0;
}
