#include <iostream>
#include <string>
using namespace std;

// Perform modulo-2 division
string divide(string data, string generator)
{
    int n = generator.length();

    for (int i = 0; i <= data.length() - n; i++)
    {
        // Perform XOR only when current bit is 1
        if (data[i] == '1')
        {
            for (int j = 0; j < n; j++)
            {
                if (data[i + j] == generator[j])
                    data[i + j] = '0';
                else
                    data[i + j] = '1';
            }
        }
    }

    // Return remainder
    return data.substr(data.length() - n + 1);
}

// Generate CRC codeword
string generateCRC(string data, string generator)
{
    int r = generator.length() - 1;

    // Append r zeros
    string appendedData = data + string(r, '0');

    // Find remainder
    string remainder = divide(appendedData, generator);

    // Codeword = original data + remainder
    return data + remainder;
}

// Check received data
bool checkCRC(string received, string generator)
{
    string remainder = divide(received, generator);

    // If remainder contains 1, error exists
    for (char bit : remainder)
    {
        if (bit == '1')
            return false;
    }

    return true;
}

int main()
{
    string data, generator;

    cout << "Enter data bits: ";
    cin >> data;

    cout << "Enter generator polynomial: ";
    cin >> generator;

    // Check input
    for (char c : data)
    {
        if (c != '0' && c != '1')
        {
            cout << "Invalid data. Enter only 0 and 1." << endl;
            return 0;
        }
    }

    for (char c : generator)
    {
        if (c != '0' && c != '1')
        {
            cout << "Invalid generator. Enter only 0 and 1." << endl;
            return 0;
        }
    }

    // Generate CRC
    string transmitted = generateCRC(data, generator);

    cout << "\nCRC Codeword: ";
    cout << transmitted << endl;

    cout << "CRC Remainder: ";
    cout << transmitted.substr(data.length()) << endl;

    // Introduce error
    int errorPosition;

    cout << "\nEnter position to introduce error";
    cout << " (0 for no error): ";
    cin >> errorPosition;

    if (errorPosition != 0)
    {
        if (errorPosition >= 1 &&
            errorPosition <= transmitted.length())
        {
            // Flip the bit
            transmitted[errorPosition - 1] =
                (transmitted[errorPosition - 1] == '0')
                ? '1'
                : '0';

            cout << "Received data with error: "
                 << transmitted << endl;
        }
        else
        {
            cout << "Invalid error position." << endl;
            return 0;
        }
    }

    // Receiver checks the data
    cout << "\nReceiver checking..." << endl;

    if (checkCRC(transmitted, generator))
    {
        cout << "No error detected." << endl;
    }
    else
    {
        cout << "Error detected!" << endl;
    }

    return 0;
}