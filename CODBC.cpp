#ifndef _CODBC_
	#include "CODBC.h"
#endif

/////////////////////////////////////////////////////////////
//
// CODBCDatabase Class
//

void CODBCDatabase::SQLAlloc()
{
	
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv);
	SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0); 
	SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc); 
}

void CODBCDatabase::SQLFree()
{
	SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
	m_hDbc = NULL;
	m_hEnv = NULL;
}

void CODBCDatabase::Close()
{
	m_bIsConnected = FALSE;
	if(m_hDbc == NULL)
		return;
	SQLDisconnect(m_hDbc);
	SQLFree();
}

BOOL CODBCDatabase::Open(CHAR* szDSN,CHAR* szUser, CHAR* szPass)
{
	SQLRETURN ret;
	
	if(m_lConnectionTimeout > 0)
		SQLSetConnectAttr(m_hDbc, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)m_lConnectionTimeout, 0);
		
	SQLSetConnectAttr(m_hDbc, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)m_lLoginTimeout, 0);

	ret = SQLConnectA(m_hDbc, (SQLCHAR *)szDSN, SQL_NTS, (SQLCHAR *)szUser, SQL_NTS, (SQLCHAR *)szPass, SQL_NTS);

	m_bIsConnected = ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
	return m_bIsConnected;
}

BOOL CODBCDatabase::Browse(UCHAR* szConnStrIn, UCHAR* szConnStrOut)
{
	SQLRETURN ret;
	SWORD swLenOut = 0;

	ret = SQLBrowseConnect(m_hDbc, 
							(SQLCHAR*)szConnStrIn, 
							sizeof(szConnStrIn), 
							(SQLCHAR*)szConnStrOut, 
							MAX_BUFFER, 
							&swLenOut);

	m_bIsConnected = ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
	return m_bIsConnected;
}

void CODBCDatabase::SetConnectionTimeout(LONG nSeconds)
{
	if(m_hDbc)
		SQLSetConnectAttr(m_hDbc, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)nSeconds, 0);

	m_lConnectionTimeout = nSeconds;
}

BOOL CODBCDatabase::DriverConnect(CHAR* szConnStr, CHAR* szConnStrOut, HWND hWnd, enum drvCompletion drvConn)
{

	SQLRETURN ret;
	SQLSMALLINT pcbConnStrOut;

	if(drvConn == sqlPrompt && hWnd == NULL)
		return FALSE;

	if(m_lConnectionTimeout > 0)
		SQLSetConnectAttr(m_hDbc, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)m_lConnectionTimeout, 0);
	
	SQLSetConnectAttr(m_hDbc, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)m_lLoginTimeout, 0);
	
	ret = SQLDriverConnect(m_hDbc, 
							hWnd, 
							(SQLCHAR*)szConnStr, 
							SQL_NTS, 
							(SQLCHAR*)szConnStrOut,
							sizeof(szConnStrOut), 
							&pcbConnStrOut, 
							(SQLUSMALLINT)drvConn);
	
	m_bIsConnected = ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
	return m_bIsConnected;
}

void CODBCDatabase::SetReadOnly(BOOL bReadOnly)
{

	SQLSetConnectAttr(m_hDbc, SQL_ATTR_ACCESS_MODE, (SQLPOINTER)(bReadOnly? SQL_MODE_READ_ONLY : SQL_MODE_READ_WRITE), 0);
}

LONG CODBCDatabase::GetConnectionTimeout()
{
	LONG nSeconds;

	SQLGetConnectAttr(m_hDbc, SQL_ATTR_CONNECTION_TIMEOUT, &nSeconds, NULL, 0);

	return nSeconds;
}

BOOL CODBCDatabase::Execute(CHAR *szSqlStr)
{
	SQLRETURN ret;
	SQLHSTMT hStmt = NULL;
	SQLLEN nRowCount;

	SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &hStmt);
	ret = SQLExecDirect(hStmt, (SQLCHAR*)szSqlStr, SQL_NTS);
	
	
	SQLRowCount(hStmt, &nRowCount);
	
	m_nRowsAffected = nRowCount;
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}


/////////////////////////////////////////////////////////////
//
// CODBCRecordset Class
//

void CODBCRecordset::AllocStmt()
{
	SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt);
}

BOOL CODBCRecordset::Open(CHAR *szSqlStr, ...)
{
	char szSqlStmnt[4096];

	va_list vl;

	va_start(vl, szSqlStr);
		vsprintf_s(szSqlStmnt, 4096, szSqlStr, vl);
	va_end(vl);

	SQLRETURN ret;

	ret = SQLExecDirect(m_hStmt, (SQLCHAR*)szSqlStmnt, SQL_NTS);
	if(ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
	{
		SQLFetch(m_hStmt);
		return TRUE;
	}
	
	return FALSE;
}

BOOL CODBCRecordset::GetFieldValue(int nField, CHAR *szData)
{
	SQLRETURN ret;
	SQLLEN cbValue;
	int nLength = GetFieldLength(nField) + 1;
	
	ret = SQLGetData(m_hStmt, (SQLUSMALLINT)nField + 1, SQL_C_CHAR, szData, nLength, &cbValue) == SQL_SUCCESS;
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

BOOL CODBCRecordset::GetFieldValue(CHAR *szFieldName, CHAR *szData)
{
	return GetFieldValue(GetFieldIndex(szFieldName), szData);	
}

BOOL CODBCRecordset::GetFieldValue(int nField, LONG *lData)
{
	SQLRETURN ret;
	SQLLEN cbValue;
	int nLength = GetFieldLength(nField) + 1;
	
	ret = SQLGetData(m_hStmt, (SQLUSMALLINT)nField + 1, SQL_C_LONG, lData, nLength, &cbValue) == SQL_SUCCESS;
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

BOOL CODBCRecordset::GetFieldValue(CHAR *szFieldName, LONG *lData)
{
	return GetFieldValue(GetFieldIndex(szFieldName), lData);	
}

BOOL CODBCRecordset::GetFieldValue(int nField, DOUBLE *dblData)
{
	SQLLEN cbValue;
	SQLRETURN ret;
	int nLength = GetFieldLength(nField) + 1;
	
	ret = SQLGetData(m_hStmt, (SQLUSMALLINT)nField + 1, SQL_C_DOUBLE, dblData, nLength, &cbValue) == SQL_SUCCESS;
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

BOOL CODBCRecordset::GetFieldValue(CHAR *szFieldName, DOUBLE *dblData)
{
	return GetFieldValue(GetFieldIndex(szFieldName), dblData);	
}

BOOL CODBCRecordset::GetFieldValue(int nField, struct tm* time)
{
	
	SQLLEN cbValue;
	SQLRETURN ret;
	int nLength = GetFieldLength(nField) + 1;
	SQL_TIMESTAMP_STRUCT* sqltm = new SQL_TIMESTAMP_STRUCT;
	
	ret = SQLGetData(m_hStmt, (SQLUSMALLINT)nField + 1, SQL_C_TYPE_TIMESTAMP, sqltm, nLength, &cbValue) == SQL_SUCCESS;
	if(ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
	{	
		time->tm_year = sqltm->year;
		time->tm_mon = sqltm->month - 1; //January must be = 0		
		time->tm_mday = sqltm->day;
		time->tm_hour = sqltm->hour;
		time->tm_min = sqltm->minute;
		time->tm_sec = sqltm->second;
		return TRUE;
	}
	return FALSE;
}

BOOL CODBCRecordset::GetFieldValue(CHAR *szFieldName, struct tm* time)
{
	return GetFieldValue(GetFieldIndex(szFieldName), time);	
}



BOOL CODBCRecordset::GetFieldName(int nField, CHAR *szFieldName)
{
	int nType, nLength;

	return GetFieldAttributes(nField, szFieldName, nType, nLength);
}

int CODBCRecordset::GetFieldIndex(CHAR *szFieldName)
{
	SQLSMALLINT nCols;
	int nCol = 1;
	CHAR szColName[MAX_COL_NAME_LEN];
	SQLSMALLINT cbColNameLen, fSqlType, ibScale, fNullable;
	SQLULEN cbColDef;


	SQLNumResultCols(m_hStmt, &nCols);
	while(nCol < nCols)
	{
		memset(szColName, 0, 32 * sizeof(CHAR));
		SQLDescribeCol(m_hStmt, nCol, (SQLCHAR*)szColName, MAX_COL_NAME_LEN, &cbColNameLen, &fSqlType, &cbColDef, &ibScale, &fNullable);

		if(_stricmp(szColName, szFieldName) == 0)
			return nCol - 1;
		nCol++;
	}
	return -1;
}

BOOL CODBCRecordset::MoveFirst()
{
	SQLRETURN ret;

	ret = SQLFetchScroll(m_hStmt, SQL_FETCH_FIRST, 0);
	
	m_bIsBOF = ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
	if(m_bIsBOF)
		m_bIsEOF = FALSE;

	return m_bIsBOF;
}

BOOL CODBCRecordset::MoveNext()
{
	SQLRETURN ret;
	
	ret = SQLFetchScroll(m_hStmt, SQL_FETCH_NEXT, 0);
	
	m_bIsEOF = ret == SQL_NO_DATA;
	m_bIsBOF = FALSE;
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

BOOL CODBCRecordset::MovePrevious()
{
	SQLRETURN ret;
	
	ret = SQLFetchScroll(m_hStmt, SQL_FETCH_PRIOR, 0);
	m_bIsBOF = ret == SQL_NO_DATA;
	m_bIsEOF = FALSE;
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

BOOL CODBCRecordset::MoveLast()
{
	SQLRETURN ret;
	
	ret = SQLFetchScroll(m_hStmt, SQL_FETCH_LAST, 0);

	m_bIsEOF = ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
	if(m_bIsEOF)
		m_bIsBOF = FALSE;

	return m_bIsEOF;
}

LONG CODBCRecordset::GetFieldLength(int nField)
{
	SQLSMALLINT fSqlType, ibScale, fNullable;
	SQLULEN cbColDef;
	
	SQLDescribeCol(m_hStmt, nField + 1, NULL, 0, 0, &fSqlType, &cbColDef, &ibScale, &fNullable);

	return cbColDef;	
}

BOOL CODBCRecordset::GetFieldAttributes(int nField, CHAR* szFieldName, int& nType, int& nLength)
{
	SQLRETURN ret;
	SQLSMALLINT cbColNameLen, fSqlType, ibScale, fNullable;
	SQLULEN cbColDef;
	
	ret = SQLDescribeCol(m_hStmt, nField + 1, (SQLCHAR*)szFieldName, MAX_COL_NAME_LEN, &cbColNameLen, &fSqlType, &cbColDef, &ibScale, &fNullable);
	
	nType = fSqlType;
	nLength = cbColDef;

	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;	
}

int CODBCRecordset::GetFieldCount()
{

	SQLSMALLINT nFieldCount = 0;
	SQLNumResultCols(m_hStmt, &nFieldCount);

	return nFieldCount;
}

void CODBCRecordset::Close()
{
	if(m_hStmt != NULL)
		SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
	m_hStmt = NULL;
}