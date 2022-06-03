#include "aes.h"
#include <string>
#include <vector>
AES::AES(int keySize,std::string &aesKey,std::string &plainText){
    NUM_OF_KEY_BLOCK_32 = keySize/32;
    NUM_OF_ROUND = NUM_OF_KEY_BLOCK_32 + 6;
    RoundKey.resize(NUM_OF_BLOCK * (NUM_OF_ROUND + 1) * 4); //BYTE

    this->keys = std::vector<BYTE>(aesKey.begin(),aesKey.end());
    TextToStateMat(plainText);
}

void AES::TextToStateMat(std::string &plainText){
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            //for example:abcd(i:0*4) abcd(i:1*4) abcd(i:2*4) abcd(i:3*4)
            state[j][i] = (BYTE)plainText[i*4+j];
        }
    }
}

void AES::KeyExpansion(){
    //Input[w1,w2,w3,w4] -> w44 for 128bit key
    //0's round -> [wi,wi+1,..wi+3]
    //1's round -> [w4,...w7]

    /*
    From [w0,w1,w2,w3] -> [w4,w5,w6,w7]
    w5 = w4 XOR w1
    w6 = w5 XOR w2
    w7 = w6 XOR w3

    How about w4?
    w4 = w1 XOR g(W3)
    then what is g?

    According to the definition
    g() - 3 steps
    - perform a one-byte left circular rotation - 向左移一個byte(循環)
    - a byte substitution of the word(returned previous step) by S_box
    - RoundConstant XOR bytes of m the previous step

    what is RoundConstant? => three rightmost bytes are always zero
    round constant of round[i] = Rcon[i]
    - Rcon[i] = {RC[i],0x00,0x00,0x00}
    - what is RC[i]?
        RC[i] obyes the following recursion: RC[1] = 0x01 and RC[j] = 0x02 x RC[j-1]
    */ 

    //first round 
    //take out 4 word[w0,w1,w2,w3]
    //block(w) = 4的倍數

    //[w0,w1,w2,w3] for 128 bits

    //w0 = string[0:3] = 1 char(1B)
    //w1 = string[4:7]
    //w2 = string[8:11]
    //w3 = string[12:15]

    //Each iteration = word -> assign to RoundKey
    for(int i = 0;i<4;i++){
        RoundKey[i*4] = keys[i*4];
        RoundKey[i+1*4] = keys[i+1*4];
        RoundKey[i+2*4] = keys[i+2*4];
        RoundKey[i+3*4] = keys[i+3*4];
        PrintEachWord(i);
    }

    //128 bits w4 ~ w44 need 9 more round
    //from 4 to 44 if it's 128 bits
    //if block size = 4, total round is blockSize + 6
    //total words size for expanded keys is roundSize * blockSize = 44
    std::vector<BYTE> tempBlock(4);
    for(int i = NUM_OF_KEY_BLOCK_32;i< NUM_OF_BLOCK*(NUM_OF_ROUND + 1) ;i++){
        // printf("Expanding W[%d]\n",i);
        //From starting poin : we have blockSize'th word
        //For example: 128 bit key -> 
        //init : 4words as w0,w1,w2,w3
        //Start at blockSize: -> generate w4

        //getting previous one that generate from round(i - 1)
        //i=4 ,getting w[4-1] = 3 => w[3]
        //According to the Key Expansion
        //128bit key -> each i/4 = 0, need a function g to geneate the begining of round i
        //for example: w[4],w[8],w[16]....until ends.
        //For XOR , we need [i-1] and [i-blockSize]
        // w3 =>BYTE[12...15]
        char temp[4];
        //take out previous one
        //eg:w3 =>BYTE[12...15]
        //Take out privous 4 Byte from our expanded key
        for(int k = 0;k<4;k++) temp[k] = RoundKey[(i-1) * NUM_OF_BLOCK + k];
        
        if(i % NUM_OF_KEY_BLOCK_32 == 0){
            //Do Function G()
            //one-byte left circular rotation
            //[a0,a1,a2,a3] -> [a1,a2,a3,a4]
            auto t = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = t;


            //byte substitution
            temp[0] = S_BOX[temp[0]];
            temp[1] = S_BOX[temp[1]];
            temp[2] = S_BOX[temp[2]];
            temp[3] = S_BOX[temp[3]];

            //XOR RrondConstant
            //RoundConst : all rightmost bit are 0 ,expect the first one
            //so here , we just need to XOR the first one
            temp[0] = temp[0] ^ Rcons[i];
        }

        //Put then back to the RoundKey
        //W4 = G(W(i/4)) XOR W(i - size)

        //update index = current i * size + offset(4 BYTE)
        //each iteratation repersent A new Word(4 BYTE)
        //Each Round = 4 iteratation
        for(int k = 0;k<4;k++){
            //W4 = W3(temp) XOR W1(i-block_size)*4+k(index of w1-BYTE)
            RoundKey[i * NUM_OF_BLOCK + k] = temp[k] ^ RoundKey[(i-NUM_OF_KEY_BLOCK_32) * 4 + k];
        }
    }}

void AES::AddRoundKey(int r){
    //Adding RoundKey to state
    //each Round involve 4word ,total 16 BYTEs


    //Colum-wise
    //for example:
    //[s(0,0),s(1,0),s(2,0),s(3,0)] XOR [RK(0,0),R(1,0),R(2,0),R(3,0)]
    //Total State : 16 BYTES
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            //for example: round 0
            //(i * 4 + j) indicate which column(i*4) of byte j
            //Round is indicate offset the RoundKey index
            state[j][i] ^= RoundKey[(i*NUM_OF_BLOCK+j) + (r * NUM_OF_BLOCK * 4)];

            /*
            Round 0:
            0*4 + 0 + round:0= 0 
            0*4 + 1 + round:0= 1
            0*4 + 2 + round:0= 2
            0*4 + 3 + round:0= 3

            ....
            Offest to 16 Byte(0-15Byte uses in Round 0)
            Round 1:
            0*4 + 0 + round:16= 16 
            0*4 + 1 + round:16= 17
            0*4 + 2 + round:16= 18
            0*4 + 3 + round:16= 19

            ....

            Round 2:
            0*4 + 0 + round:32 = 32
            0*4 + 1 + round:32 = 33
            0*4 + 2 + round:32 = 34
            0*4 + 3 + round:32 = 35
            ....
            */

           
        }
    }
}

void AES::SubStitute(){
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            state[i][j] = S_BOX[(int)state[i][j]];
        }
    }
}

void AES::ShiftRow(){
    std::vector<std::vector<int>> temp(4,std::vector<int>(4,0x00));
    for(int r = 1;r<4;r++){
        for(int c = 0;c<4;c++){
            temp[r][c] = state[r][(c+r)%4];
        }

        for(int c = 0;c<4;c++){
            state[r][c] = temp[r][c];
        }
    }
}

void AES::MixColumns(){
    // 1's row: (0x02 x S0) XOR (0x03 x S1) XOR S2 XOR S3
    // 2's row: S0 XOR (0x02 x S1) XOR (0x03 x S2) XOR S#
    // 3's row: S0 XOR S1 XOR (0x02 x S2) XOR (0x03 x S3)
    // 4's row: (0x03 x S0) XOR S1 XOR S2 XOR (0x02 x S3) 
    auto tempState = state;
    for(int col = 0;col <4 ; col ++){
        tempState[0][col] = GF_Mul(0x02,state[0][col]) ^ GF_Mul(0x03,state[1][col]) ^ state[2][col] ^ state[3][col];
        tempState[1][col] = state[0][col] ^ GF_Mul(0x02,state[1][col]) ^ GF_Mul(0x03,state[2][col]) ^ state[3][col];
        tempState[2][col] = state[0][col] ^ state[1][col] ^ GF_Mul(0x02,state[2][col]) ^ GF_Mul(0x03,state[3][col]);
        tempState[3][col] =  GF_Mul(0x03,state[0][col]) ^ state[1][col] ^ state[2][col] ^ GF_Mul(0x02,state[3][col]);
    }
    state = tempState;
}

void AES::InvSubStitute(){
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            state[i][j] = Inv_S_BOX[state[i][j]];
        }
    }
}

void AES::InvShiftRows(){
    std::vector<std::vector<int>> temp(4,std::vector<int>(4,0x00));
    for(int r = 1;r<4;r++){
        for(int c = 0;c<4;c++){
            temp[r][c] = state[r][(c - r + NUM_OF_BLOCK)%4];
        }

        for(int c = 0;c<4;c++){
            state[r][c] = temp[r][c];
        }
    }
}

void AES::InvMixColumns(){    
    auto tempState = state;
    for(int col = 0;col <4 ; col ++){
        tempState[0][col] = GF_Mul(0x0E,state[0][col]) ^ GF_Mul(0x0B,state[1][col]) ^ GF_Mul(0x0D,state[2][col]) ^ GF_Mul(0x09,state[3][col]);
        tempState[1][col] = GF_Mul(0x09,state[0][col]) ^ GF_Mul(0x0E,state[1][col]) ^ GF_Mul(0x0B,state[2][col]) ^ GF_Mul(0x0D,state[3][col]);
        tempState[2][col] = GF_Mul(0x0D,state[0][col]) ^ GF_Mul(0x09,state[1][col]) ^ GF_Mul(0x0E,state[2][col]) ^ GF_Mul(0x0B,state[3][col]);
        tempState[3][col] =  GF_Mul(0x0B,state[0][col]) ^ GF_Mul(0x0D,state[1][col]) ^ GF_Mul(0x09,state[2][col]) ^ GF_Mul(0x0E,state[3][col]);
    }
    state = tempState;}

void AES::InvAddRoundKey(){
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            state[j][i] ^= RoundKey[(i*NUM_OF_BLOCK+j) + ((NUM_OF_ROUND - r) * NUM_OF_BLOCK * 4)];
        }
    }
}


/*
    Suppose
    6E * 3
    state_pow [6E,6E*2,6E*4,6E*8]
    state_pow [6E,DC,A3,5D]

    mulVal: 0x03 : 11
    res:6E XOR value
    res: res' XOR DC = 1011 0010
*/
BYTE AES::GF_Mul(BYTE mulVal,BYTE stateByte){
    BYTE state_pow[4] = {stateByte,0x00,0x00,0x00};
    for(int i = 0;i<4;i++){
        state_pow[i] = state_pow[i-1] << 1;
        if(state_pow[i-1] & 0x80) state_pow[i] ^= 0x1B;
    }

    BYTE res;
    for(int i = 0;i<4;i++){
        if(mulVal >> i & 0x01){
            res ^= state_pow[i];
        }
    }

    return res;
}