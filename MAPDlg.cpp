// MAPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MAP.h"
#include "MAPDlg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMAPDlg dialog

CMAPDlg::CMAPDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMAPDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMAPDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//绘制多边形的点数组,添加数据的初始化
	CPoint temp(0,0);
	for (int i=0;i<140;i++)
	{
		m_point[i]=temp;
	}
	
    n_point[0]=temp;
	n_point[1]=temp;
	n_point[2]=temp;
	tem_point=temp;
	pall=CPoint(20,25);
	int choice =0;
	draw_type="A"; //默认开始画圆弧

	order=0;
	fs=0;
	kk=0;
	begin=1;
}

void CMAPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMAPDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMAPDlg, CDialog)
	//{{AFX_MSG_MAP(CMAPDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()


	ON_WM_LBUTTONDOWN()			//响应鼠标左键按下
	ON_WM_LBUTTONUP()			//响应鼠标左键放开
	ON_WM_MOUSEMOVE()			//响应鼠标移动

	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON_LINE, OnButtonLine)
	ON_BN_CLICKED(IDC_BUTTON_POINT, OnButtonPoint)
	ON_BN_CLICKED(IDC_BUTTON_RECT, OnButtonRect)
	ON_BN_CLICKED(IDC_BUTTON_ARC, OnButtonArc)
	ON_BN_CLICKED(IDC_BUTTON_PLINE, OnButtonPline)
	ON_BN_CLICKED(IDC_BUTTON_IN_OR_OUT, OnButtonInOrOut)
	ON_BN_CLICKED(IDC_BUTTON_INTER, OnButtonInter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMAPDlg message handlers

BOOL CMAPDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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

void CMAPDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMAPDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMAPDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//*******************************************************************************************
void DrawPoint(CClientDC &dc,CPoint p0)	//画一个小矩形
{
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//设置透明笔刷
	CBrush* OldBrush=dc.SelectObject(pBrush);
	
	CPoint p1(3,3);
	CPoint p2=(p0-p1);
	CPoint p3=(p0+p1);
	CRect rect(p2,p3);
	dc.Rectangle(&rect);
	
	dc.SelectObject(&OldBrush);
	//dc.SetPixel( p0,RGB(84,84,84) );
}

void DrawRect(CClientDC& dc,CPoint p0,CPoint p1)	
{
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	CBrush* OldBrush=dc.SelectObject(pBrush);
	
	CRect rect(p0,p1);
	dc.Rectangle(&rect);
	
	dc.SelectObject(&OldBrush);
}

void DrawLine(CClientDC &dc,CPoint p0,CPoint p1)  //直线
{
	dc.MoveTo(p0);
	dc.LineTo(p1);
}

//CMAPDlg dlg;

void CMAPDlg::OnButton1() //清除
{
	// TODO: Add your control notification handler code here
	fs=0;
	kk=0;
	order=0;
	Invalidate();	//调用窗口的刷新函数
}

double direction(CPoint a, CPoint b, CPoint c) //画圆弧时使用的用了判断方向的函数
{
	return (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
}
//如果返回值大于0为顺时针，小于0为逆时针。

void DrawMultiArc(CClientDC& dc, CPoint p0,CPoint p1,CPoint p2)		//用三点画弧
{
	int iDirection = direction(p0, p1, p2) > 0 ? AD_CLOCKWISE : AD_COUNTERCLOCKWISE;
	dc.SetArcDirection(iDirection);
	
	int a1=2*(p1.x-p0.x);
	int b1=2*(p1.y-p0.y);
	int c1=p1.x * p1.x+p1.y * p1.y - p0.x * p0.x - p0.y * p0.y;
	int a2=2*(p2.x-p1.x);
	int b2=2*(p2.y-p1.y);
	
	int c2=p2.x*p2.x+p2.y*p2.y-p1.x*p1.x-p1.y*p1.y;
	if((a1*b2)-(a2*b1)==0 
		|| (a1*b2)-(a2*b1)==0 )
		return ;
	double x=((c1*b2)-(c2*b1))/((a1*b2)-(a2*b1));  //之前需要判断除数是否等于零
	double y=((a1*c2)-(a2*c1))/((a1*b2)-(a2*b1));	//圆心坐标
	
	double temp_1=((x-p0.x)*(x-p0.x)+(y-p0.y)*(y-p0.y));	//两点之间的距离的平方，有可能是取了符号的
	
	double temp_2=temp_1>=0 ? temp_1:-temp_1;	//确定用阿里开方的数是正数
	double radius=sqrt(temp_2);			//半径
	//使用分成员函数对公有成员成员数据赋值，需要使用类限定符
	dc.Arc(x-radius , y-radius , x+radius , y+radius , p0.x ,p0.y ,p2.x , p2.y );
}

bool is_PointInRect(const CPoint& p0,const CPoint& TopLeft,const CPoint& BottomRight)//判断点是不是在矩形内部
{
	if(p0.x>TopLeft.x && p0.x<BottomRight.x
		&&p0.y>TopLeft.y && p0.y<BottomRight.y)
		return true;
	else
		return false;
}

//判断直线与与圆弧 的交点  返回交点的个数
int   is_LineAndArc(const CPoint& t1,const CPoint& t2,			//直线的两个点
					const CPoint& p0,const CPoint& p1,const CPoint& p2)//圆弧的三个点
				    
{
	int a1=2*(p1.x-p0.x);
	int b1=2*(p1.y-p0.y);
	int c1=p1.x * p1.x+p1.y * p1.y - p0.x * p0.x - p0.y * p0.y;
	int a2=2*(p2.x-p1.x);
	int b2=2*(p2.y-p1.y);
	
	int c2=p2.x*p2.x+p2.y*p2.y-p1.x*p1.x-p1.y*p1.y;
	if((a1*b2)-(a2*b1)==0 
		|| (a1*b2)-(a2*b1)==0 )
		return 0;
	double x_=((c1*b2)-(c2*b1))/((a1*b2)-(a2*b1));  //之前需要判断除数是否等于零
	double y_=((a1*c2)-(a2*c1))/((a1*b2)-(a2*b1));	//圆心坐标
	
	double temp_1=((x_-p0.x)*(x_-p0.x)+(y_-p0.y)*(y_-p0.y));	//两点之间的距离的平方，有可能是取了符号的
	
	double temp_2=temp_1>=0 ? temp_1:-temp_1;	//确定用阿里开方的数是正数
	double radius=sqrt(temp_2);			//半径
//*************************************************/

	double A,B,C,dist;//距离和系数
	double ange1,ange2;//角度
	double dist1=(t1.x-x_)*(t1.x-x_)+(t1.y-y_)*(t1.y-y_);
	double dist2=(t2.x-x_)*(t2.x-x_)+(t2.y-y_)*(t2.y-y_);
	
	if(  dist1<radius&& dist2<radius )
		return 0;//没有交点
	else if(dist1<radius || dist2<radius)//有一个交点
		return 1;
	else if(t1.x==t2.x)// 直线的一般方程 Ax + By + C = 0; 两个点都在外面
	{
		A=1;
		B=0;
		C=t1.x;
	}
	else if (t1.y==t2.y)
	{
		A=0;
		B=1;
		C=t1.y;
	}
	else
	{
		A=t2.y-t1.y;
		B=t2.x-t1.x;
		C=t2.x* t1.y - t1.x* t2.y;
	}

	dist=abs(A*x_ - B*y_ + C)/( sqrt(A*A+B*B) );	//点到直线的距离
	if(dist>radius)
	return 0;

	ange1=(x_ - t1.x)*(t2.x - t1.x)+(y_ - t1.y)*(t2.y - t1.y);//角度
	ange2=(x_ - t2.x)*(t1.x - t2.x)+(y_ - t2.y)*(t1.y - t2.y);
	if(ange1>0 && ange2>0)
		return 2;
}

//*********************************************************************************
void CMAPDlg::OnLButtonDown()	//左键下去 使用此来获取点的坐标，画图
{
	CPoint pos;				
	GetCursorPos(&pos);		
	ScreenToClient(&pos);	
	
	CRect rc;				
	GetClientRect(rc);		
	if( !rc.PtInRect(pos) )	
		return;				
	CClientDC dc(this);

	CPen PenRed;
	PenRed.CreatePen(  PS_SOLID,1,RGB(255,0,0) );	//红色实线
	CPen * Oldpen=dc.SelectObject(&PenRed);

	switch(choice)
	{
	case 1:
		{
			n_point[0]=pos;	 
			DrawPoint(dc,n_point[0]);
			break;
		}
	case 2:
		{
			m_point[0]=pos;
			fs=1;
			break;
		}
	case 3:			//画多义线
		{	

			if(begin==1 &&  draw_type=="A" && fs==0)	//第一个画圆弧的情况
			{
				DrawPoint(dc,pos);
				m_point[0]=pos;
				order++;
				fs=11;

				CPen PenBlue;
				PenBlue.CreatePen(  PS_SOLID,1,RGB(0,0,255) );	//蓝色实线
				CPen * Oldpen1=dc.SelectObject(&PenBlue);

				DrawPoint(dc,pos+pall);
			
				dc.SelectObject(&Oldpen1);
			}
			else if (begin==1 && draw_type=="A" && fs==11)
			{
				DrawPoint(dc,pos);
				m_point[order++];
				fs=12;
	
				CPen PenBlue;
				PenBlue.CreatePen(  PS_SOLID,1,RGB(0,0,255) );	//蓝色实线
				CPen * Oldpen1=dc.SelectObject(&PenBlue);
				
				DrawPoint(dc,pos+pall);
				
				dc.SelectObject(&Oldpen1);

			}
			else if(begin==1 && draw_type=="L" && fs==0) //第一个画直线
			{
				DrawPoint(dc,pos);
				m_point[0]=pos; 
				order++;
				fs=21;

				CPen PenBlue;
				PenBlue.CreatePen(  PS_SOLID,1,RGB(0,0,255) );	//蓝色实线
				CPen * Oldpen1=dc.SelectObject(&PenBlue);
				
				DrawPoint(dc,pos+pall);
				
				dc.SelectObject(&Oldpen1);
			}
			else if(begin==1 && draw_type=="L" && fs==21)
			{
				DrawPoint(dc,pos);
				m_point[order++]=pos;
				DrawLine(dc,m_point[order-2],m_point[order-1]);
				fs=22;

				CPen PenBlue;
				PenBlue.CreatePen(  PS_SOLID,1,RGB(0,0,255) );	//蓝色实线
				CPen * Oldpen1=dc.SelectObject(&PenBlue);
				
				DrawPoint(dc,pos+pall);
				DrawLine(dc,m_point[order-2]+pall,m_point[order-1]+pall);

				dc.SelectObject(&Oldpen1);

			}
			else if(begin==0 && draw_type=="A" && fs==0)//不是第一个圆弧，只需要再取一个点
			{
				DrawPoint(dc,pos);
				m_point[order++]=pos;
				fs=31;

				CPen PenBlue;
				PenBlue.CreatePen(  PS_SOLID,1,RGB(0,0,255) );	//蓝色实线
				CPen * Oldpen1=dc.SelectObject(&PenBlue);
				
				DrawPoint(dc,pos+pall);
				
				dc.SelectObject(&Oldpen1);
			}
			else if(begin==0 && draw_type=="L" &&fs==0)//不是第一个的直线,点击就直接画直线
			{
				DrawPoint(dc,pos);
				m_point[order++]=pos;
				fs=41;	//鼠标起来的时候，初始化控制变量的值
				DrawLine(dc,m_point[order-2],m_point[order-1]);

				CPen PenBlue;
				PenBlue.CreatePen(  PS_SOLID,1,RGB(0,0,255) );	//蓝色实线
				CPen * Oldpen1=dc.SelectObject(&PenBlue);
				
				DrawPoint(dc,pos+CPoint(10,10));
				DrawLine(dc,m_point[order-2]+pall,m_point[order-1]+pall);

				dc.SelectObject(&Oldpen1);
			}
			break;	
		}
	case 4:
		{
			n_point[0]=pos;
			fs=1;
			break;
		}
	case 5:
		{
			DrawPoint(dc,pos);
			if(fs==0)
			{
				m_point[0]=pos;		//第一次点下鼠标，记录第一个点
				fs=1;	//记录状态
			}
			else if(fs==1)	//	第二次点击鼠标点
			{
				m_point[1]=pos;
				fs=2;	//为了进入下行存储点
			}
			break;
		}
	}
	dc.SelectObject(&Oldpen);
 }

void CMAPDlg::OnLButtonUp()	   //鼠标左键起来函数
{
	
	
	CPoint pos;
	GetCursorPos(&pos);
	ScreenToClient(&pos);
	CClientDC dc(this);

	CPen PenRed;
	PenRed.CreatePen(  PS_SOLID,1,RGB(255,0,0) );	//红色实线
	CPen * Oldpen=dc.SelectObject(&PenRed);

	switch(choice)
	{
	case 2:
		{
			m_point[1]=pos;
			DrawRect(dc,m_point[0],m_point[1]);
			fs =0;
			kk=0;
			break;
		}
	case 3:
		{
			if(fs==12 )	//第一个圆弧
			{
				m_point[order++]=pos;
				DrawPoint(dc,pos);
				DrawMultiArc(dc,m_point[order-3],m_point[order-2],m_point[order-1]);
				fs=0;
				begin=0;
				kk=0;

				CPen PenBlue;
				PenBlue.CreatePen(  PS_SOLID,1,RGB(0,0,255) );	//蓝色实线
				CPen * Oldpen1=dc.SelectObject(&PenBlue);
				
				DrawPoint(dc,pos+CPoint(10,10));
				DrawMultiArc(dc,m_point[order-3]+pall,m_point[order-2]+pall,m_point[order-1]+pall);
				dc.SelectObject(&Oldpen1);
			}
			else if(fs==22 || fs==41)//第一个直线画完
			{
				begin=0;
				fs=0;
				kk=0;
			}
			else if(fs==31)//不是第一个的圆弧     
			{
				m_point[order++]=pos;
				DrawPoint(dc,pos);
				DrawMultiArc(dc,m_point[order-3],m_point[order-2],m_point[order-1]);
				fs=0;
				kk=0;

				CPen PenBlue;
				PenBlue.CreatePen(  PS_SOLID,1,RGB(0,0,255) );	//蓝色实线
				CPen * Oldpen1=dc.SelectObject(&PenBlue);
				
				DrawPoint(dc,pos+CPoint(10,10));
				DrawMultiArc(dc,m_point[order-3]+pall,m_point[order-2]+pall,m_point[order-1]+pall);
				dc.SelectObject(&Oldpen1);
			}
			break;
		}
	case 4:
		{
			n_point[1]=pos;
			DrawLine(dc,n_point[0],n_point[1]);
			fs=0;
			kk=0;
			break;
		}
	case 5:
		{
			if(fs==2)
			{
				m_point[2]=pos;
				DrawPoint(dc,pos);
				DrawMultiArc(dc,m_point[0],m_point[1],m_point[2]);
				
				fs=0 ;
				kk=0 ;		//恢复初始状态
			}
			break;
		}
	}
	dc.SelectObject(&Oldpen);
}

void CMAPDlg::OnMouseMove()			//鼠标移动
{
	CPoint	pos;
	CRect	rc;	
	GetCursorPos(&pos); 
	ScreenToClient(&pos);	
	GetClientRect(rc);	
	if( !rc.PtInRect(pos) )	
		return;		
	
	CClientDC dc(this);			
	dc.SetROP2(R2_NOT);

	CPen PenRed;
	PenRed.CreatePen(  PS_SOLID,1,RGB(255,0,0) );	//红色实线
	CPen * Oldpen=dc.SelectObject(&PenRed);

	switch (choice)
	{
	case 2:
		{	
			if(fs==1)
			{
				m_point[1]=pos;
				if(kk==1)
					DrawRect(dc,m_point[0],m_point[2]);
				DrawRect(dc,m_point[0],m_point[1]);
				m_point[2]=pos;
				kk=1;
				break;
			}
		}
	case 3:
		{
			if(fs==12 || fs==31)		//圆弧
			{
				m_point[order]=pos;
				if(kk==1)
					DrawMultiArc(dc,m_point[order-2],m_point[order-1],tem_point);
				DrawMultiArc(dc,m_point[order-2],m_point[order-1],m_point[order]);
				tem_point=pos;
				kk=1;
			}

			else if(fs==21) //第一个直线
			{
				m_point[1]=pos;
				if(kk==1)
					DrawLine(dc,n_point[0],tem_point);
				DrawLine(dc,m_point[0],m_point[1]);
				tem_point=pos;//将当前的鼠标点记录为下次操作的上一个移动点
				kk=1;
			}
			else if(begin=0 && draw_type=="L")//不是第一个直线
			{
				m_point[order]=pos;
				if(kk==1)
					DrawLine(dc,n_point[order-1],tem_point);
				DrawLine(dc,m_point[order-1],m_point[order]);
				tem_point=pos;//将当前的鼠标点记录为下次操作的上一个移动点
				kk=1;
			}
			break;
		}
	case 4:
		{
			if(fs==1)
			{
				n_point[1]=pos;
				if(kk==1)
				{
					DrawLine(dc,n_point[0],n_point[2]);
				}
				DrawLine(dc,n_point[0],n_point[1]);
				n_point[2]=pos;//将当前的鼠标点记录为下次操作的上一个移动点
				kk=1;//	kk=0;
			}
			break;
		}
	case 5:
		{
			if(fs==2)
			{
				m_point[2]=pos;
				if(kk==1)
					DrawMultiArc(dc,m_point[0],m_point[1],m_point[3]);
				DrawMultiArc(dc,m_point[0],m_point[1],m_point[2]);
				m_point[3]=pos;
				kk=1;	
				break;
			}
		}
	}
	dc.SelectObject(&Oldpen);
}
//******************************************************
void CMAPDlg::OnButtonPoint() //画点
{
	// TODO: Add your control notification handler code here
	choice =1;
}

void CMAPDlg::OnButtonRect() //画矩形
{
	// TODO: Add your control notification handler code here
	choice =2;
}

void CMAPDlg::OnButtonPline() //画多义线
{
	// TODO: Add your control notification handler code here
	choice =3;
}

void CMAPDlg::OnButtonLine()	//画直线 
{
	// TODO: Add your control notification handler code here
	 choice =4;
}


void CMAPDlg::OnButtonArc() //画圆弧
{
	// TODO: Add your control notification handler code here
	choice =5;
}



void CMAPDlg::OnButtonInOrOut() 
{
	// TODO: Add your control notification handler code here
	int i=is_PointInRect(n_point[0], m_point[0], m_point[1]);
	if (i==1)
		AfxMessageBox(" 点在矩形内! ");
	else
		AfxMessageBox(" 点不在矩形内! ");
}

BOOL CMAPDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->wParam == 'A')
	{
		draw_type="A";	//这个时候画圆弧

	}
	else if (pMsg->wParam == 'L')
	{
		draw_type="L";	//这个时候画直线
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CMAPDlg::OnButtonInter() //圆弧与直线的交点
{
	// TODO: Add your control notification handler code here
	int number=is_LineAndArc(n_point[0],n_point[1],m_point[0],m_point[1],m_point[2]);
	
	switch(number)
	{
	case 0:
		AfxMessageBox("直线与圆弧没有交点!");
		break;
	case 1:
		AfxMessageBox("直线与圆弧有 1 个交点!");
		break;
	case 2:
	AfxMessageBox("直线与圆弧有 2 个交点!");
	break;
	}
}
