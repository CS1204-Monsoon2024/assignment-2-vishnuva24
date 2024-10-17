#include <iostream>
#include <vector>
using namespace std;

class HashTable {
    private:
        int size;
        int* arr;
        int capacity;
        int hash(int key, int size){
            return key % size;
        }

    public:
        HashTable(int initialSize){
            capacity = initialSize;
            size = 0;
            arr = new int[capacity];
            for (int i=0; i<capacity; i++){
                arr[i] = -1;
            }
        }
        
        void insert(int key){
            if (size >= 0.8 * capacity){
                resizeTable();
            }
            int index = hash(key, capacity);
            if (arr[index]==-1){
                arr[index] = key;
                size++;
                return;
            }
            else{
                for (int i=1; i< capacity/2; i++){
                    int index2 = (index + i*i)%size;
                    if (arr[index2]==-1){
                        arr[index2] = key;
                        size++;
                        return;
                    }
                }
            }

        }

        void remove(int key){
            int index = hash(key, capacity);
            if (arr[index]==key){
                arr[index] = -1;
                size--;
            }
            else{
                for (int i=1; i< capacity/2; i++){
                    int index2 = (index + i*i)%size;
                    if (arr[index2]==key){
                        arr[index2] = -1;
                        size--;
                        return;
                    }
                }
            }

        }
        bool isPrime(int num) {
            if (num <= 1) return false; 
            for (int i = 2; i*i <= num; i++){
                if (num%i==0){
                    return false;
                }
            }
            return true;
        }

        int primeGreaterThan(int num){
            int i = num+1;

            while (true){
                if (isPrime(i)){
                    return i;
                }
                i++;
            }
        }

        void resizeTable(){
            int updatedSize = primeGreaterThan(2*size);
            int* updatedArr = new int[updatedSize];
            for (int i=0; i<updatedSize; i++){
                updatedArr[i] = -1;
            }
            for (int i=0; i<size; i++){
                if (arr[i]!=-1){
                    int key = arr[i];
                    int index = hash(key, updatedSize);
                    if (updatedArr[index]==-1){
                        updatedArr[index] = key;
                    }
                    else{
                        for (int j=1; j<updatedSize; j++){
                            int index2 = (index + j*j)%updatedSize;
                            if (updatedArr[index2] == -1){
                                updatedArr[index2] = key;
                                break;
                            }
                        }
                    }
                }
            }
            delete[] arr;
            arr = updatedArr;
            size = updatedSize;
        }
        int search(int key){
            int index = hash(key, capacity);
            if (arr[index]==key){
                return index;
            }
            else{
                for (int i=1; i< capacity/2; i++){
                    int index2 = (index + i*i)%size;
                    if (arr[index2]==key){
                        return index2;
                    }
                }
            }
            return -1;
        }
        
        void printTable(){
            for (int i=0; i<capacity; i++){
                if (arr[i]==-1){
                    cout << "- " ;
                }
                else{
                    cout << arr[i] << " " ;
                }
            }
            cout << endl;   
        }
};