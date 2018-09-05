//============================================================================
// Name        : mycom.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "com.h"
using namespace std;

int main() {
	cout << "comm test" << endl;
	cout << "wait for open comm....."<<endl;

	MyCom mcomm("com6");
	bool ret;
	ret = mcomm.opencom();
	if( ret  == true )
	    cout << "open comm succse"<<endl;
	else
		cout << "open comm false" << endl;
	unsigned char dat[5] ="hell";
	ret = mcomm.writeToComm(dat, sizeof(dat));
	cout << "write to comm " << boolalpha<< ret  << endl;
	cout << "test of read from com" << endl;
	char buffer[10];
	 mcomm.readFromCom(buffer, 10);
	cout << "read from com :" << boolalpha<< ret  << endl;
	cout <<  buffer << endl;
	mcomm.closeCom();
	return 0;
}
