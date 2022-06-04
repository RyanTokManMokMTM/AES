#include<iostream>
#include <vector>
#include <fstream>
#include "time.h"
#include "aes.cpp"

AES* NewAes(int keySize,std::string &aesKey,std::string &plainText){
    return new AES(keySize,aesKey,plainText);
}

std::string ReadFile(std::string fileName){
    std::ifstream keyFile(fileName);
    if(keyFile.fail()){
        std::cout << fileName <<" Not Exist\n";
        exit(1);
    }
    std::string key;
    getline(keyFile,key);
    keyFile.close();
    return key;
}

int main(int argc,char **argv){
    std::string keyFilePath,textFilePath;
    
    std::cout << "Enter key file path:";
    std::cin >> keyFilePath;

    std::cout << "Text file path:";
    std::cin >> textFilePath;

    std::string keyStr = ReadFile(keyFilePath);
    std::string textStr = ReadFile(textFilePath);

    int keySize = keyStr.length() *8;

    if(keySize != 128 && keySize != 192 && keySize != 256){
        std::cout << "You Key must be 16(128bits)/24(192bits)/32(256bits) characters.";
        exit(1);
    }

    if(textStr.length() > 16){
        std::cout << "[Warning] You Text is larger than 16(128 bits) character. The AES will just take the first 16 character as input.\n";
        textStr = textStr.substr(0,16);
    }
       
    if(textStr.length() < 16){
        for(int i = textStr.length();i<16;i++){
            textStr.push_back(0x00);
        }
    }

    // bool aesProcess =false ,encrypt = false,decrypt = false;

    // // //Get Plain Text and
    time_t start,end;
    
    auto obj = NewAes(keySize,keyStr,textStr);
    obj->En_De();
    obj->PrintState();
    return 0;
}

