/*
 * com.cpp
 *
 *  Created on: 2018年8月12日
 *      Author: Administrator
 */

#include <Windows.h>
#include "com.h"

using namespace std;

MyCom::MyCom(
			const string portNum,                   //串口号
			DWORD boudrate,	                   //波特率
			BYTE  byteSize,				           //数据位
			BYTE parityBit,				   //校验位
			BYTE stopBit                //停止位
			):comNum(portNum),
			myBoudRate(boudrate)
{

}
/**
 * 打开串口
 */
bool MyCom::opencom()
{
	myCom = CreateFile(comNum.c_str(),
			GENERIC_READ |GENERIC_WRITE,0, NULL, OPEN_EXISTING,
			0, NULL);
	if( INVALID_HANDLE_VALUE  == myCom )    //串口打开失败
	{
		return false;
	}
	SetupComm(myCom, bufferSize,bufferSize);      //设置读写缓存区大小

	/***配置串口**/
	DCB dcb;
	GetCommState(myCom, &dcb);                 //获取原有配置
	dcb.DCBlength = sizeof(dcb);
	dcb.BaudRate = myBoudRate;
	dcb.StopBits = ONESTOPBIT;
	dcb.Parity = 0;
	dcb.ByteSize = 8;                      //数据位
	if( !SetCommState(myCom, &dcb) )
	{
		return false;
	}
	//清空缓存区
	PurgeComm(myCom, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_TXABORT | PURGE_RXABORT);
	isOpen = true;
	return true;
}

/**
 * close com
 */
bool MyCom::closeCom()
{
	{
		return false;
	}
	isOpen = false;
	CloseHandle(myCom);
	myCom = INVALID_HANDLE_VALUE;
}

/**
 * send data to com
 * data: witch will write to com
 * err:
 *     -1: com has not open
 *     -2: can't write data to com
 * dwLength: length of data
 */
bool MyCom::writeToComm(const BYTE data[], DWORD dwLength)
{

	DWORD dwError = 0;
	if(isOpen == false )           //未打开串口
	{
		return false;
	}
	if (ClearCommError(myCom, &dwError, NULL) && dwError > 0)
	{
		PurgeComm(myCom, PURGE_TXABORT | PURGE_TXCLEAR);
	}

	DWORD dwTx = 0;                //写入的字节数
	bool ret = false;
	ret = WriteFile(myCom, data, dwLength, &dwTx, NULL);

	if( ret == false )
	{
		return false;
	}
	return true;
}

/**
 * get data from com
 * buffer: save data from com
 * dwlength: length of buffer from com
 *
 */
bool MyCom::readFromCom(char buffer[], DWORD dwLength)
{
	getByteCom(buffer[0]);
}

/**
 * get one byte from com
 * data: one byte from com
 */
bool MyCom::getByteCom(char &data)
{
	DWORD dwRx = 0;		// 读入的字节数
	return ReadFile(myCom, &data, 1 , &dwRx, NULL);	// 读入数据
}

