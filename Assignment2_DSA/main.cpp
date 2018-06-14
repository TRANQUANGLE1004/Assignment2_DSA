#include <iostream>
#include<functional>
#include "dsaLib.h"
#include "requestLib.h"
#include "dbLib.h"

using namespace std;

bool processRequest(VRequest& request, L1List<VRecord>& recList, void* pGData);
bool initVGlobalData(void** pGData);
void releaseVGlobalData(void* pGData);

int main(int narg, char** argv) {
    L1List<VRequest>  reqList;
    L1List<VRecord>   recDB;// database of records
    void*             pGData;
	char request[] = "request.txt";
	char recDb[] = "sampleData.dat";
    loadRequests(request, reqList);
    loadVDB(recDb, recDB);

    cout << fixed << setprecision(12);// preset for floating point numbers
    /// Process events
    if (initVGlobalData(&pGData)) {
        clog << "Successfully initialize data\n";
    }
    else {
        clog << "Failed to initialize data\nExiting...\n";
        return -1;
    }

    while (!reqList.isEmpty()) {
        if (!processRequest(reqList[0], recDB, pGData))
            cout << "Failed to process the request\n";
        reqList.removeHead();
    }

    cout << resetiosflags(ios::showbase) << setprecision(-1);
    /// Release any global allocaed data
    releaseVGlobalData(pGData);
	system("pause");
    return 0;
}

//struct inta {
//	int x;
//	inta(int a) :x(a) {};
//};
//
//void print(inta &a) {
//	cout << a.x << " ";
//}
//
//int main() {
//	AVLTree<inta> avl;
//	avl.insert(10);
//	avl.insert(7);
//	avl.insert(12);
//	avl.insert(4);
//	avl.insert(8);
//	avl.insert(9);
//	cout << "NLR :"; avl.traverseNLR(&print); cout << '\n';
//	cout << "LNR :"; avl.traverseLNR(&print);
//	system("pause");
//	return 0;
//}