/*

CIS7
FINAL PROJECT
TEAM JT
Joseph Tolentino

*/

/*
  Case 3: Vigenere Cipher Decryption
Vigenere Cipher is a method of encrypting alphabetic text. It uses a simple form of polyalphabetic substitution. A polyalphabetic cipher is any cipher based on substitution, using multiple substitution alphabets .The encryption of the original text is done using the Vigenère square or Vigenère table.
The table consists of the alphabets written out 26 times in different rows, each alphabet shifted cyclically to the left compared to the previous alphabet, corresponding to the 26 possible Caesar Ciphers.
At different points in the encryption process, the cipher uses a different alphabet from one of the rows.
The alphabet used at each point depends on a repeating keyword.

Example:
Input : Plaintext :   GEEKSFORGEEKS
Keyword :  AYUSH
Output : Ciphertext :  GCYCZFMLYLEIM

For generating key, the given keyword is repeated in a circular manner until it matches the length of the plain text.
The keyword "AYUSH" generates the key "AYUSHAYUSHAYU"
The plain text is then encrypted using the process explained below.

Encryption:
The first letter of the plaintext, G is paired with A, the first letter of the key. So use row G and column A of the Vigenère square, namely G. Similarly, for the second letter of the plaintext, the second letter of the key is used, the letter at row E and column Y is C. The rest of the plaintext is enciphered in a similar fashion.

Decryption:
Decryption is performed by going to the row in the table corresponding to the key, finding the position of the ciphertext letter in this row, and then using the column’s label as the plaintext. For example, in row A (from AYUSH), the ciphertext G appears in column G, which is the first plaintext letter. Next we go to row Y (from AYUSH), locate the ciphertext C which is found in column E, thus E is the second plaintext letter.

An easier implementation could be to visualize Vigenère algebraically by converting [A-Z] into numbers [0–25].

Encryption
The the plaintext(P) and key(K) are added modulo 26.
Ei = (Pi + Ki) mod 26

Decryption
Di = (Ei - Ki + 26) mod 26
Note: Di denotes the offset of the i-th character of the plaintext. Like offset of A is 0 and of B is 1 and so on.

1.	Given the above description of the Vigenère cipher, create a C++ program that encrypt and decrypts a message from the user. 
2.	Test the program to verify that the output is accurate. Assess program limitations. 
3.	Provide documentation that entails programming approach for encryption and decryption.

*/

//preproccessor directives
#include <iostream>
#include <string>
using namespace std;


//function prototypes - defined below main
int letterToNumber(char);
char numberToLetter(int);
string reKey(string, string);
string encrypt(string, string);
string decrypt(string, string);



int main()
{
  //variables
  string plaintext; //holds user submitted plaintext of message to be encrypted
  string keyword; //holds user submitted keyword to be used for encryption
  string rekey; //holds key to be used for encryption
  string encryptedtext; //holds encrypted message using the Vigenere Cipher
  string decryptedtext; //holds decrypted message using the Vigenere Cipher/ **should end up with the same as the initial plaintext**


  //prompts and inputs from user
  cout << "Enter plaintext to be encrypted: "; //prompts user to enter plaintext
 getline(cin, plaintext);  //**DELETE THIS REMARK **TESTED WITH SUBMITTING "GEEKSFORGEEKS"**

  cout << "Enter the encryption keyword: "; //prompts user to enter keyword
  getline(cin, keyword); //**DELETE THIS REMARK **TESTED WITH SUBMITTING "AYUSH"**


  //function Calls
   rekey = reKey(plaintext, keyword); //calls rekey function to rekey the keyword to be same length as plaintext to be used in encryption

  encryptedtext = encrypt(plaintext, rekey); //calls encrypt function to encrypt the plaintext using the rekeyed keyword

  decryptedtext = decrypt(encryptedtext, rekey); //calls decrypt function to decrypt the encryptedtext using the rekeyed keyword


  //console outputs
  cout << "Encrypted text: " << encryptedtext << endl; //encrpyted text //**DELETE THIS REMARK **SHOULD OUTPUT "GCYCZFMLYLEIM"**
  cout << "Decrypted text: " << decryptedtext << endl; //decrypted text **should end up with initial plaintext**

  return 0;

}


//function definitions

//function to convert a letter to a number uses the ASCII table values
int letterToNumber(char letter)
{
  
    if (isalpha(letter)) //if character is a letter
    {
      letter = toupper(letter); //use upper to keep from having to use two separate for A..Z a..z
   
    return letter - 'A'; //return the number value of the letter(ASCII VALUE)
    }
    else
    {
      return -1; //if letter isnt alpha, just send it back.
    }
  
};


//function to convert a number to a letter uses the ASCII table values
char numberToLetter(int num)
{
  if (num >= 0 && num <= 26) //if number is between 0 and 26
  {
  return num + 'A';  //converts each number back to a letter by adding the ASCII value of A
  }
    return '?'; //if number isnt between 0 and 26, just send it back.
  
};


//function to reKey the keyword to match the length of the plaintext
string reKey (string plaintext, string keyword) 
{
  string reKey; //holds the rekeyed version of the keyword
  for(int i = 0; i < plaintext.length(); i++) //loops through the plaintext
    {
      reKey += keyword[i % keyword.length()]; //adds the keyword to the reKey string
    }
  return reKey; //returns the reKeyed version of the keyword
};


//function to encrypt the plaintext
string encrypt(string plaintext, string reKey)
{
  string encryptedtext = ""; //holds the encrypted text
  for(int i = 0; i < plaintext.length(); i++) //loops through the plaintext
    {
      if(isalpha(plaintext[i])) //if the character is a letter)
      {
       int Pi = letterToNumber(plaintext[i]); //converts the plaintext letters to numbers
       int Ki = letterToNumber(reKey[i]); //converts the reKey letters to numbers
       int Ei = (Pi + Ki) % 26; //formula for encryption
      encryptedtext += numberToLetter(Ei); //converts the encrypted numbers to letters
      }
      else
      {
        encryptedtext += plaintext[i];//if the character is not a letter just add as is
      }
    }  
      return encryptedtext; //returns the encrypted text
  
}


// Function to decrypt the encrypted text
string decrypt(string encryptedtext, string rekey)
{
    string decryptedText = ""; //holds the decrypted text
    for (int i = 0; i < encryptedtext.length(); i++) //loops through the encrypted text
    {
      if (isalpha(encryptedtext[i])) //only if the character is a letter
      {
        int Ei = letterToNumber(encryptedtext[i]); //converts the encrypted letters to numbers
        int Ki = letterToNumber(rekey[i]); //converts the rekey letters to numbers
        int Pi = (Ei - Ki + 26) % 26; //formula for decryption
        decryptedText += numberToLetter(Pi); // Converts the decrypted numbers to letters
      }
      else
      {
        decryptedText += encryptedtext[i]; //if the character is not a letter just add as is
      }
    }  
    return decryptedText; //returns the decrypted text 
}