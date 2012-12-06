// DIB.cpp
// Download by http://www.codefans.net

#include "stdafx.h"
#include "DIB.h"

CDib::CDib()
{

	m_pDib = NULL;
	m_pWordData = NULL;
	m_pFile = NULL;
	m_pOldDibShow = NULL;
}

CDib::~CDib()
{


	if( m_pDib != NULL )
		delete [] m_pDib;
	if( m_pWordData != NULL )
		delete [] m_pWordData;
	if (m_pFile != NULL)
		delete [] m_pFile;
	if (m_pOldDibShow != NULL)
		delete [] m_pOldDibShow;

}

BOOL CDib::Load( const char *pszFilename )
{

	CFile cf;

	if( !cf.Open( pszFilename, CFile::modeRead ) )
		return( FALSE );

	
	DWORD dwDibSize;
	dwDibSize =
		cf.GetLength() - sizeof( BITMAPFILEHEADER );

	unsigned char *pDib;
	pDib = new unsigned char [dwDibSize];
	if( pDib == NULL )
		return( FALSE );

	BITMAPFILEHEADER BFH;

	try{

		if( cf.Read( &BFH, sizeof( BITMAPFILEHEADER ) )
			!= sizeof( BITMAPFILEHEADER ) ||

			BFH.bfType != 'MB' ||

			cf.Read( pDib, dwDibSize ) != dwDibSize ){

			delete [] pDib;
			return( FALSE );
			}
		}

	
	catch( CFileException *e ){
		e->Delete();
		delete [] pDib;
		return( FALSE );
		}
	
	cf.Close();

	if( m_pDib != NULL )
		delete m_pDib;


 
	if (BFH.bfReserved1 != 0)          //含有隐藏信息，保存其大小
	{
		if (BFH.bfReserved2 == 0)
			embfile_size = BFH.bfReserved1;
		else
			embfile_size = BFH.bfReserved1 + 65535;
	}

	m_pDib = pDib;
	m_dwDibSize = dwDibSize;


	m_pBIH = (BITMAPINFOHEADER *) m_pDib;
	m_pPalette =
		(RGBQUAD *) &m_pDib[sizeof(BITMAPINFOHEADER)];


	m_nPaletteEntries = 1 << m_pBIH->biBitCount;
	if( m_pBIH->biBitCount > 8 )         
		m_nPaletteEntries = 0;
	else if( m_pBIH->biClrUsed != 0 )
		m_nPaletteEntries = m_pBIH->biClrUsed;

	
	m_pDibBits =                     
		&m_pDib[sizeof(BITMAPINFOHEADER)+
			m_nPaletteEntries*sizeof(RGBQUAD)];



	if( m_Palette.GetSafeHandle() != NULL )
		m_Palette.DeleteObject();

	if( m_nPaletteEntries != 0 ){      

		LOGPALETTE *pLogPal = (LOGPALETTE *) new char
				[sizeof(LOGPALETTE)+
				m_nPaletteEntries*sizeof(PALETTEENTRY)];

		if( pLogPal != NULL ){

			pLogPal->palVersion = 0x300;
			pLogPal->palNumEntries = m_nPaletteEntries;

			for( int i=0; i<m_nPaletteEntries; i++ ){
				pLogPal->palPalEntry[i].peRed =
					m_pPalette[i].rgbRed;
				pLogPal->palPalEntry[i].peGreen =
					m_pPalette[i].rgbGreen;
				pLogPal->palPalEntry[i].peBlue =
					m_pPalette[i].rgbBlue;
				}

			m_Palette.CreatePalette( pLogPal );
			delete [] pLogPal;
			}
		}

	m_BitCount = 24;             //24位位图
	p = m_pDibBits;              //指向位图数据的指针，用来执行处理操作用
	bitmap_size = m_dwDibSize - (m_pDibBits - m_pDib);//真正的位图数据的大小（即除头结构外）
	
	tag = BFH.bfReserved1;
	return( TRUE );

}

BOOL CDib::Save( const char *pszFilename ) //保存含有隐藏信息的bmp
{

	
	if( m_pDib == NULL )
		return( FALSE );

	CFile cf;


	if( !cf.Open( pszFilename,
		CFile::modeCreate | CFile::modeWrite ) )
		return( FALSE );
	

	try{

	
		BITMAPFILEHEADER BFH;
		memset( &BFH, 0, sizeof( BITMAPFILEHEADER ) );
		BFH.bfType = 'MB';
		BFH.bfSize = sizeof( BITMAPFILEHEADER ) + m_dwDibSize;
		BFH.bfOffBits = sizeof( BITMAPFILEHEADER ) +
			sizeof( BITMAPINFOHEADER ) +
			m_nPaletteEntries * sizeof( RGBQUAD );

		if (embfile_size <= 65535)   //由于bfReserved1是unsigned short型的，大小可能不能满足要求,可能要用到reserved2
			BFH.bfReserved1 = embfile_size;   
		else
		{
			BFH.bfReserved1 = embfile_size - 65535;
			BFH.bfReserved2 = 1; //标记
		}

		cf.Write( &BFH, sizeof( BITMAPFILEHEADER ) );
		cf.Write( m_pDib, m_dwDibSize );
		}


	catch( CFileException *e ){
		e->Delete();
		return( FALSE );
		}
		

	return( TRUE );

}

BOOL CDib::Draw( CDC *pDC, int nX, int nY, int nWidth, int nHeight, int Style )
{

 	if( m_pDib == NULL )
		return( FALSE );

 	long vWidth = m_pBIH->biWidth;
 

 	if( nWidth == -1 )
 		nWidth = m_pBIH->biWidth;
	if( nHeight == -1 )
 		nHeight = m_pBIH->biHeight;
 	
 	if (Style)   
 	{
 		StretchDIBits( pDC->m_hDC, nX, nY,
 			nWidth, nHeight,
 			0, 0,
 			m_pBIH->biWidth, m_pBIH->biHeight,
 			m_pDibBits,
 			(BITMAPINFO *) m_pBIH,
			BI_RGB, SRCCOPY );
 	}
 	else
 	{
		SetDIBitsToDevice( pDC->m_hDC, nX, nY,
 			m_pBIH->biWidth, m_pBIH->biHeight,
			0, 0,
 			0, m_pBIH->biHeight,
 			m_pDibBits,
 			(BITMAPINFO *) m_pBIH,
 			BI_RGB);
 	}

	return( TRUE );
}



BOOL CDib::LoadEmbFile(const char * pszFilename)
{	
	CFile cf;

	if( !cf.Open( pszFilename, CFile::modeRead ) )
		return( FALSE );

	DWORD dwFileSize;
	dwFileSize = cf.GetLength();

	embfile_size = dwFileSize;
	unsigned char *pFile;
	pFile = new unsigned char [dwFileSize];
	cf.Read( pFile, dwFileSize );       //将文件中内容读入数组，解下来就开始嵌入操作

	m_pFile = pFile;
	q = pFile;        //记录下位置
	return true;
}

void CDib::Embed()//嵌入
{
	unsigned char bmdata;//bitmap data
	unsigned char efdata;//embeddedfile data
	int t = 7;		
	int x[8];	
	int s[8];
	int last_bit; //记录字节最低位本来的bit

	for(UINT i1 = 0, i2 = 0; i1 <= bitmap_size - 1, i2 <= embfile_size - 1; i1++)
	{
		bmdata = *p;
		int j;
		for ( j = 0; j <= 7; j++) //计算各bit位
		{
			x[j] = bmdata & 1;
			bmdata >>= 1;
		}
		
		last_bit = x[0];
		x[0] = x[1] ^ x[2] ^ x[3] ^ x[4] ^ x[5] ^ x[6] ^ x[7];
		
		if (t == 7)    //宿主图片每走过八个字节，计算一次s[]
		{
			efdata = *q;
			for (j = 0; j <= 7; j++)
			{
				s[j] = efdata & 1;
				efdata >>= 1;
			}
		}
		x[0] ^= s[t];//隐藏信息
		if (last_bit == 0)  //嵌入隐藏信息
		{
			*p |= x[0];
		}
		else
		{
			*p &= 254 + x[0];
		}
	
		p++;
		t--;
		if (t == -1)  //需要计算一次s[]
		{
			t = 7;
			q++;
			i2++;
		}
	}

}

void CDib::Pick()//提取
{
	m_pFile = new unsigned char [embfile_size];
	unsigned char *q = m_pFile;

	unsigned char bmdata;//bitmap data

	int x[8];	
	int s[8];
	int t = 7;
	for (UINT i1 = 0, i2 = 0; i1 <= bitmap_size - 1, i2 <= embfile_size - 1; i1++)
	{
		bmdata = *p;
		for (int j = 0; j <= 7; j++) //计算各bit位
		{
			x[j] = bmdata & 1;
			bmdata >>= 1;
		}
		s[t] = x[0] ^ x[1] ^ x[2] ^ x[3] ^ x[4] ^ x[5] ^ x[6] ^ x[7];
		t--;
		if (t == -1) //s[7]到s[0]组成一个字节
		{
			*q = s[7] * 128 + s[6] * 64 + s[5] * 32 + s[4] * 16 + 
				s[3] * 8 + s[2] * 4 + s[1] * 2 + s[0];
			t = 7;
			i2++;
			q++;
		}
		p++;
	}

}
	
void CDib::SavePicked( const char *pszFilename )
{
	CFile cf;
	cf.Open( pszFilename, CFile::modeCreate | CFile::modeWrite );
	cf.Write( m_pFile, embfile_size );

}

void CDib::BackUpDib()
{
	m_pOldDibShow = new unsigned char [bitmap_size];
   
	::CopyMemory(m_pOldDibShow, m_pDibBits, bitmap_size); //将原始的数据单独保存以便对比显示
}

BOOL CDib::DrawContrast(CDC *pDC, int rect_width, int rect_height)
{                             //看原图，如果容纳得下两个图，则不要压缩，否则要压缩
	if (m_pOldDibShow == NULL)
		return FALSE;
	if (rect_width >= 2*m_pBIH->biWidth + 30 && rect_height >= m_pBIH->biHeight)
	{
		StretchDIBits( pDC->m_hDC, 0, 0,
		m_pBIH->biWidth, m_pBIH->biHeight,
		0, 0,
		m_pBIH->biWidth, m_pBIH->biHeight,
		m_pOldDibShow,
		(BITMAPINFO *) m_pBIH,
		BI_RGB, SRCCOPY );    // 原图

		StretchDIBits( pDC->m_hDC, m_pBIH->biWidth+30, 0,
		m_pBIH->biWidth, m_pBIH->biHeight,
		0, 0,
		m_pBIH->biWidth, m_pBIH->biHeight,
		m_pDibBits,
		(BITMAPINFO *) m_pBIH,
		BI_RGB, SRCCOPY );    // 嵌入隐藏信息的图
	}
	else
	{
		int scale_i = m_pBIH->biWidth * 5 / (rect_width*2);
		int scale_j = m_pBIH->biHeight / rect_height;
		if (scale_i < scale_j)
			scale_i = scale_j;

		StretchDIBits( pDC->m_hDC, 0, 0,
		m_pBIH->biWidth / scale_i, m_pBIH->biHeight / scale_i,
		0, 0,
		m_pBIH->biWidth, m_pBIH->biHeight,
		m_pOldDibShow,
		(BITMAPINFO *) m_pBIH,
		BI_RGB, SRCCOPY );    // 原图

		StretchDIBits( pDC->m_hDC, m_pBIH->biWidth / scale_i+30, 0,
		m_pBIH->biWidth / scale_i, m_pBIH->biHeight / scale_i,
		0, 0,
		m_pBIH->biWidth, m_pBIH->biHeight,
		m_pDibBits,
		(BITMAPINFO *) m_pBIH,
		BI_RGB, SRCCOPY );    // 嵌入隐藏信息的图

	}

	return TRUE;
}

