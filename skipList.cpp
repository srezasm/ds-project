// CREDIT: https://gist.github.com/hjy0102/d83518e77b0d01864b8a427b78053bed
// Added Search, and done some refactoring

/*
To compile :
g++ -Wall skiplist.cc -o skiplist
*/

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "utils.h"
#define MAX_LEVEL 6
const float P = 0.5;
using namespace std;

struct SkipList {
    struct SNode {
        float value;
        SNode** forw;

        SNode(int level, float& value) {
            forw = new SNode*[level + 1];
            memset(forw, 0, sizeof(SNode*) * (level + 1));
            this->value = value;
        }

        ~SNode() { delete[] forw; }
    };

    SNode* header;
    float value;
    int level;

    SkipList() : header(new SNode(MAX_LEVEL, value)), level(0) {}
    ~SkipList() { delete header; }

    bool search(float& sValue) {
        SNode* x = header;
        for (int i = level; i >= 0; i--) {
            while (x->forw[i] != NULL && x->forw[i]->value < sValue) {
                x = x->forw[i];
            }
        }
        x = x->forw[0];
        return x != NULL && x->value == sValue;
    }

    void insertElement(float& value) {
        SNode* x = header;
        SNode* update[MAX_LEVEL + 1];
        memset(update, 0, sizeof(SNode*) * (MAX_LEVEL + 1));
        for (int i = level; i >= 0; i--) {
            while (x->forw[i] != NULL && x->forw[i]->value < value) {
                x = x->forw[i];
            }
            update[i] = x;
        }
        x = x->forw[0];
        if (x == NULL || x->value != value) {
            int lvl = randLevel();
            if (lvl > level) {
                for (int i = level + 1; i <= lvl; i++) {
                    update[i] = header;
                }
                level = lvl;
            }
            x = new SNode(lvl, value);
            for (int i = 0; i <= lvl; i++) {
                x->forw[i] = update[i]->forw[i];
                update[i]->forw[i] = x;
            }
        }
    }

    void deleteElement(float& value) {
        SNode* x = header;
        SNode* update[MAX_LEVEL + 1];

        memset(update, 0, sizeof(SNode*) * (MAX_LEVEL + 1));

        for (int i = level; i >= 0; i--) {
            while (x->forw[i] != NULL && x->forw[i]->value < value) {
                x = x->forw[i];
            }
            update[i] = x;
        }

        x = x->forw[0];

        if (x->value == value) {
            for (int i = 0; i <= level; i++) {
                if (update[i]->forw[i] != x)
                    break;
                update[i]->forw[i] = x->forw[i];
            }
            delete x;
            while (level > 0 && header->forw[level] == NULL) {
                level--;
            }
        }
    }

    void display() {
        const SNode* x = header->forw[0];

        while (x != NULL) {
            cout << x->value;
            x = x->forw[0];
            if (x != NULL)
                cout << " - ";
        }

        cout << endl;
    }

   private:
    float fRand() { return (float)rand() / RAND_MAX; }

    int randLevel() {
        static bool first = true;

        if (first) {
            srand((unsigned)time(NULL));
            first = false;
        }

        int lvl = (int)(log(fRand()) / log(1. - P));
        return lvl < MAX_LEVEL ? lvl : MAX_LEVEL;
    }
};

void initSkipList(int n, SkipList** slistRef) {
    *slistRef = new SkipList();
    for (int i = 0; i < n; i++) {
        float rndVal = randomFloat();
        (*slistRef)->insertElement(rndVal);
    }
}

bool searchSkipList(float& value, SkipList* slist) {
    return slist->search(value);
}

/*
 * Main: Contains Menu
 */
// int main() {
//     SkipList ss;
//     float n;
//     int choice;

//     cout << endl << "-----------------------" << endl;
//     cout << endl << "Operations on Skip list" << endl;
//     cout << endl << "-----------------------" << endl;
//     cout << "1.Insert Element" << endl;
//     cout << "2.Delete Element" << endl;
//     cout << "3.Search Element" << endl;
//     cout << "4.Display List " << endl;
//     cout << "5.Exit " << endl;
//     cout << "6. Search " << endl;
//     while (1) {
//         cout << "Enter your choice : ";
//         cin >> choice;
//         switch (choice) {
//             case 1:
//                 cout << "Enter the element to be inserted: ";
//                 cin >> n;
//                 ss.insertElement(n);
//                 if (ss.contains(n))
//                     cout << "Element Inserted" << endl;
//                 break;
//             case 2:
//                 cout << "Enter the element to be deleted: ";
//                 cin >> n;
//                 if (!ss.contains(n)) {
//                     cout << "Element not found" << endl;
//                     break;
//                 }
//                 ss.deleteElement(n);
//                 if (!ss.contains(n))
//                     cout << "Element Deleted" << endl;
//                 break;
//             case 3:
//                 cout << "Enter the element to be searched: ";
//                 cin >> n;
//                 if (ss.contains(n))
//                     cout << "Element " << n << " is in the list" << endl;
//                 else
//                     cout << "Element not found" << endl;
//             case 4:
//                 cout << "The List is: ";
//                 ss.display();
//                 break;
//             case 5:
//                 exit(1);
//                 break;
//             case 6:
//                 cout << "Enter the element to be searched: ";
//                 cin >> n;
//                 if (ss.search(n))
//                     cout << "Element " << n << " is in the list" << endl;
//                 else
//                     cout << "Element not found" << endl;
//                 break;
//             default:
//                 cout << "Wrong Choice" << endl;
//         }
//     }
//     return 0;
// }