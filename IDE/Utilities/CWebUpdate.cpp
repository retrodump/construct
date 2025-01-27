// CWebUpdate.cpp : implementation file
//

#include "..\stdafx.h"
#include "CWebUpdate.h"

#include "sha1.h" 

#include <process.h>
#include "atlbase.h"

#include <sys/stat.h>

// Global variables
CString remoteFile;
CString localFile;
HRESULT dloadResult;

// Thread function, downloads a file
//
void downloadFile(void* nullData)
{
	dloadResult = URLDownloadToFile(NULL, remoteFile, localFile, NULL, NULL);   

	return;
}

/////////////////////////////////////////////////////////////////////////////
// CWebUpdate class



CWebUpdate::CWebUpdate()
{
	// Nothing to see here
}



// Internal function, do the SHA-1 hash
//
CString CWebUpdate::DoSHA1Hash(LPCSTR filePath)
{
	sha1_ctx m_sha1;

	CString tempHash;
	FILE *fileToHash = NULL;

	unsigned char fileBuf[16000];
	unsigned long lenRead = 0;

	// The outputted hash
	CString outHash;

	// Temporary working buffers
	unsigned char* tempOut = new unsigned char[256];

	sha1_begin(&m_sha1);

	fileToHash = fopen(filePath, "rb");
	
	do
	{
		lenRead = fread(fileBuf, 1, 16000, fileToHash);
		if(lenRead != 0)
		{
			sha1_hash(fileBuf, lenRead, &m_sha1);
		}
	} while (lenRead == 16000);

	fclose(fileToHash); fileToHash = NULL;

	sha1_end(tempOut, &m_sha1);

	for (int i = 0 ; i < 20 ; i++)
	{
		char tmp[3];
		_itoa(tempOut[i], tmp, 16);
		if (strlen(tmp) == 1)
		{
			tmp[1] = tmp[0];
			tmp[0] = '0';
			tmp[2] = '\0';
		}
		tempHash += tmp;
	}

	delete[] tempOut;

	outHash = tempHash;

	return outHash;
}



// Set the local directory to download to
//
void CWebUpdate::SetLocalDirectory(LPCSTR pathTo, bool generate)
{
	if (generate)
	{
		char blankStr[MAX_PATH] = "";
		CString path;

		GetModuleFileName(0, blankStr, sizeof(blankStr) - 1);

		path = blankStr;
		path = path.Left(path.ReverseFind('\\'));

		localDir = path;
	}

	else
	{
		localDir = pathTo;
	}
}



// Perform the actual update
//
bool CWebUpdate::DoUpdateCheck()
{
	// Reset previous attributes
	numMissing = 0;
	numDifferent = 0;
	numSuccess = 0;

	missingFiles.RemoveAll();
	differentFiles.RemoveAll();
	successfulFiles.RemoveAll();
	differentInfo.RemoveAll();
	missingInfo.RemoveAll();

	// First of all, try and retrieve the update file
	remoteFile = updateURL;

	CPath path;
	path.SetToAppDataDirectory("Scirra");

	localFile.Format("%sTempUpdate.txt", path.GetFullPath());
	DeleteFile(localFile);

	// Download
	HANDLE dloadHandle = (HANDLE)_beginthread(downloadFile, 0, (void*)"");

	// Wait for it to finish
	AtlWaitWithMessageLoop(dloadHandle);

	// The download failed, return false
	if (!SUCCEEDED(dloadResult))
		return false;

	// It downloaded, now we parse it
	// Read it line by line and work out what's what
	CStdioFile loadFile(localFile, CFile::modeRead | CFile::typeText);
	CString curLine;
	bool anyFilesFound = false;
	
	while(loadFile.ReadString(curLine))
	{
		CString fileTo;
		AfxExtractSubString(fileTo, curLine, 0, ':');

		CString fileHash;
		AfxExtractSubString(fileHash, curLine, 1, ':');

		CString fileInfo;
		AfxExtractSubString(fileInfo, curLine, 2, ':');

		// Empty line: don't try to do anything
		if (fileTo == "")
			continue;
		else
			anyFilesFound = true;

		// So the path = ..
		CString pathTo = localDir + "\\" + fileTo;

		struct stat checkFile;
		if(stat(pathTo, &checkFile) == 0)
		{
			// It exists, but is it the same file?
			CString verifyFile = DoSHA1Hash(pathTo);

			// Now compare the hases
			if (verifyFile == fileHash)
			{
				// The files are the same, no worries
				numSuccess++;

				successfulFiles.Add(fileTo);
			}

			else
			{
				// The files are different
				numDifferent++;

				differentFiles.Add(fileTo);
				differentInfo.Add(fileInfo);
			}
		}

		else
		{
			// The files doesn't exist at all
			numMissing++;

			missingFiles.Add(fileTo);
			missingInfo.Add(fileInfo);
		}
	}

	return anyFilesFound;
}



// Download a missing file
//
bool CWebUpdate::DownloadMissing(int i)
{
	// Attempt to download the file
	remoteFile = remoteURL + "/" + missingFiles.GetAt(i);
	localFile = localDir + "\\" + missingFiles.GetAt(i);

	HANDLE dloadHandle = (HANDLE)_beginthread(downloadFile, 0, (void*)"");

	AtlWaitWithMessageLoop(dloadHandle);

	if (!SUCCEEDED(dloadResult))
		return false;

	else
		return true;
}



// Download an updated file
//
bool CWebUpdate::DownloadDifferent(int i)
{
	// Attempt to download the file
	remoteFile = remoteURL + "/" + differentFiles.GetAt(i);
	localFile = localDir + "\\" + differentFiles.GetAt(i);

	HANDLE dloadHandle = (HANDLE)_beginthread(downloadFile, 0, (void*)"");

	AtlWaitWithMessageLoop(dloadHandle);

	if (!SUCCEEDED(dloadResult))
		return false;

	else
		return true;
}
#include "stdafx.h"