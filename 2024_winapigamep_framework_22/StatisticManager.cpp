#include "pch.h"
#include "StatisticManager.h"

void StatisticManager::Reset()
{
	m_startTime = time(NULL);
	m_jumpCount = 0;
	m_fallCount = 0;
	m_detectThorn = 0;
}