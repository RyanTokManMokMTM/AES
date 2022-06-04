#include<iostream>
#include <vector>
#include <fstream>
#include "time.h"
#include "aes.cpp"

AES* NewAes(int keySize,std::string &aesKey,std::string &plainText,std::string& encrypteFile,std::string& decrypteFile,bool mode){
    return new AES(keySize,aesKey,plainText,encrypteFile,decrypteFile,mode);
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

void Start(){


    std::cout<<"     _      _____   ____      ____    _                    ____                                      _" << std::endl; 
    std::cout<<"    / \\    | ____| / ___|    |  _ \\  | |   __ _   _   _   / ___|  _ __    ___    _   _   _ __     __| |" << std::endl; 
    std::cout<<"   / _ \\   |  _|   \\___ \\    | |_) | | |  / _` | | | | | | |  _  | '__|  / _ \\  | | | | | '_ \\   / _` |" << std::endl; 
    std::cout<<"  / ___ \\  | |___   ___) |   |  __/  | | | (_| | | |_| | | |_| | | |    | (_) | | |_| | | | | | | (_| |" << std::endl; 
    std::cout<<" /_/   \\_\\ |_____| |____/    |_|     |_|  \\__,_|  \\__, |  \\____| |_|     \\___/   \\__,_| |_| |_|  \\__,_|" << std::endl; 
    std::cout<<"                                                  |___/                                                " << std::endl; 
    std::cout<<"                                Welcome to AES Algorithm Playground(128/192/256)                                    " << std::endl;
}

int main(int argc,char **argv){
    std::string keyFilePath,textFilePath,EncryptedFilePath,DecryptedFilePath;
    std::string outputName;
    bool isMode = false;
    Start();    

    printf("\n");
    std::cout << "Enter key file path: ";
    std::cin >> keyFilePath;

    std::cout << "Enter text file path: ";
    std::cin >> textFilePath;

    std::cout << "Enter encrypted file path: ";
    std::cin >> EncryptedFilePath;
 
    std::cout << "Enter decrypted file path: ";
    std::cin >> DecryptedFilePath;

    std::cout << "AES Detail Mode? (Yes:1/No:0): ";
    std::cin >> isMode;

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
    auto aesObj = NewAes(keySize,keyStr,textStr,EncryptedFilePath,DecryptedFilePath,isMode);
    int selected = -1;
    do{
        std::cout << "AES Main menu\n";
        std::cout << "1. Encryption only\n";
        std::cout << "2. Decryption only\n";
        std::cout << "3. Encryption and Decryption\n";
        std::cout << "0. Quit\n";
        std::cin >> selected;

        switch (selected)
        {
        case 1:
            aesObj->Encrypt();
            break;
        case 2:
            aesObj->Decrypt();
            break;
        case 3:
            aesObj->En_De();
            break;
        case 0:
            std::cout << "Exited\n";
            break;
        
        default:
            exit(1);
            break;
        }
    }while(selected != 0);

    delete aesObj;
    return 0;
}

