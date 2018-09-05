/*
 * com.h
 *
 *  Created on: 2018年8月12日
 *      Author: Administrator
 */

#ifndef COM_H_
#define COM_H_
#include <windows.h>
#include <iostream>


class MyCom{
public:
	MyCom(
			const std::string portNum ,                   //串口号
			DWORD boudrate = 9600,	                   //波特率
			BYTE  byteSize = 8,				           //数据位
			BYTE parityBit = NOPARITY,				   //校验位
			BYTE stopBit   = ONESTOPBIT                //停止位
			);
	bool opencom();              //打开端口
	bool closeCom();             //关闭端口
	bool writeToComm(const BYTE data[], DWORD dwLength);	   //发送数据
	bool readFromCom(char buffer[], DWORD dwlength);  //读取数据

private:
	HANDLE myCom;                               //通信设备句柄
	std::string comNum;                             //串口号
	DWORD  bufferSize = 1024;                   //缓存区大小
	DWORD  myBoudRate;                   //波特率
	bool   isOpen = false;

	bool getByteCom(char& data);                     //从串口中读取一个字节
};



#endif /* COM_H_ */
