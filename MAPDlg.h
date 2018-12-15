// MAPDlg.h : header file
//

#if !defined(AFX_MAPDLG_H__6CA3B0F0_574E_41C5_B3BA_00E46DC22986__INCLUDED_)
#define AFX_MAPDLG_H__6CA3B0F0_574E_41C5_B3BA_00E46DC22986__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMAPDlg dialog

class CMAPDlg : public CDialog
{
// Construction
public:
	CMAPDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMAPDlg)
	enum { IDD = IDD_MAP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMAPDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	
	public:
		CPoint m_point[140];  //�� ���Σ��ͻ�Բ��  �ĵ��¼�������ߵĵ�λ�ü�¼
		CPoint n_point[3];   //��  �㣬  �� ֱ��   ��λ�õ�ļ�¼
		CPoint tem_point;    //���ɵ�
		CPoint pall;
		int choice;			 //��Ϊ����������ͬ������
		int fs,kk;			 //fs ���µĴ�������¼���״̬
		CString  draw_type;	 //���ߺ������ģ�����
		int order;//��¼�㣬�±�
		bool begin;//��һ������ͼ���ı��
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMAPDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnLButtonDown();		//��������Ҽ�
	afx_msg void OnLButtonUp();			//�������
	afx_msg void OnMouseMove();			//����ƶ�

	afx_msg void OnButton1();
	afx_msg void OnButtonLine();
	afx_msg void OnButtonPoint();
	afx_msg void OnButtonRect();
	afx_msg void OnButtonArc();
	afx_msg void OnButtonPline();
	afx_msg void OnButtonInOrOut();
	afx_msg void OnButtonPall();
	afx_msg void OnButtonInter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPDLG_H__6CA3B0F0_574E_41C5_B3BA_00E46DC22986__INCLUDED_)
