#pragma once
class StatisticManager
{
	DECLARE_SINGLE(StatisticManager);

public:
	void Reset();

	time_t GetStartTime() {
		return m_startTime;
	}

	int GetJumpCount() {
		return m_jumpCount;
	}
	
	int GetFallCount() {
		return m_fallCount;
	}

	int GetDetectThorn() {
		return m_detectThorn;
	}

	void AddJump() {
		m_jumpCount++;
	}
	void AddFall() {
		m_fallCount++;
	}
	void AddThorn() {
		m_detectThorn++;
	}

private:
	time_t m_startTime;
	int m_jumpCount;
	int m_fallCount;
	int m_detectThorn;
};

