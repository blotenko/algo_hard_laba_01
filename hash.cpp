//
//  hash.cpp
//  hash_string
//
//  Created by Blotenko on 25.01.2022.
//

#include <time.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <stdio.h>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::list;
using std::string;

typedef long long int long_int;
const int max_int = 1000000001; 
int stringHash(string str);

inline int hash(long_int a_prime, long_int b_prime, int p_prime, int table_size, int key)
{
    return (((a_prime * key + b_prime) % p_prime) % table_size);
}
class Bucket
{
    vector<int> _cells;
    int size;
    long_int hash_a;
    long_int hash_b;
    int prime;

public:
    Bucket() {}
    void Initialize()
    {
        prime = 17;
        hash_a = std::rand() % prime;
        hash_b =  1 + std::rand() % (prime - 1);
    }

    void Construct(list<int>& input)
    {
        if (input.empty())
        {
            size = 0;
            return;
        }

        size = input.size() * input.size();
        bool flag = true;

        // while there is no collisions in table
        while (flag)
        {
            _cells.assign(size, max_int);
            Initialize();
            list<int>::iterator elem = input.begin();
            while (elem != input.end() && flag)
            {
                int hashKey = hash(hash_a, hash_b, prime, size, *elem);
                if (hashKey < 0)
                    hashKey = - hashKey;

                // if collision then construct hash table from the begining!
                if (_cells[hashKey] != max_int)
                {
                    flag = false;
                    break;
                }
                _cells[hashKey] = *elem;
                ++elem;
            }

            if (!flag)
                flag = true;
            else
                flag = false;
        }
    }

    bool Contains(int elem)
    {
        if (size == 0)
            return false;
        int hashKey = hash(hash_a, hash_b, prime, size, elem);
        if (hashKey < 0)
            hashKey = - hashKey;
        if (_cells[hashKey] == elem)
            return true;
        return false;
    }
};

class FixedSet
{
    int _tableSize;
    long_int _hashFuncA;
    long_int _hashFuncB;
    int _primeNumber;
    vector<list<int> > _elementsInCells;
    vector<Bucket> _buckets;

public:
    FixedSet()
    {
        _primeNumber = 100013; // the maximum prime number
        _hashFuncA = std::rand() % _primeNumber;
        _hashFuncB =  1 + std::rand() % (_primeNumber - 1);
    }

    void setTableSize(int size)
    {
        _tableSize = size;
        _buckets.resize(size);
    }

    void Initialize(const vector<string>& numbers)
    {
        _tableSize = numbers.size();
        _buckets.resize(numbers.size());
        _elementsInCells.resize(numbers.size());
        for (int i = 0; i < numbers.size(); ++i)
        {
            int hashKey = hash(_hashFuncA, _hashFuncB, _primeNumber, _tableSize, stringHash(numbers[i]));
            if (hashKey < 0)
                hashKey = - hashKey;
            _elementsInCells[hashKey].push_back(stringHash(numbers[i]));
        }
        for (int i = 0; i < numbers.size(); ++i)
        {
                _buckets[i].Construct(_elementsInCells[i]);
        }
    }

    bool Contains(string number)
    {
        for(int i = 0; i<_buckets.size();i++)
        {
            cout<< &_buckets[i]<<" ";
        }
        cout<<endl;
        
        return _buckets[1].Contains(stringHash(number));
    }
};


int stringHash(string str){
    int num=0;
    for(int i = 0; i<str.size();i++)
    {
        num += (int)str[i];
    }
    return num;
}

int main(int argc, char* argv[])
{
    int numberOfElements;
    scanf("%i", &numberOfElements);

    FixedSet fs;
    vector<string> inputVector;
    fs.setTableSize(numberOfElements);

    for (int i = 0; i < numberOfElements; ++i)
    {
        string elemValue;
        cin>>elemValue;

        inputVector.push_back(elemValue);
    }

    fs.Initialize(inputVector);
    fs.Contains("1");



    return 0;
}
