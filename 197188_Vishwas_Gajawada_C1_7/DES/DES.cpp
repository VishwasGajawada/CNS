#include <iostream>
using namespace std;

/// declaration of tables ///
int IP[] =
{
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17,  9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};
 
int E[] =
{
    32,  1,  2,  3,  4,  5,
    4,  5,  6,  7,  8,  9,
    8,  9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32,  1
};
 
int P[] =
{
    16,  7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2,  8, 24, 14,
    32, 27,  3,  9,
    19, 13, 30,  6,
    22, 11,  4, 25
};
 
int FP[] =
{
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41,  9, 49, 17, 57, 25
};

int S[8][4][16] = {
    {
        14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
        0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
        4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
        15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13
    },
    {
        15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
        3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
        0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
        13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9
    },
    {
        10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
        13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
        13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
        1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12
    },
    {
        7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
        13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
        10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
        3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14
    },
    {
        2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
        14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
        4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
        11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3
    },
    {
        12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
        10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
        9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
        4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
    },
    {
        4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
        13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
        1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
        6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12
    },
    {
        13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
        1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
        7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
        2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
    }
};

// key 64 to 56 bits
int PC1[] =
{
    57, 49, 41, 33, 25, 17,  9,
    1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27,
    19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29,
    21, 13,  5, 28, 20, 12,  4
};

// key compression table (56 to 48 bits)
int PC2[] =
{
    14, 17, 11, 24,  1,  5,
    3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8,
    16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

int SHIFTS[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

string inputStringHex;

struct DES {
    int key[64], key56[56];
    int keyC[17][28], keyD[17][28], keyCD[17][56];
    int L[17][32], R[17][32];
    int subKey[17][48];

    void init(string key_str = "AABB09182736CCDD") {
        hexToBin(key_str, key);
        this->keyGen();
    }

    /* Generates Sub key for the specified round*/
    void subKeyGenRound(int round) {
        copyBinaryNumber(keyC[round-1], keyC[round], 28);
        copyBinaryNumber(keyD[round-1], keyD[round], 28);

        for(int i=0; i < SHIFTS[round-1]; i++) {
            leftShift(keyC[round], 28);
            leftShift(keyD[round], 28);
        }
        combineBinaryNumber(keyC[round], keyD[round], keyCD[round], 28);
        // key compression
        permute(keyCD[round], subKey[round], PC2, 48);
    }

    /* Generates Sub keys for all the 16 rounds*/
    void keyGen() {
        cout<<"Initial key\t: "<<binToHex(key, 64)<<endl;

        permute(key, key56, PC1, 56);
        splitBinaryNumber(key56, keyC[0], keyD[0], 56);
        for(int i=1;i<=16;i++) {
            subKeyGenRound(i);
        }

        for(int i=1;i<=16;i++) {
            cout<<"subkey "<<i<<"\t: "<<binToHex(subKey[i], 48)<<endl;
        }
    }

    void encryptionRound(int round, int roundKey[48]) {
        copyBinaryNumber(R[round-1], L[round], 32);

        int r48[48];
        permute(R[round-1], r48, E, 48);
        int kXorR[48];
        _xor(roundKey, r48, kXorR, 48);
        int Sout[32]; // output after S boxes
        for(int i=0;i<8;i++) {
            int row = 2*kXorR[i*6] + kXorR[i*6 + 5];
            int col = 8*kXorR[i*6 + 1] + 4*kXorR[i*6 + 2] + 2*kXorR[i*6 + 3] + 1*kXorR[i*6 + 4];
            int val  = S[i][row][col];
            decToBin(val, Sout+i*4);
        }
        int SoutPermuted[32];
        permute(Sout, SoutPermuted, P, 32);

        _xor(L[round-1], SoutPermuted, R[round], 32);
    }

    /* returns the string after encryption/decryption */
    string encrypt(string plain_text = "123456ABCD132536", bool _decrypt = false) {
        if(_decrypt) cout<<"\nDecryption : \n";
        else cout<<"\nEncryption : \n";


        int input_[64], input[64], cipher_text[64];
        hexToBin(plain_text, input_);
        // initial permutation
        permute(input_, input, IP, 64);
        splitBinaryNumber(input, L[0], R[0], 64);

        for(int i=1;i<=16;i++) {
            if(_decrypt) encryptionRound(i, subKey[17-i]);
            else encryptionRound(i, subKey[i]);
        }

        for(int i=1;i<=16;i++) {
            printf("Round %2d\t: %s %s\n", i, binToHex(L[i], 32).c_str(), binToHex(R[i], 32).c_str());
        }

        int temp[64];
        combineBinaryNumber(R[16], L[16], temp, 32);
        permute(temp, cipher_text, FP, 64);
        string cipher = binToHex(cipher_text, 64);
        return cipher;
    }

    /* returns the decrypted string */
    string decrypt(string cipher_text) {
        return encrypt(cipher_text, true);
    }


    //////////////// helper functions //////////////

    void copyBinaryNumber(int inp[], int out[], int len) {
        for(int i=0;i<len;i++) out[i] = inp[i];
    }

    void _xor(int inp1[], int inp2[], int out[], int len) {
        for(int i=0;i<len;i++) out[i] = (inp1[i] + inp2[i])%2;
    }
    
    void decToBin(int dec, int bin[]) {
        for(int i=3;i>=0;i--) {
            bin[3-i] = ((dec>>i)&1);
        }
    }
    
    void hexToBin(string hex, int bin[]) {
        int len = hex.length();
        for(int i=0; i<len;i++) {
            char c = hex[i];
            int val = (c>='0' && c<='9')?c-'0':10+(c-'A');
            decToBin(val, bin + i*4);
        }
    }
    
    int binToDec(int bin[]) {
        int dec = 0;
        for(int i=0;i<4;i++) dec = dec*2 + bin[i];
        return dec;
    }
    
    string binToHex(int bin[], int len) {
        string hex = "";
        for(int i=0;i<len;i+=4) {
            int dec = binToDec(bin+i);
            if(dec<10) hex+=('0'+dec);
            else hex+=('A'+dec-10);
        }
        return hex;
    }
    
    void permute(int inp[], int out[], int perm_table[], int outlen) {
        for(int i=0;i<outlen;i++) out[i] = inp[perm_table[i] - 1];
    }

    void splitBinaryNumber(int inp[], int out_left[], int out_right[], int inplen) {
        for(int i=0;i<inplen/2;i++) out_left[i] = inp[i];
        for(int i=inplen/2;i<inplen;i++) out_right[i-inplen/2] = inp[i];
    }

    void combineBinaryNumber(int inp_left[], int inp_right[], int out[], int inplen) {
        for(int i=0;i<inplen;i++) out[i] = inp_left[i];
        for(int i=0;i<inplen;i++) out[i+inplen] = inp_right[i];
    }

    void leftShift(int inp[], int len) {
        int msb = inp[0];
        for(int i=0;i<len-1;i++) inp[i] = inp[i+1];
        inp[len-1] = msb;
    }
};

int main() {
    struct DES d;
    string key = "AABBCCDD11223344";
    d.init(key);

    string plainText = "123456ABCDEF1234";

    string cipherText = d.encrypt(plainText);
    printf("Plain text input = %s\nEncrypted cipher text = %s\n\n", plainText.c_str(), cipherText.c_str());
    
    string decrypted = d.decrypt(cipherText);
    printf("Cipher text input = %s\nDecrypted cipher text = %s\n\n", cipherText.c_str(), decrypted.c_str());

    if(decrypted == plainText) cout<<"Decrypted successfully and obtained the plain text\n\n";
    return 0;
}