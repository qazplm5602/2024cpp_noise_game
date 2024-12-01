#include "pch.h"
#include "MicJumpObserver.h"
#include "IMicJumpHandler.h"
#include "Object.h"
#include "MicrophoneManager.h"
#include "TimeManager.h"

MicJumpObserver::MicJumpObserver()
	: m_lastPeek(0.0f)
	, m_upDuration(0.0f)
	, m_cumulativePower(0.0f)
{

}

void MicJumpObserver::LateUpdate()
{
}

void MicJumpObserver::Update()
{
	IMicJumpHandler* handler = dynamic_cast<IMicJumpHandler*>(GetOwner());
	assert(handler != nullptr);

	float currentPeek;
	GET_SINGLE(MicrophoneManager)->GetMicPeek(&currentPeek);
	
	if (m_lastPeek <= currentPeek) {
		m_cumulativePower += currentPeek - m_lastPeek;
		m_upDuration += fDT;
	}
	else { // 소리가 작아짐
		if (m_cumulativePower > 0.1f) {
			handler->OnMicJump(m_cumulativePower);
		}

		//cout << m_cumulativePower << endl;
		m_upDuration = m_cumulativePower = 0.0f;
	}

	m_lastPeek = currentPeek;
	//cout << m_lastPeek << "->" << currentPeek << "/" << m_cumulativePower << " / " << m_upDuration << endl;
}

void MicJumpObserver::Render(HDC _hdc)
{
}
