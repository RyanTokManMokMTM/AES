#include<iostream>
#include <vector>
// #include "aes.cpp"

// typedef unsigned char BYTE;
// const int NUM_OF_BLOCK =  4;
// int NUM_OF_ROUND;
// int NUM_OF_KEY_BLOCK_32;
// //Total 10- Rcons[0] ignored
// std::vector<BYTE> Rcons = {
//     0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 
//     0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 
//     0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 
//     0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 
//     0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 
//     0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 
//     0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 
//     0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 
//     0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 
//     0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 
//     0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 
//     0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 
//     0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 
//     0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 
//     0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 
//     0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d
// };
// std::vector<BYTE> S_BOX{
//     0x63,0x7C,0x77,0x7B,0xF2,0x6B,0x6F,0xC5,0x30,0x01,0x67,0x2B,0xFE,0xD7,0xAB,0x76,
//     0xCA,0x82,0xC9,0x7D,0xFA,0x59,0x47,0xF0,0xAD,0xD4,0xA2,0xAF,0x9C,0xA4,0x72,0xC0,
//     0xB7,0xFD,0x93,0x26,0x36,0x3F,0xF7,0xCC,0x34,0xA5,0xE5,0xF1,0x71,0xD8,0x31,0x15,
//     0x04,0xC7,0x23,0xC3,0x18,0x96,0x05,0x9A,0x07,0x12,0x80,0xE2,0xEB,0x27,0xB2,0x75,
//     0x09,0x83,0x2C,0x1A,0x1B,0x6E,0x5A,0xA0,0x52,0x3B,0xD6,0xB3,0x29,0xE3,0x2F,0x84,
//     0x53,0xD1,0x00,0xED,0x20,0xFC,0xB1,0x5B,0x6A,0xCB,0xBE,0x39,0x4A,0x4C,0x58,0xCF,
//     0xD0,0xEF,0xAA,0xFB,0x43,0x4D,0x33,0x85,0x45,0xF9,0x02,0x7F,0x50,0x3C,0x9F,0xA8,
//     0x51,0xA3,0x40,0x8F,0x92,0x9D,0x38,0xF5,0xBC,0xB6,0xDA,0x21,0x10,0xFF,0xF3,0xD2,
//     0xCD,0x0C,0x13,0xEC,0x5F,0x97,0x44,0x17,0xC4,0xA7,0x7E,0x3D,0x64,0x5D,0x19,0x73,
//     0x60,0x81,0x4F,0xDC,0x22,0x2A,0x90,0x88,0x46,0xEE,0xB8,0x14,0xDE,0x5E,0x0B,0xDB,
//     0xE0,0x32,0x3A,0x0A,0x49,0x06,0x24,0x5C,0xC2,0xD3,0xAC,0x62,0x91,0x95,0xE4,0x79,
//     0xE7,0xC8,0x37,0x6D,0x8D,0xD5,0x4E,0xA9,0x6C,0x56,0xF4,0xEA,0x65,0x7A,0xAE,0x08,
//     0xBA,0x78,0x25,0x2E,0x1C,0xA6,0xB4,0xC6,0xE8,0xDD,0x74,0x1F,0x4B,0xBD,0x8B,0x8A,
//     0x70,0x3E,0xB5,0x66,0x48,0x03,0xF6,0x0E,0x61,0x35,0x57,0xB9,0x86,0xC1,0x1D,0x9E,
//     0xE1,0xF8,0x98,0x11,0x69,0xD9,0x8E,0x94,0x9B,0x1E,0x87,0xE9,0xCE,0x55,0x28,0xDF,
//     0x8C,0xA1,0x89,0x0D,0xBF,0xE6,0x42,0x68,0x41,0x99,0x2D,0x0F,0xB0,0x54,0xBB,0x16
// };
// std::vector<BYTE> Inv_S_BOX{
//     0x52,0x09,0x6A,0xD5,0x30,0x36,0xA5,0x38,0xBF,0x40,0xA3,0x9E,0x81,0xF3,0xD7,0xFB,
//     0x7C,0xE3,0x39,0x82,0x9B,0x2F,0xFF,0x87,0x34,0x8E,0x43,0x44,0xC4,0xDE,0xE9,0xCB,
//     0x54,0x7B,0x94,0x32,0xA6,0xC2,0x23,0x3D,0xEE,0x4C,0x95,0x0B,0x42,0xFA,0xC3,0x4E,
//     0x08,0x2E,0xA1,0x66,0x28,0xD9,0x24,0xB2,0x76,0x5B,0xA2,0x49,0x6D,0x8B,0xD1,0x25,
//     0x72,0xF8,0xF6,0x64,0x86,0x68,0x98,0x16,0xD4,0xA4,0x5C,0xCC,0x5D,0x65,0xB6,0x92,
//     0x6C,0x70,0x48,0x50,0xFD,0xED,0xB9,0xDA,0x5E,0x15,0x46,0x57,0xA7,0x8D,0x9D,0x84,
//     0x90,0xD8,0xAB,0x00,0x8C,0xBC,0xD3,0x0A,0xF7,0xE4,0x58,0x05,0xB8,0xB3,0x45,0x06,
//     0xD0,0x2C,0x1E,0x8F,0xCA,0x3F,0x0F,0x02,0xC1,0xAF,0xBD,0x03,0x01,0x13,0x8A,0x6B,
//     0x3A,0x91,0x11,0x41,0x4F,0x67,0xDC,0xEA,0x97,0xF2,0xCF,0xCE,0xF0,0xB4,0xE6,0x73,
//     0x96,0xAC,0x74,0x22,0xE7,0xAD,0x35,0x85,0xE2,0xF9,0x37,0xE8,0x1C,0x75,0xDF,0x6E,
//     0x47,0xF1,0x1A,0x71,0x1D,0x29,0xC5,0x89,0x6F,0xB7,0x62,0x0E,0xAA,0x18,0xBE,0x1B,
//     0xFC,0x56,0x3E,0x4B,0xC6,0xD2,0x79,0x20,0x9A,0xDB,0xC0,0xFE,0x78,0xCD,0x5A,0xF4,
//     0x1F,0xDD,0xA8,0x33,0x88,0x07,0xC7,0x31,0xB1,0x12,0x10,0x59,0x27,0x80,0xEC,0x5F,
//     0x60,0x51,0x7F,0xA9,0x19,0xB5,0x4A,0x0D,0x2D,0xE5,0x7A,0x9F,0x93,0xC9,0x9C,0xEF,
//     0xA0,0xE0,0x3B,0x4D,0xAE,0x2A,0xF5,0xB0,0xC8,0xEB,0xBB,0x3C,0x83,0x53,0x99,0x61,
//     0x17,0x2B,0x04,0x7E,0xBA,0x77,0xD6,0x26,0xE1,0x69,0x14,0x63,0x55,0x21,0x0C,0x7D
// };

// std::vector<BYTE> RoundKey;
// std::vector<BYTE> keys;
// std::vector<std::vector<BYTE>> state(4,std::vector<BYTE>(4,0x00));
// //@parms block size = keySize/32
// //example: 128/32 = 4 -> 32 bit(4Byte)

// void PrintExpandedWord(int i){
//     for(int start = i;i<4;i++){
//         printf("W[%d]:",i);
//         std::cout << RoundKey[i*4];
//         std::cout << RoundKey[i+1*4];
//         std::cout << RoundKey[i+2*4];
//         std::cout << RoundKey[i+3*4];
//         printf("\n");
//     }
//     printf("\n");
// }

// void PrintEachWord(int i){
//     printf("W[%d]:",i);
//     printf("%02hhx ",RoundKey[i*4]);
//     printf("%02hhx ",RoundKey[i*4 + 1]);
//     printf("%02hhx ",RoundKey[i*4 + 2]);
//     printf("%02hhx ",RoundKey[i*4 + 3]);
//     printf("\n");
// }

// void KeyExpansion(){
//     //Input[w1,w2,w3,w4] -> w44 for 128bit key
//     //0's round -> [wi,wi+1,..wi+3]
//     //1's round -> [w4,...w7]

//     /*
//     From [w0,w1,w2,w3] -> [w4,w5,w6,w7]
//     w5 = w4 XOR w1
//     w6 = w5 XOR w2
//     w7 = w6 XOR w3

//     How about w4?
//     w4 = w1 XOR g(W3)
//     then what is g?

//     According to the definition
//     g() - 3 steps
//     - perform a one-byte left circular rotation - 向左移一個byte(循環)
//     - a byte substitution of the word(returned previous step) by S_box
//     - RoundConstant XOR bytes of m the previous step

//     what is RoundConstant? => three rightmost bytes are always zero
//     round constant of round[i] = Rcon[i]
//     - Rcon[i] = {RC[i],0x00,0x00,0x00}
//     - what is RC[i]?
//         RC[i] obyes the following recursion: RC[1] = 0x01 and RC[j] = 0x02 x RC[j-1]
//     */ 

//     //first round 
//     //take out 4 word[w0,w1,w2,w3]
//     //block(w) = 4的倍數

//     //[w0,w1,w2,w3] for 128 bits

//     //w0 = string[0:3] = 1 char(1B)
//     //w1 = string[4:7]
//     //w2 = string[8:11]
//     //w3 = string[12:15]

//     //Each iteration = word -> assign to RoundKey
//     for(int i = 0;i<4;i++){
//         RoundKey[i*4] = keys[i*4];
//         RoundKey[i+1*4] = keys[i+1*4];
//         RoundKey[i+2*4] = keys[i+2*4];
//         RoundKey[i+3*4] = keys[i+3*4];
//         PrintEachWord(i);
//     }

//     //128 bits w4 ~ w44 need 9 more round
//     //from 4 to 44 if it's 128 bits
//     //if block size = 4, total round is blockSize + 6
//     //total words size for expanded keys is roundSize * blockSize = 44
//     std::vector<char> tempBlock(4);
//     for(int i = NUM_OF_KEY_BLOCK_32;i< NUM_OF_BLOCK*(NUM_OF_ROUND + 1) ;i++){
//         // printf("Expanding W[%d]\n",i);
//         //From starting poin : we have blockSize'th word
//         //For example: 128 bit key -> 
//         //init : 4words as w0,w1,w2,w3
//         //Start at blockSize: -> generate w4

//         //getting previous one that generate from round(i - 1)
//         //i=4 ,getting w[4-1] = 3 => w[3]
//         //According to the Key Expansion
//         //128bit key -> each i/4 = 0, need a function g to geneate the begining of round i
//         //for example: w[4],w[8],w[16]....until ends.
//         //For XOR , we need [i-1] and [i-blockSize]
//         // w3 =>BYTE[12...15]
//         char temp[4];
//         //take out previous one
//         //eg:w3 =>BYTE[12...15]
//         //Take out privous 4 Byte from our expanded key
//         for(int k = 0;k<4;k++) temp[k] = RoundKey[(i-1) * NUM_OF_BLOCK + k];
        
//         if(i % NUM_OF_KEY_BLOCK_32 == 0){
//             //Do Function G()
//             //one-byte left circular rotation
//             //[a0,a1,a2,a3] -> [a1,a2,a3,a4]
//             auto t = temp[0];
//             temp[0] = temp[1];
//             temp[1] = temp[2];
//             temp[2] = temp[3];
//             temp[3] = t;


//             //byte substitution
//             temp[0] = S_BOX[temp[0]];
//             temp[1] = S_BOX[temp[1]];
//             temp[2] = S_BOX[temp[2]];
//             temp[3] = S_BOX[temp[3]];

//             //XOR RrondConstant
//             //RoundConst : all rightmost bit are 0 ,expect the first one
//             //so here , we just need to XOR the first one
//             temp[0] = temp[0] ^ Rcons[i];
//         }

//         //Put then back to the RoundKey
//         //W4 = G(W(i/4)) XOR W(i - size)

//         //update index = current i * size + offset(4 BYTE)
//         //each iteratation repersent A new Word(4 BYTE)
//         //Each Round = 4 iteratation
//         for(int k = 0;k<4;k++){
//             //W4 = W3(temp) XOR W1(i-block_size)*4+k(index of w1-BYTE)
//             RoundKey[i * NUM_OF_BLOCK + k] = temp[k] ^ RoundKey[(i-NUM_OF_KEY_BLOCK_32) * 4 + k];
//         }
//         PrintEachWord(i);
//     }
// }

// void AddRoundKey(int r){
//     //Adding RoundKey to state
//     //each Round involve 4word ,total 16 BYTEs


//     //Colum-wise
//     //for example:
//     //[s(0,0),s(1,0),s(2,0),s(3,0)] XOR [RK(0,0),R(1,0),R(2,0),R(3,0)]
//     //Total State : 16 BYTES
//     for(int i = 0;i<4;i++){
//         for(int j = 0;j<4;j++){
//             //for example: round 0
//             //(i * 4 + j) indicate which column(i*4) of byte j
//             //Round is indicate offset the RoundKey index
//             state[j][i] ^= RoundKey[(i*NUM_OF_BLOCK+j) + (r * NUM_OF_BLOCK * 4)];

//             /*
//             Round 0:
//             0*4 + 0 + round:0= 0 
//             0*4 + 1 + round:0= 1
//             0*4 + 2 + round:0= 2
//             0*4 + 3 + round:0= 3

//             ....
//             Offest to 16 Byte(0-15Byte uses in Round 0)
//             Round 1:
//             0*4 + 0 + round:16= 16 
//             0*4 + 1 + round:16= 17
//             0*4 + 2 + round:16= 18
//             0*4 + 3 + round:16= 19

//             ....

//             Round 2:
//             0*4 + 0 + round:32 = 32
//             0*4 + 1 + round:32 = 33
//             0*4 + 2 + round:32 = 34
//             0*4 + 3 + round:32 = 35
//             ....
//             */

           
//         }
//     }
// }

// void TranformToState(std::string plainText){
//     for(int i = 0;i<4;i++){
//         for(int j = 0;j<4;j++){
//             //for example:abcd(i:0*4) abcd(i:1*4) abcd(i:2*4) abcd(i:3*4)
//             state[j][i] = (BYTE)plainText[i*4+j];
//         }
//     }
// }

// void SubStitute(){
//     for(int i = 0;i<4;i++){
//         for(int j = 0;j<4;j++){
//             state[i][j] = S_BOX[(int)state[i][j]];
//         }
//     }
// }

// void PrintState(){
//     for(int i = 0;i<4;i++){
//         for(int j = 0;j<4;j++){
//             printf("%02hhx ",state[i][j]);
//         }
//         printf("\n");
//     }
// }

// void ShiftRow(){
//     //row 1 not change - ignored

//     std::vector<std::vector<int>> temp(4,std::vector<int>(4,0x00));
//     for(int r = 1;r<4;r++){
//         for(int c = 0;c<4;c++){
//             temp[r][c] = state[r][(c+r)%4];
//         }

//         for(int c = 0;c<4;c++){
//             state[r][c] = temp[r][c];
//         }
//     }


// }

// BYTE GF_Mul(BYTE mulVal,BYTE state){
//     /*
//     Suppose
//     6E * 3
//     [6E,6E*2,6E*4,6E*8]
//     [6E,DC,A3,5D]

//     a: 0x03 : 11
//     v:6E XOR value
//     v: v' XOR DC = 1011 0010
//     */
    
//     BYTE mul_State[4] = {state, 0, 0, 0};
//     for (int i = 1; i < 4; i++){
//         mul_State[i] = mul_State[i - 1] << 1;
//         if (mul_State[i - 1] & 0x80)
//             mul_State[i] ^= 0x1B;
//     }
//     int value = 0;
//     for (int i = 0; i < 4; i++)
//         if ((mulVal >> i) & 0x01) value ^= mul_State[i];
//     return value;
// }

// void MixColumns(){
//     // 1's row: (0x02 x S0) XOR (0x03 x S1) XOR S2 XOR S3
//     // 2's row: S0 XOR (0x02 x S1) XOR (0x03 x S2) XOR S#
//     // 3's row: S0 XOR S1 XOR (0x02 x S2) XOR (0x03 x S3)
//     // 4's row: (0x03 x S0) XOR S1 XOR S2 XOR (0x02 x S3) 
//     auto tempState = state;
//     for(int col = 0;col <4 ; col ++){
//         tempState[0][col] = GF_Mul(0x02,state[0][col]) ^ GF_Mul(0x03,state[1][col]) ^ state[2][col] ^ state[3][col];
//         tempState[1][col] = state[0][col] ^ GF_Mul(0x02,state[1][col]) ^ GF_Mul(0x03,state[2][col]) ^ state[3][col];
//         tempState[2][col] = state[0][col] ^ state[1][col] ^ GF_Mul(0x02,state[2][col]) ^ GF_Mul(0x03,state[3][col]);
//         tempState[3][col] =  GF_Mul(0x03,state[0][col]) ^ state[1][col] ^ state[2][col] ^ GF_Mul(0x02,state[3][col]);
//     }
//     state = tempState;
// }

// void Encrypted(){
//     printf("Orginal State:\n");
//     PrintState();
//     //Starting at round 1-10,expect round 0
//     //Round 0 just need a AddRoung Key
//     printf("Round 0 - (Adding Round key):\n");
//     AddRoundKey(0); 
//     PrintState();

//     //Interation for rest of round
//     // //From 1 to
//     for(int i = 1;i<NUM_OF_ROUND;i++){
//         //subByte
//         printf("Round %d - Subtitute\n",i);
//         SubStitute();
//         PrintState();
//         //ShiftRow
//         printf("Round %d - ShiftRow\n",i);
//         ShiftRow();
//         PrintState();
//         //MixMat
//         printf("Round %d - MixColumns\n",i);
//         MixColumns();
//         PrintState();
//         //AddRoundKey
//         printf("Round %d - AddRoundKey\n",i);
//         AddRoundKey(i);
//         PrintState();

//         printf("\n");
//     }

//     //Last Round - without MixMat
//     //subByte
//     //ShiftRow
//     //MixMat
//     //AddRoundKey
//     printf("Round %d - AddRoundKey\n",NUM_OF_ROUND);
//     SubStitute();
//     PrintState();
//     //ShiftRow
//     printf("Round %d - AddRoundKey\n",NUM_OF_ROUND);
//     ShiftRow();
//     PrintState();
//     //MixMat
//     //AddRoundKey
//     printf("Round %d - AddRoundKey\n",NUM_OF_ROUND);
//     AddRoundKey(NUM_OF_ROUND);
//     PrintState();
// }

// void InvSubBytes(){
//     for(int i = 0;i<4;i++){
//         for(int j = 0;j<4;j++){
//             int index = (int)state[i][j];
//             state[i][j] = Inv_S_BOX[index];
//         }
//     }
// }

// void InvShiftRows(){
//     std::vector<std::vector<int>> temp(4,std::vector<int>(4,0x00));
//     for(int r = 1;r<4;r++){
//         for(int c = 0;c<4;c++){
//             temp[r][c] = state[r][(c - r + NUM_OF_BLOCK)%4];
//         }

//         for(int c = 0;c<4;c++){
//             state[r][c] = temp[r][c];
//         }
//     }
// }

// void InvMixColumns(){
//     auto tempState = state;
//     for(int col = 0;col <4 ; col ++){
//         tempState[0][col] = GF_Mul(0x0E,state[0][col]) ^ GF_Mul(0x0B,state[1][col]) ^ GF_Mul(0x0D,state[2][col]) ^ GF_Mul(0x09,state[3][col]);
//         tempState[1][col] = GF_Mul(0x09,state[0][col]) ^ GF_Mul(0x0E,state[1][col]) ^ GF_Mul(0x0B,state[2][col]) ^ GF_Mul(0x0D,state[3][col]);
//         tempState[2][col] = GF_Mul(0x0D,state[0][col]) ^ GF_Mul(0x09,state[1][col]) ^ GF_Mul(0x0E,state[2][col]) ^ GF_Mul(0x0B,state[3][col]);
//         tempState[3][col] =  GF_Mul(0x0B,state[0][col]) ^ GF_Mul(0x0D,state[1][col]) ^ GF_Mul(0x09,state[2][col]) ^ GF_Mul(0x0E,state[3][col]);
//     }
//     state = tempState;
// }

// void InvAddRoundKey(int r){
//     for(int i = 0;i<4;i++){
//         for(int j = 0;j<4;j++){
//             state[j][i] ^= RoundKey[(i*NUM_OF_BLOCK+j) + ((NUM_OF_ROUND - r) * NUM_OF_BLOCK * 4)];
//         }
//     }
// }

// void Decrypted(){
//     printf("Round 0 - InvAddRoundKey:\n");
//     InvAddRoundKey(0); 
//     PrintState();

//     // //Interation for rest of round
//     // //From 1 to
//     for(int i = 1;i<NUM_OF_ROUND;i++){
//         printf("Round %d - InvShiftRow\n",i);
//         InvShiftRows();
//         PrintState();

//         printf("Round %d - InvSubtitute\n",i);
//         InvSubBytes();
//         PrintState();

//         printf("Round %d - InvAddRoundKey\n",i);
//         InvAddRoundKey(i);
//         PrintState();
        
//         printf("Round %d - InvMixColumns\n",i);
//         InvMixColumns();
//         PrintState();
//         //AddRoundKey

//         printf("\n");
//     }

//     //Last Round - without MixMat
//     printf("Round %d - InvShiftRow\n",NUM_OF_ROUND);
//     InvShiftRows();
//     PrintState();

//     printf("Round %d - InvSubtitute\n",NUM_OF_ROUND);
//     InvSubBytes();
//     PrintState();

//     printf("Round %d - InvAddRoundKey\n",NUM_OF_ROUND);
//     InvAddRoundKey(NUM_OF_ROUND);
//     PrintState();
// }

int main(){

    int keySize=0;
    std::string intput_key;
    while(keySize != 128 && keySize != 192 && keySize != 256){
        std::cout << "Please input AES key size(only allow 128/192/256 sizes):";
        std::cin >> keySize;
    }

    if(keySize == 128){
        std::cout << "Pleas input 128 bits keys(16 characters)\n";
        std::cin >> intput_key;
        // keys.resize(16);
    }else if(keySize == 192){
        std::cout << "Pleas input 192 bits keys(24 characters)\n";
        std::cin >> intput_key;
        // keys.resize(24);
    }else if(keySize == 256){
        std::cout << "Pleas input 256 bits keys(32 characters)\n";
        std::cin >> intput_key;
        // keys.resize(32);
        exit(0);
    }else{
        return 0;
    }

    std::string plainText;
    std::cout << "input your plain(max 16characters)";
    std::cin >> plainText;

    if(plainText.length() < 16){
        for(int i = plainText.length();i<16;i++){
            plainText.push_back(0x00);
        }
    }



    return 0;
}

