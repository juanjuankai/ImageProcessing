
// ImageProcessing.h : ImageProcessing Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CImageProcessingApp:
// �йش����ʵ�֣������ ImageProcessing.cpp
//

class CImageProcessingApp : public CWinApp
{
public:
	CImageProcessingApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CImageProcessingApp theApp;
