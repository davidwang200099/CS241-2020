#include <cstdlib>
#include <iostream>
using namespace std;

// upper bound on hashtable size
#define MAXN 101
// actual used hashtable size

// number of tables
#define ver 2

int hashtable[ver][MAXN];

// possible positions for a key

/* function to fill hash table with dummy value
 * dummy value: -1
 * number of hashtables: ver */
void initTable() {
    for (int j = 0; j < MAXN; j++)
        for (int i = 0; i < ver; i++)
            hashtable[i][j] = -1;
}

/* return hashed value for a key
 * function: ID of hash function
 * key: item to be hashed */
int myhash(int function, int key, int m) {
    switch (function) {
    case 0:
        return key % m;
    case 1:
        return (key / m) % m;
    }
}

bool place(int key, int n) {
    int m = n + 1;
    int pos = myhash(0, key, m);
    int elem1 = hashtable[0][myhash(0, key, m)];
    int elem2 = hashtable[1][myhash(1, key, m)];
    if (elem1 == key || elem2 == key)
        return true;
    if (elem1 == -1) {
        hashtable[0][pos] = key;
        return true;
    } else {
        int index = 0;
        int elem;
        for (int i = 0; i < n; i++) {
            if ((elem = hashtable[index][myhash(index, key, m)]) == -1) {
                hashtable[index][myhash(index, key, m)] = key;
                return true;
            } else {
                hashtable[index][myhash(index, key, m)] = key;
                key = elem;
                index = !index;
            }
        }
        return false;
    }
}

/* function to print hash table contents */
void printTable(int n) {
    int m = n + 1;
    for (int i = 0; i < ver; i++, std::cout << endl)
        for (int j = 0; j < m; j++)
            (hashtable[i][j] == -1) ? std::cout << "- "
                                    : std::cout << hashtable[i][j] << " ";
}

/* function for Cuckoo-hashing keys
 * keys[]: input array of keys
 * n: size of input array */
void cuckoo(int keys[], int n) {
    // init
    initTable();
    bool flag = true;
    // start with placing every key at its position in
    // the first hash table according to first hash
    // function
    for (int i = 0; i < n; i++)
        if (!place(keys[i], n)) {
            flag = false;
            break;
        }

    // print the final hash tables
    if (flag)
        printTable(n);
    else
        cout << "Failed!" << endl;
}

int main() {
    int keys_1[MAXN];
    // input array size
    int n;
    std::cin >> n;
    // m in hash function
    m = n + 1;
    int i = 0;
    while (i < n) {
        std::cin >> keys_1[i++];
    }
    cuckoo(keys_1, n);

    return 0;
}
