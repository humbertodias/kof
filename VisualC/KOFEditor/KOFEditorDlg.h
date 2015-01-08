
// KOFEditorDlg.h : ͷ�ļ�
//

#pragma once

#include <structs.h>
#include "afxcmn.h"
// CKOFEditorDlg �Ի���
class CKOFEditorDlg : public CDialogEx
{
// ����
public:
	CKOFEditorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_KOFEDITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	int m_pos;

	SFFFile m_sfffile;
	PaletteFormat m_commonPal;
	Uint8* DecodePcx(Uint8* PcxByte,PCXHEADER header);
	void PareseSff(CString &file);
	void SaveAllSpr();

	void ClearRender();
	void DrawSprByIndex(int index);
	void RLEData(Uint8* data,  PCXHEADER* header, Uint8** destdata, int* destlength);
	void ScaleSpr(int pos, float scale);
	void DrawSliderSpr();
	void ClearSff();
	void PostNcDestroy();

// ʵ��
protected:
	HICON m_hIcon;
	SDL_Renderer* m_render;
	SDL_Texture* m_texture;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpenfile();
	afx_msg void OnNMCustomdrawSliderSpr(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_Slider;
	afx_msg void OnBnClickedBtnSavescale();
	afx_msg void OnEnChangeEditScale();
	afx_msg void OnBnClickedCheckShowback();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnIddKofeditorDialog();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnScaleall();
};
