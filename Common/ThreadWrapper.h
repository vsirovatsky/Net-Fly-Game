#pragma once

#include "stdafx.h"

namespace common {

class thread
{
	static DWORD WINAPI ThreadFunc(LPVOID pv)
	{
		try {
		(reinterpret_cast<thread *>(pv))->run();
		} catch(...) {
		}
		return 0;
	}
public:
	typedef DWORD threadid;
	HANDLE m_hThread;
	threadid m_id;
	thread(){m_hThread=0;}
	virtual ~thread(){}

	static threadid getthreadid()
	{
		return ::GetCurrentThreadId();
	}
	static void sleep(long milliseconds=1)
	{
		::Sleep(milliseconds);
	}
	threadid start()
	{
		m_hThread = ::CreateThread(NULL, 0, ThreadFunc, this, 0, &m_id);
		return m_id;
	}
	virtual void run()=0;
	bool IsThreadActive() const
    {
		return ((m_hThread != NULL) && (::WaitForSingleObject(m_hThread, 0) != WAIT_OBJECT_0));
    }

	void suspend()
	{
		::SuspendThread( m_hThread );
	}

	void resume()
	{
		int resumeCount = ::ResumeThread( m_hThread );
		while (resumeCount > 1)
			resumeCount = ::ResumeThread( m_hThread );
	}

	void terminate()
	{
		if (m_hThread)
		{
			::TerminateThread( m_hThread, 0 );
			::CloseHandle( m_hThread );
			m_hThread = NULL;
		}
	}
};

}