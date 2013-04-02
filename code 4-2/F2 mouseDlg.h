
// F2 mouseDlg.h : header file
//

#pragma once
#define ALPHA_KEY_NO 26
#define KEY_SIZE 40
#define KEY_DISTANCE 50
#define KEY_AREA_X0 15
#define KEY_AREA_Y0 60 
#define KEY_AREA_LENGTH 752
#define KEY_AREA_WIDTH 230
#define WORD_MAX_LENGTH 100

#include <vector>
#include "afxwin.h"
using namespace std;
class StrokePoint 
{
public:
	double x;
	double y;
	double time;
};
typedef vector<StrokePoint> Stroke;

class Key
{
public:
    CString letter;
	int size;
	CPoint location;
	bool inKey(CPoint);
};

// CF2mouseDlg dialog
class CF2mouseDlg : public CDialogEx
{
// Construction
public:
	CF2mouseDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_F2MOUSE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	bool mouseflag;
	double m_xpos;
	double m_ypos;
	double m_time;
	CPoint m_oldpoint;
	Stroke stroke;	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	CPoint m_tpos;
//	double m_tposX;
//	double m_tposY;
	CRect m_tcontrol;
	afx_msg void OnBnClickedPostest1();
	afx_msg void OnBnClickedPostest2();

	CString m_word;
	CString m_letter;
	bool m_lockkey;
	int m_lockno;
	Key m_keys[ALPHA_KEY_NO];
	CString m_alphebet[ALPHA_KEY_NO];
	void drawKeyboard(CF2mouseDlg * backgroud);
	//void drawSingleKey(CPaintDC dc,Key key, bool flag);
//	CEdit m_showword;
};
