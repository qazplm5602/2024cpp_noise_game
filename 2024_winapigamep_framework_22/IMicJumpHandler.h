#pragma once

class IMicJumpHandler {
public:
	virtual void OnMicJump(const float& power) = 0;
};