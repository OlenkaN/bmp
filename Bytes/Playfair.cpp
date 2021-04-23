#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
#define ALPHA "ABCDEFGHIJKLMNOPQRSTUVXYZ"

class playfair
{
private:
    char matrix[5][5];
public:
    string textEditing(string text)
    {
        string nmsg = "";
        for (int x = 0; x < text.length(); x+=2) {
            nmsg += text[x];
            if (x + 1 < text.length()) {
                if ((text[x] == text[x + 1]) && (text[x] != 'X'))
                {
                    nmsg += 'X';
                }
                nmsg += text[x + 1];
            }
        }
            text = nmsg;

            if (text.length() & 1)
            {
                text += 'X';
            }
            return text;

        
    }
        string textEditingRemove(string text)
        {
            string nmsg = "";
            for (int x = 0; x < text.length(); ++x) {

                if (x + 2 < text.length()) {
                    if ((text[x] == text[x + 2]) && (text[x + 1] == 'X') && (text[x] != 'X')) {
                        nmsg += text[x];
                        nmsg += text[x + 2];
                        x += 2;
                    }
                    else
                    {
                        nmsg += text[x];
                    }

                }

            }
            text = nmsg;

            if ((!(text.length() & 1)) && text[text.length() - 1] == 'X')
            {
                text.pop_back();
            }
            return text;

        }
    

        bool getPos(char l, int& r, int& c) {
            for (int y = 0; y < 5; y++)
                for (int x = 0; x < 5; x++)
                    if (matrix[y][x] == l) {
                        c = x;
                        r = y;
                        return true;
                    }
            return false;
        }
        void setKey(const char* key)
        {
            string keyNew = string(key);
            keyNew += ALPHA;
            string s = "";
            for (string::iterator it = keyNew.begin(); it != keyNew.end(); ++it) {
                *it = toupper(*it);
                if (*it < 65 || *it > 90)
                    continue;
                if (s.find(*it) == -1)
                    s += toupper(*it);
            }
            copy(s.begin(), s.end(), &matrix[0][0]);
        }
        string playfair_encrypt(const char* key, string text)
        {
            setKey(key);
            transform(text.begin(), text.end(), text.begin(), ::toupper);
            string textToEncrypt = textEditing(text);
            string encrypt = "";
            int r1, r2, c1, c2;

            for (int i = 0; i < textToEncrypt.length(); i += 2)
            {
                if (i + 1 < textToEncrypt.length()) {

                    if (getPos(toupper(textToEncrypt[i]), r1, c1) && getPos(toupper(textToEncrypt[i + 1]), r2, c2))
                    {
                        if (r1 == r2 && c1 == c2)
                        {
                            encrypt += matrix[(r1 + 1) % 5][c1];
                            encrypt += matrix[(r2 + 1) % 5][c2];
                        }
                        else if (r1 == r2)
                        {
                            encrypt += matrix[r1][(c1 + 1) % 5];
                            encrypt += matrix[r2][(c2 + 1) % 5];
                        }
                        else if (c1 == c2)
                        {
                            encrypt += matrix[(r1 + 1) % 5][c1];
                            encrypt += matrix[(r2 + 1) % 5][c2];
                        }
                        else
                        {
                            encrypt += matrix[r1][c2];
                            encrypt += matrix[r2][c1];
                        }
                    }
                }
            }
            return encrypt;

        }
        string playfair_decrypt(const char* key, string text)
        {
            setKey(key);
            string textToDecrypt = string(text);
            string decrypt = "";
            int r1, r2, c1, c2;

            for (int i = 0; i < textToDecrypt.length(); i += 2)
            {
                if (i + 1 < textToDecrypt.length()) {

                    if (getPos(textToDecrypt[i], r1, c1) && getPos(textToDecrypt[i + 1], r2, c2))
                    {
                        if (r1 == r2 && c1 == c2)
                        {
                            if (r1 == 0)
                            {
                                r1 = r2 = 5;
                            }
                            decrypt += matrix[(r1 - 1) % 5][c1];
                            decrypt += matrix[(r2 - 1) % 5][c2];
                        }
                        else if (r1 == r2)
                        {
                            if (c1 == 0)
                            {
                                c1 = c2 = 5;
                            }
                            decrypt += matrix[r1][(c1 - 1) % 5];
                            decrypt += matrix[r2][(c2 - 1) % 5];
                        }
                        else if (c1 == c2)
                        {
                            if (r1 == 0)
                            {
                                r1 = r2 = 5;
                            }
                            decrypt += matrix[(r1 - 1) % 5][c1];
                            decrypt += matrix[(r2 - 1) % 5][c2];
                        }
                        else
                        {
                            decrypt += matrix[r1][c2];
                            decrypt += matrix[r2][c1];
                        }
                    }
                }
            }
            return textEditingRemove(decrypt);

        }
    };
    int main2()
    {
        playfair test;
        //cout<<(test.playfair_decrypt("belfast","RGRBTAPZ"));
        string encrypted = test.playfair_encrypt("please", "Taxxxiii");
        printf("%s", encrypted.c_str());
        // "Taxxxiii" --> "TAXXXIIXIX"
        // RS EE VJ JV JV
        string decrypted = test.playfair_decrypt("please", encrypted.c_str());
        printf("%s", decrypted.c_str());
        return 0;
    }

