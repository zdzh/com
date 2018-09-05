/*
 * com.h
 *
 *  Created on: 2018��8��12��
 *      Author: Administrator
 */

#ifndef COM_H_
#define COM_H_
#include <windows.h>
#include <iostream>


class MyCom{
public:
	MyCom(
			const std::string portNum ,                   //���ں�
			DWORD boudrate = 9600,	                   //������
			BYTE  byteSize = 8,				           //����λ
			BYTE parityBit = NOPARITY,				   //У��λ
			BYTE stopBit   = ONESTOPBIT                //ֹͣλ
			);
	bool opencom();              //�򿪶˿�
	bool closeCom();             //�رն˿�
	bool writeToComm(const BYTE data[], DWORD dwLength);	   //��������
	bool readFromCom(char buffer[], DWORD dwlength);  //��ȡ����

private:
	HANDLE myCom;                               //ͨ���豸���
	std::string comNum;                             //���ں�
	DWORD  bufferSize = 1024;                   //��������С
	DWORD  myBoudRate;                   //������
	bool   isOpen = false;

	bool getByteCom(char& data);                     //�Ӵ����ж�ȡһ���ֽ�
};



#endif /* COM_H_ */
