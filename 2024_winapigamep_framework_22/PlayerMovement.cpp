#include "pch.h"
#include "PlayerMovement.h"
#include "Rigidbody.h"
#include "Object.h"
#include "MicrophoneManager.h"
#include "TimeManager.h"

PlayerMovement::PlayerMovement()
{
}

PlayerMovement::~PlayerMovement()
{
}

void PlayerMovement::HandleJump()
{
	
	if (rb == nullptr)
	{
		rb = GetOwner()->GetComponent<Rigidbody>();
	}
	if (rb != nullptr && rb->IsGrounded())
	{
		//cout << rb->GetVelocity().y << endl;
		//rb->AddImpulse(Vec2(0.f, -1000.f));
		float volume = 0; 
		if (GET_SINGLE(MicrophoneManager)->IsConnected())
		{
			GET_SINGLE(MicrophoneManager)->GetMicPeek(&volume);
		}
		if (volume < 0.235f) return;
		rb->AddImpulse(Vec2(0.f, volume * -90.f));
		fJumpTime = BASEJUMPDURATION;
	}
}

void PlayerMovement::LateUpdate()
{
	if (fJumpTime > 0)
	{
		fJumpTime -= fDT;
		float volume = 0;
		if (GET_SINGLE(MicrophoneManager)->IsConnected())
		{
			GET_SINGLE(MicrophoneManager)->GetMicPeek(&volume);
		}
		rb->AddForce({0.f, volume * -5200.f });
	}
}

void PlayerMovement::Render(HDC _hdc)
{
}
