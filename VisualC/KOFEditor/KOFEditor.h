
// KOFEditor.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CKOFEditorApp:
// �йش����ʵ�֣������ KOFEditor.cpp
//

class CKOFEditorApp : public CWinApp
{
public:
	CKOFEditorApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CKOFEditorApp theApp;