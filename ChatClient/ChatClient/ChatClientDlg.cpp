
// ChatClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	EnableActiveAccessibility();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CChatClientDlg �Ի���



CChatClientDlg::CChatClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHATCLIENT_DIALOG, pParent)
	, m_ServerName(_T(""))
	, m_ServerPort(0)
	, m_SendMsg(_T(""))
{
	m_ServerName = _T("");
	m_SendMsg = _T("");
	m_ServerPort = 0;
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SERVERNAME, m_ServerName);
	DDX_Text(pDX, IDC_EDIT_SERVERPORT, m_ServerPort);
	DDX_Text(pDX, IDC_EDIT_SENDMSG, m_SendMsg);
	DDX_Control(pDX, IDC_LIST_MSG, m_Msg);
}

BEGIN_MESSAGE_MAP(CChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CChatClientDlg::OnButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CChatClientDlg::OnButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CChatClientDlg::OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CChatClientDlg::OnButtonSend)
END_MESSAGE_MAP()


// CChatClientDlg ��Ϣ��������

BOOL CChatClientDlg::OnInitDialog()
{

	CDialogEx::OnInitDialog();

	// ��������...���˵������ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_ServerName = "localhost";
	m_ServerPort = 3030;
	UpdateData(FALSE);
	m_sConnectSocket.SetParent(this);

	GetDlgItem(IDC_EDIT_SENDMSG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);

	//ShowWindow(SW_MAXIMIZE);

	// TODO: �ڴ����Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChatClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatClientDlg::OnButtonConnect()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	UpdateData(TRUE);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVERNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(TRUE);
	m_sConnectSocket.Create();
	m_sConnectSocket.Connect(m_ServerName, m_ServerPort);


}


void CChatClientDlg::OnButtonDisconnect()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	OnClose();
}


void CChatClientDlg::OnButtonExit()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	CDialog::OnOK();
}


void CChatClientDlg::OnButtonSend()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	int nLen=0;
	int nSent=0;
	UpdateData(TRUE);
	if (!m_SendMsg.IsEmpty())
	{
		//int nLen;
		char * wsabuf = NULL;
#ifdef _UNICODE
		//CStringת����char*
		USES_CONVERSION;
		wsabuf = W2A(m_SendMsg);//m_strMsgΪCString��Ϣ
		nLen = strlen(wsabuf);
		nSent = m_sConnectSocket.Send(wsabuf, nLen);//��������
#else
		nLen = m_strMsg.GetLength();
		nSent = m_sConnectSocket.Send(LPCTSTR(m_SendMsg), nLen);//��������
#endif
		//nLen = m_SendMsg.GetLength();
		//nSent = m_sConnectSocket.Send(LPCTSTR(m_SendMsg), nLen);
		if (nSent != SOCKET_ERROR)
		{
			CTime  time = CTime::GetCurrentTime();
			CString m_Time = time.Format("%Y-%m-%d %H:%M:%S");
			m_Msg.AddString(m_Time);
			m_Msg.AddString(_T("Client��")+m_SendMsg);
			UpdateData(FALSE);

		}
		else {
			AfxMessageBox(_T("����ʧ�ܣ�"), MB_OK | MB_ICONSTOP);
		}
		m_SendMsg.Empty();
		UpdateData(FALSE);

	}
}

void CChatClientDlg::OnConnect()
{
	GetDlgItem(IDC_EDIT_SENDMSG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
	m_Msg.AddString(_T("���������ͨ�������Ѿ�����"));

}

void CChatClientDlg::OnClose()
{
	m_sConnectSocket.Close();
	GetDlgItem(IDC_EDIT_SENDMSG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(FALSE);
	while (m_Msg.GetCount() != 0)
		m_Msg.DeleteString(0);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SERVERNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(TRUE);
}

void CChatClientDlg::OnReceive()
{
	char * pBuf = new char[1025];
	int nBufSize = 1024;
	int nReceived;
	CString strReceived;
	nReceived = m_sConnectSocket.Receive(pBuf, nBufSize,0);
	if (nReceived != SOCKET_ERROR)
	{
		pBuf[nReceived] = NULL;
		strReceived = pBuf;
		CTime  time = CTime::GetCurrentTime();
		CString m_Time = time.Format("%Y-%m-%d %H:%M:%S");
		m_Msg.AddString(m_Time);
		m_Msg.AddString(_T("Server��")+strReceived);
		UpdateData(FALSE);

	}
	else {
		AfxMessageBox(_T("����ʧ�ܣ�"), MB_OK | MB_ICONSTOP);
	}
}