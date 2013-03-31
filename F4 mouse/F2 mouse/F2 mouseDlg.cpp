
// F2 mouseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "F2 mouse.h"
#include "F2 mouseDlg.h"
#include "afxdialogex.h"

#include<iostream>
#include<fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CF2mouseDlg dialog



CF2mouseDlg::CF2mouseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CF2mouseDlg::IDD, pParent)
	, mouseflag(FALSE)
	, m_lockkey(FALSE)
	, m_lockno(0)
	, m_xpos(0)
	, m_ypos(0)
	, m_time(0)
	, m_oldpoint(0)
	//, m_tposX(0)
	//, m_tposY(0)
	, m_tpos(0,0)
	, m_word(_T(""))
	, m_letter(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	for(int i=0;i<ALPHA_KEY_NO;i++)
	{
		m_alphebet[i].Format(_T("%c"),'a'+i);        //more to fix here CString str.Format(_T("%d"),number);
	}		
}

void CF2mouseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_X, m_xpos);
	DDX_Text(pDX, IDC_Y, m_ypos);
	//  DDX_Text(pDX, IDC_tposX, m_tposX);
	//  DDX_Text(pDX, IDC_tposY, m_tposY);
	//  DDX_Control(pDX, IDC_word, m_showword);
}

BEGIN_MESSAGE_MAP(CF2mouseDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_POSTEST1, &CF2mouseDlg::OnBnClickedPostest1)
	ON_BN_CLICKED(IDC_POSTEST2, &CF2mouseDlg::OnBnClickedPostest2)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CF2mouseDlg message handlers

BOOL CF2mouseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CF2mouseDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CF2mouseDlg::OnPaint()
{
	//draw keys on keyboard
    drawKeyboard(this);
	if (IsIconic())
	{
		//original part draw mouse cursor
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CF2mouseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CF2mouseDlg::OnBnClickedPostest1()
{
	// TODO: Add your control notification handler code here
	//UpdateData();
	/*
	GetDlgItem(IDC_POSTEST1)->GetWindowRect(&m_tcontrol);
	m_tpos=m_tcontrol.CenterPoint();
	m_tposX=m_tpos.x;
	m_tposY=m_tpos.y;
	UpdateData(FALSE);*/
	MessageBox(_T("按下鼠标拖动模拟键盘输入，如果到键盘区以外就会终止，键盘区域信息和轨迹信息参见exe同目录下的txt文件"));
}

void CF2mouseDlg::OnBnClickedPostest2()
{
	// TODO: Add your control notification handler code here
	//UpdateData();
	MessageBox(_T("晗哥靠你了"));
	//UpdateData(FALSE);
}

void CF2mouseDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//HWND hDlg=this->GetSafeHwnd();
	StrokePoint spoint;
    CDC *pdc=GetDC();
	CPen pen(PS_SOLID,1,RGB(255,0,0));
	CPen *pOldPen=pdc->SelectObject(&pen);
	COLORREF cf = RGB(0,255,0);
    bool inregion=FALSE;
	if(point.x>=KEY_AREA_X0&&point.x<=KEY_AREA_X0+KEY_AREA_LENGTH
		&&point.y>=KEY_AREA_Y0&&point.y<=KEY_AREA_Y0+KEY_AREA_WIDTH)
	   inregion=TRUE;
			
	if(!inregion&&mouseflag)
	{
	  // MessageBox(m_word);
	   mouseflag=FALSE;
       m_xpos=0;
       m_ypos=0;
	   UpdateData(FALSE);
       //m_word=(_T(""));
       //m_letter=(_T(""));
	   Invalidate();
	 }

	if(mouseflag&&inregion)
	{
		  //record point
	      m_xpos=point.x;
	      m_ypos=point.y;
		  m_time++;
		  spoint.x=m_xpos;
		  spoint.y=m_ypos;
		  spoint.time=m_time;
		  stroke.push_back(spoint);
          SetDlgItemText(IDC_word, m_word) ;
	      UpdateData(FALSE);

		  //read keys method 1	
		  /*
		  for(int i=0;i<ALPHA_KEY_SIZE;i++)
		  {
			  if(m_keys[i].inKey(point)&&m_lockkey==FALSE)
			  {
				  pdc->FillSolidRect(m_keys[i].location.x,m_keys[i].location.y, m_keys[i].size,m_keys[i].size,cf);
				  m_letter=m_keys[i].letter;
				  m_lockkey=TRUE;
				  m_lockno=i;
				  break;
			  }
		  }
		  if(!m_keys[m_lockno].inKey(point)&&m_lockkey==TRUE)
		  {
				  m_word=m_word+m_letter;
				  m_letter=(_T(""));
				  m_lockkey=FALSE;
				  m_lockno=0;
		  }*/

		  //read keys method 3		  
		  for(int i=0;i<ALPHA_KEY_NO;i++)
		  {
			  if(m_keys[i].inKey(point)&&m_lockkey==FALSE)
			  {
				  pdc->FillSolidRect(m_keys[i].location.x,m_keys[i].location.y, m_keys[i].size,m_keys[i].size,cf);
				  pdc->TextOut(m_keys[i].location.x,m_keys[i].location.y,m_keys[i].letter);
				  m_letter=m_keys[i].letter;
				  m_word=m_word+m_letter;
				  m_lockkey=TRUE;
				  m_lockno=i;
				  break;
			  }
		  }
		  if(!m_keys[m_lockno].inKey(point)&&m_lockkey==TRUE)
		  {	
				  m_letter=(_T(""));
				  m_lockkey=FALSE;
				  m_lockno=0;
		  }
		  //if(int(m_time)%30==0)
			//  m_lockkey=FALSE;

		  //read keys method 2
		  /*
		  for(int i=0;i<ALPHA_KEY_SIZE;i++)
		  {
			  if(m_keys[i].inKey(point)&&m_lockkey==FALSE)
			  {
				  pdc->FillSolidRect(m_keys[i].location.x,m_keys[i].location.y, m_keys[i].size,m_keys[i].size,cf);
				  m_letter=m_keys[i].letter;
				  m_word=m_word+m_letter;
				  m_letter=(_T(""));
				  m_lockkey=TRUE;
				  //m_lockno=i;
				  break;
			  }
		  }
		  m_lockno++;
		  if(m_lockno>=10)
		  {
			  m_lockno=0;
			  m_lockkey=FALSE;
		  }*/
	        
		  //draw gesture
		  pdc->MoveTo(m_oldpoint);
		  pdc->LineTo(point);
		  m_oldpoint=point;
	}    
	ReleaseDC(pdc);
	DeleteObject(pOldPen);
	CDialogEx::OnMouseMove(nFlags, point);
}

void CF2mouseDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	mouseflag=TRUE;
    m_oldpoint=point;
	CDialogEx::OnLButtonDown(nFlags, point);

	//
    //read keys method 2
	/*
   CDC *pdc=GetDC();
   for(int i=0;i<ALPHA_KEY_SIZE;i++)
   {
	   if(m_keys[i].inKey(point))
	   {
				//  pdc->FillSolidRect(m_keys[i].location.x,m_keys[i].location.y, m_keys[i].size,m_keys[i].size,cf);
				  m_letter=m_keys[i].letter;
				  m_word=m_word+m_letter;
				  m_letter=(_T(""));
				  //m_lockno=i;
				  break;
	   }
	}
    m_lockno++;
    if(m_lockno>=30)
    {
		 m_lockno=0;
		 //m_lockkey=FALSE;
    }
	pdc->TextOut(200,200,m_word);*/
}

void CF2mouseDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//CDC *pdc=GetDC();
	//pdc->TextOut(200,200,m_word);
	char writeword[WORD_MAX_LENGTH]="0";
	for(int i=0;i<m_word.GetLength();i++)
		writeword[i]=(char)m_word.GetAt(i);
//	MessageBox(m_word);
	mouseflag=FALSE;
	m_xpos=0;
	m_ypos=0;
	UpdateData(FALSE);
	m_word=(_T(""));
	m_letter=(_T(""));
	Invalidate(); //InvalidateRgn();
	CDialogEx::OnLButtonUp(nFlags, point);

	char const filename[]="letter and stroke data.txt";
    ofstream o_file;
    o_file.open(filename);
	o_file<<"letter is:";
	o_file<<writeword<<endl;
    o_file<<"x pos"<<"      "<<"y pos"<<"     "<<"time"<<"     "<<endl;
    for(int i=0;i<m_time;i++)
    {
	   o_file<<stroke.at(i).x<<"     "<<stroke.at(i).y<<"     "<<stroke.at(i).time<<"     "<<endl;
    }
    o_file.close();
}



void CF2mouseDlg::drawKeyboard(CF2mouseDlg * background)
{
	//set key information 
	for(int index=0;index<10;index++)
	{
		m_keys[index].letter=m_alphebet[index];
		m_keys[index].size=KEY_SIZE;
		m_keys[index].location.x=KEY_AREA_X0+20+index*KEY_DISTANCE;
		m_keys[index].location.y=KEY_AREA_Y0+20;
	}
	for(int index=10;index<20;index++)
	{
		m_keys[index].letter=m_alphebet[index];
		m_keys[index].size=KEY_SIZE;
		m_keys[index].location.x=KEY_AREA_X0+20+(index-10)*KEY_DISTANCE;
		m_keys[index].location.y=KEY_AREA_Y0+KEY_DISTANCE+20;
	}
	for(int index=20;index<ALPHA_KEY_NO;index++)
	{
		m_keys[index].letter=m_alphebet[index];
		m_keys[index].size=KEY_SIZE;
		m_keys[index].location.x=KEY_AREA_X0+20+(index-20)*KEY_DISTANCE+2*(KEY_DISTANCE);
		m_keys[index].location.y=KEY_AREA_Y0+KEY_DISTANCE*2+20;
	}

	//draw alphabetical keysCRect rect;
	CPaintDC dc(background); 
	HBRUSH hB;
	dc.Rectangle(KEY_AREA_X0,KEY_AREA_Y0,KEY_AREA_X0+KEY_AREA_LENGTH,KEY_AREA_Y0+KEY_AREA_WIDTH);
	hB=CreateSolidBrush(RGB(0,0,255));
	SelectObject(dc,hB);
	dc.SetBkColor(RGB(0,0,255));
	for(int i=0;i<ALPHA_KEY_NO;i++)
	{
	   Rectangle(dc,m_keys[i].location.x,m_keys[i].location.y,m_keys[i].location.x+m_keys[i].size,m_keys[i].location.y+m_keys[i].size);
	   dc.TextOut(m_keys[i].location.x,m_keys[i].location.y,m_keys[i].letter);
	}
    DeleteObject(hB);
	/*
	CDC *pdc=GetDC();
	CPen pen(PS_SOLID,1,RGB(255,0,0));
	CPen *pOldPen=pdc->SelectObject(&pen);
	for(int i=0;i<ALPHA_KEY_NO;i++)
	{
	   pdc->Rectangle(m_keys[i].location.x,m_keys[i].location.y,m_keys[i].location.x+m_keys[i].size,m_keys[i].location.y+m_keys[i].size);
	}
	ReleaseDC(pdc);*/
	//get keyborad locations
	char const filename[]="key borad locations.txt";
    ofstream o_file;
    o_file.open(filename);
	o_file<<"key area lefttop (15,60)"<<endl;
	o_file<<"key area right_bottom (15+752,60+230)"<<endl;
	o_file<<"Current key number 26"<<endl;
	o_file<<"all keys are square and size is 40 pixel units"<<endl;
    o_file<<"key index"<<"      "<<"key letter"<<"     "<<"key_top_x"<<"     "<<"key_top_y"<<endl;
    for(int i=0;i<ALPHA_KEY_NO;i++)
    {
		o_file<<i<<"     "<<(char)m_keys[i].letter.GetAt(0)<<"     "<<m_keys[i].location.x<<"     "<<m_keys[i].location.y<<"     "<<endl;
    }
    o_file.close();
}

/*void CF2mouseDlg::drawSingleKey( CPaintDC dc, Key key, bool flag)
{
	//CPaintDC dc(background); 
	HBRUSH hB;
	if(flag==TRUE)
	    hB=CreateSolidBrush(RGB(0,0,255));
	else
		hB=CreateSolidBrush(RGB(255,0,0));
	SelectObject(dc,hB);
	Rectangle(dc,key.location.x,key.location.y,key.location.x+key.size,key.location.y+key.size);
	DeleteObject(hB);
}*/

bool Key::inKey(CPoint mp)
{
	if(mp.x>=location.x&&mp.x<=location.x+size&&mp.y>=location.y&&mp.y<=location.y+size)
		return TRUE;
	else
	    return FALSE;
}