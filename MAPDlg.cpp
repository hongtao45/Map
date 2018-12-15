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

	//���ƶ���εĵ�����,������ݵĳ�ʼ��
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
	draw_type="A"; //Ĭ�Ͽ�ʼ��Բ��

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


	ON_WM_LBUTTONDOWN()			//��Ӧ����������
	ON_WM_LBUTTONUP()			//��Ӧ�������ſ�
	ON_WM_MOUSEMOVE()			//��Ӧ����ƶ�

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
void DrawPoint(CClientDC &dc,CPoint p0)	//��һ��С����
{
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//����͸����ˢ
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

void DrawLine(CClientDC &dc,CPoint p0,CPoint p1)  //ֱ��
{
	dc.MoveTo(p0);
	dc.LineTo(p1);
}

//CMAPDlg dlg;

void CMAPDlg::OnButton1() //���
{
	// TODO: Add your control notification handler code here
	fs=0;
	kk=0;
	order=0;
	Invalidate();	//���ô��ڵ�ˢ�º���
}

double direction(CPoint a, CPoint b, CPoint c) //��Բ��ʱʹ�õ������жϷ���ĺ���
{
	return (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
}
//�������ֵ����0Ϊ˳ʱ�룬С��0Ϊ��ʱ�롣

void DrawMultiArc(CClientDC& dc, CPoint p0,CPoint p1,CPoint p2)		//�����㻭��
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
	double x=((c1*b2)-(c2*b1))/((a1*b2)-(a2*b1));  //֮ǰ��Ҫ�жϳ����Ƿ������
	double y=((a1*c2)-(a2*c1))/((a1*b2)-(a2*b1));	//Բ������
	
	double temp_1=((x-p0.x)*(x-p0.x)+(y-p0.y)*(y-p0.y));	//����֮��ľ����ƽ�����п�����ȡ�˷��ŵ�
	
	double temp_2=temp_1>=0 ? temp_1:-temp_1;	//ȷ���ð��￪������������
	double radius=sqrt(temp_2);			//�뾶
	//ʹ�÷ֳ�Ա�����Թ��г�Ա��Ա���ݸ�ֵ����Ҫʹ�����޶���
	dc.Arc(x-radius , y-radius , x+radius , y+radius , p0.x ,p0.y ,p2.x , p2.y );
}

bool is_PointInRect(const CPoint& p0,const CPoint& TopLeft,const CPoint& BottomRight)//�жϵ��ǲ����ھ����ڲ�
{
	if(p0.x>TopLeft.x && p0.x<BottomRight.x
		&&p0.y>TopLeft.y && p0.y<BottomRight.y)
		return true;
	else
		return false;
}

//�ж�ֱ������Բ�� �Ľ���  ���ؽ���ĸ���
int   is_LineAndArc(const CPoint& t1,const CPoint& t2,			//ֱ�ߵ�������
					const CPoint& p0,const CPoint& p1,const CPoint& p2)//Բ����������
				    
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
	double x_=((c1*b2)-(c2*b1))/((a1*b2)-(a2*b1));  //֮ǰ��Ҫ�жϳ����Ƿ������
	double y_=((a1*c2)-(a2*c1))/((a1*b2)-(a2*b1));	//Բ������
	
	double temp_1=((x_-p0.x)*(x_-p0.x)+(y_-p0.y)*(y_-p0.y));	//����֮��ľ����ƽ�����п�����ȡ�˷��ŵ�
	
	double temp_2=temp_1>=0 ? temp_1:-temp_1;	//ȷ���ð��￪������������
	double radius=sqrt(temp_2);			//�뾶
//*************************************************/

	double A,B,C,dist;//�����ϵ��
	double ange1,ange2;//�Ƕ�
	double dist1=(t1.x-x_)*(t1.x-x_)+(t1.y-y_)*(t1.y-y_);
	double dist2=(t2.x-x_)*(t2.x-x_)+(t2.y-y_)*(t2.y-y_);
	
	if(  dist1<radius&& dist2<radius )
		return 0;//û�н���
	else if(dist1<radius || dist2<radius)//��һ������
		return 1;
	else if(t1.x==t2.x)// ֱ�ߵ�һ�㷽�� Ax + By + C = 0; �����㶼������
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

	dist=abs(A*x_ - B*y_ + C)/( sqrt(A*A+B*B) );	//�㵽ֱ�ߵľ���
	if(dist>radius)
	return 0;

	ange1=(x_ - t1.x)*(t2.x - t1.x)+(y_ - t1.y)*(t2.y - t1.y);//�Ƕ�
	ange2=(x_ - t2.x)*(t1.x - t2.x)+(y_ - t2.y)*(t1.y - t2.y);
	if(ange1>0 && ange2>0)
		return 2;
}

//*********************************************************************************
void CMAPDlg::OnLButtonDown()	//�����ȥ ʹ�ô�����ȡ������꣬��ͼ
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
	PenRed.CreatePen(  PS_SOLID,1,RGB(255,0,0) );	//��ɫʵ��
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
	case 3:			//��������
		{	

			if(begin==1 &&  draw_type=="A" && fs==0)	//��һ����Բ�������
			{
				DrawPoint(dc,pos);
				m_point[0]=pos;
				order++;
				fs=11;

				CPen PenBlue;
				PenBlue.CreatePen(  PS_SOLID,1,RGB(0,0,255) );	//��ɫʵ��
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
				PenBlue.CreatePen(  PS_SOLID,1,RGB(0,0,255) );	//��ɫʵ��
				CPen * Oldpen1=dc.SelectObject(&PenBlue);
				
				DrawPoint(dc,pos+pall);
				
				dc.SelectObject(&Oldpen1);

			}
			else if(begin==1 && draw_type=="L" && fs==0) //��һ����ֱ��
			{
				DrawPoint(dc,pos);
				m_point[0]=pos; 
				order++;
				fs=21;

				CPen PenBlue;
				PenBlue.CreatePen(  PS_SOLID,1,RGB(0,0,255) );	//��ɫʵ��
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
				PenBlue.CreatePen(  PS_SOLID,1,RGB(0,0,255) );	//��ɫʵ��
				CPen * Oldpen1=dc.SelectObject(&PenBlue);
				
				DrawPoint(dc,pos+pall);
				DrawLine(dc,m_point[order-2]+pall,m_point[order-1]+pall);

				dc.SelectObject(&Oldpen1);

			}
			else if(begin==0 && draw_type=="A" && fs==0)//���ǵ�һ��Բ����ֻ��Ҫ��ȡһ����
			{
				DrawPoint(dc,pos);
				m_point[order++]=pos;
				fs=31;

				CPen PenBlue;
				PenBlue.CreatePen(  PS_SOLID,1,RGB(0,0,255) );	//��ɫʵ��
				CPen * Oldpen1=dc.SelectObject(&PenBlue);
				
				DrawPoint(dc,pos+pall);
				
				dc.SelectObject(&Oldpen1);
			}
			else if(begin==0 && draw_type=="L" &&fs==0)//���ǵ�һ����ֱ��,�����ֱ�ӻ�ֱ��
			{
				DrawPoint(dc,pos);
				m_point[order++]=pos;
				fs=41;	//���������ʱ�򣬳�ʼ�����Ʊ�����ֵ
				DrawLine(dc,m_point[order-2],m_point[order-1]);

				CPen PenBlue;
				PenBlue.CreatePen(  PS_SOLID,1,RGB(0,0,255) );	//��ɫʵ��
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
				m_point[0]=pos;		//��һ�ε�����꣬��¼��һ����
				fs=1;	//��¼״̬
			}
			else if(fs==1)	//	�ڶ��ε������
			{
				m_point[1]=pos;
				fs=2;	//Ϊ�˽������д洢��
			}
			break;
		}
	}
	dc.SelectObject(&Oldpen);
 }

void CMAPDlg::OnLButtonUp()	   //��������������
{
	
	
	CPoint pos;
	GetCursorPos(&pos);
	ScreenToClient(&pos);
	CClientDC dc(this);

	CPen PenRed;
	PenRed.CreatePen(  PS_SOLID,1,RGB(255,0,0) );	//��ɫʵ��
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
			if(fs==12 )	//��һ��Բ��
			{
				m_point[order++]=pos;
				DrawPoint(dc,pos);
				DrawMultiArc(dc,m_point[order-3],m_point[order-2],m_point[order-1]);
				fs=0;
				begin=0;
				kk=0;

				CPen PenBlue;
				PenBlue.CreatePen(  PS_SOLID,1,RGB(0,0,255) );	//��ɫʵ��
				CPen * Oldpen1=dc.SelectObject(&PenBlue);
				
				DrawPoint(dc,pos+CPoint(10,10));
				DrawMultiArc(dc,m_point[order-3]+pall,m_point[order-2]+pall,m_point[order-1]+pall);
				dc.SelectObject(&Oldpen1);
			}
			else if(fs==22 || fs==41)//��һ��ֱ�߻���
			{
				begin=0;
				fs=0;
				kk=0;
			}
			else if(fs==31)//���ǵ�һ����Բ��     
			{
				m_point[order++]=pos;
				DrawPoint(dc,pos);
				DrawMultiArc(dc,m_point[order-3],m_point[order-2],m_point[order-1]);
				fs=0;
				kk=0;

				CPen PenBlue;
				PenBlue.CreatePen(  PS_SOLID,1,RGB(0,0,255) );	//��ɫʵ��
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
				kk=0 ;		//�ָ���ʼ״̬
			}
			break;
		}
	}
	dc.SelectObject(&Oldpen);
}

void CMAPDlg::OnMouseMove()			//����ƶ�
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
	PenRed.CreatePen(  PS_SOLID,1,RGB(255,0,0) );	//��ɫʵ��
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
			if(fs==12 || fs==31)		//Բ��
			{
				m_point[order]=pos;
				if(kk==1)
					DrawMultiArc(dc,m_point[order-2],m_point[order-1],tem_point);
				DrawMultiArc(dc,m_point[order-2],m_point[order-1],m_point[order]);
				tem_point=pos;
				kk=1;
			}

			else if(fs==21) //��һ��ֱ��
			{
				m_point[1]=pos;
				if(kk==1)
					DrawLine(dc,n_point[0],tem_point);
				DrawLine(dc,m_point[0],m_point[1]);
				tem_point=pos;//����ǰ�������¼Ϊ�´β�������һ���ƶ���
				kk=1;
			}
			else if(begin=0 && draw_type=="L")//���ǵ�һ��ֱ��
			{
				m_point[order]=pos;
				if(kk==1)
					DrawLine(dc,n_point[order-1],tem_point);
				DrawLine(dc,m_point[order-1],m_point[order]);
				tem_point=pos;//����ǰ�������¼Ϊ�´β�������һ���ƶ���
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
				n_point[2]=pos;//����ǰ�������¼Ϊ�´β�������һ���ƶ���
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
void CMAPDlg::OnButtonPoint() //����
{
	// TODO: Add your control notification handler code here
	choice =1;
}

void CMAPDlg::OnButtonRect() //������
{
	// TODO: Add your control notification handler code here
	choice =2;
}

void CMAPDlg::OnButtonPline() //��������
{
	// TODO: Add your control notification handler code here
	choice =3;
}

void CMAPDlg::OnButtonLine()	//��ֱ�� 
{
	// TODO: Add your control notification handler code here
	 choice =4;
}


void CMAPDlg::OnButtonArc() //��Բ��
{
	// TODO: Add your control notification handler code here
	choice =5;
}



void CMAPDlg::OnButtonInOrOut() 
{
	// TODO: Add your control notification handler code here
	int i=is_PointInRect(n_point[0], m_point[0], m_point[1]);
	if (i==1)
		AfxMessageBox(" ���ھ�����! ");
	else
		AfxMessageBox(" �㲻�ھ�����! ");
}

BOOL CMAPDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->wParam == 'A')
	{
		draw_type="A";	//���ʱ��Բ��

	}
	else if (pMsg->wParam == 'L')
	{
		draw_type="L";	//���ʱ��ֱ��
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CMAPDlg::OnButtonInter() //Բ����ֱ�ߵĽ���
{
	// TODO: Add your control notification handler code here
	int number=is_LineAndArc(n_point[0],n_point[1],m_point[0],m_point[1],m_point[2]);
	
	switch(number)
	{
	case 0:
		AfxMessageBox("ֱ����Բ��û�н���!");
		break;
	case 1:
		AfxMessageBox("ֱ����Բ���� 1 ������!");
		break;
	case 2:
	AfxMessageBox("ֱ����Բ���� 2 ������!");
	break;
	}
}
