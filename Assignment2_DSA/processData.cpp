/*
 * =========================================================================================
 * Name        : processData.cpp
 * Description : Student code for Assignment 2 - Data structures and Algorithms - Spring 2018
 * =========================================================================================
 */
#include "requestLib.h"
#include "dbLib.h"
/// Initialize and Finalize any global data that you use in the program


void convertLListToAvlLat(L1List<VRecord>& recList,AVLTree<VRecord>*& recAvl) {
	L1Item<VRecord>* temp = recList.getFirstPointer();
	while (temp != NULL) {
		recAvl->insertx(temp->data);
		temp = temp->pNext;
	}
}

void convertLListToAvlLong(L1List<VRecord>& recList, AVLTree<VRecord>*& recAvl) {
	L1Item<VRecord>* temp = recList.getFirstPointer();
	while (temp != NULL) {
		recAvl->inserty(temp->data);
		temp = temp->pNext;
	}
}

void printx(VRecord &a) {
	cout << a.x << endl;
}
void printy(VRecord &a) {
	cout << a.y << endl;
}
bool initVGlobalData(void** pGData) {
    // TODO: allocate global data if you think it is necessary.
    /// pGData contains the address of a pointer. You should allocate data for the global data
    /// and then assign its address to *pGData
    return true;
}
void releaseVGlobalData(void* pGData) {
    // TODO: release the data if you finish using it
}

bool processRequest(VRequest& request, L1List<VRecord>& recList, void* pGData) {
    // TODO: Your code comes here
	AVLTree<VRecord>* recAvl = new AVLTree<VRecord>;
	convertLListToAvlLong(recList, recAvl);
	recAvl->traverseLNR(&printy);
    /// NOTE: The output of the request will be printed on one line
    /// end by the end-line '\n' character.
    return true;
}

