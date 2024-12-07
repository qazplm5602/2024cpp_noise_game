#include "pch.h"
#include "Player.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Projectile.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Rigidbody.h"
#include "MicJumpObserver.h"
#include "PlayerMovement.h"
#include "StatisticManager.h"

Player::Player()
	: m_pTex(nullptr)
{
	//m_pTex = new Texture;
	//wstring path = GET_SINGLE(ResourceManager)->GetResPath();
	//path += L"Texture\\planem.bmp";
	//m_pTex->Load(path);
	//m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Player", L"Texture\\planem.bmp");

	//GetComponent<Animator>()->CreateAnimation(L"JiwooFront", m_pTex, Vec2(0.f, 150.f),
	//Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.1f);

	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Jiwoo", L"Texture\\MinsungMove.bmp");
	this->AddComponent<Collider>();
	AddComponent<Animator>();
	GetComponent<Animator>()->CreateAnimation(L"Move", m_pTex, Vec2(0.f, 0.f),
		Vec2(32.f, 32.f), Vec2(32.f, 0.f), 2, 0.08f, true);
	GetComponent<Animator>()->CreateAnimation(L"Idle", m_pTex, Vec2(0.f, 0.f),
		Vec2(32.f, 32.f), Vec2(32.f, 0.f), 1, 0.08f, true);
	GetComponent<Animator>()->PlayAnimation(L"Idle", true);
	AddComponent<MicJumpObserver>();
	AddComponent<Rigidbody>();
	AddComponent<PlayerMovement>();

	SetCheckPoint({ 0.f, 500.f });
}
Player::~Player()
{
	//if (nullptr != m_pTex)
	//	delete m_pTex;
}
void Player::Update()
{
	Vec2 vPos = GetPos();

	int buf = 0;
	bool prev = b_moving;

	b_moving = false;
	//if(GET_KEY(KEY_TYPE::LEFT))
	if (GET_KEY(KEY_TYPE::A))
	{
		//vPos.x -= 200.f * fDT;
		GetComponent<Rigidbody>()->AddForce({ -2700.f,0.f });
		b_moving = true;
		buf++;
	}
	if (GET_KEY(KEY_TYPE::D))
	{
		//vPos.x += 200.f * fDT;
		GetComponent<Rigidbody>()->AddForce({ 2700.f,0.f });
		b_moving = true;
		buf++;
	}
	if (GET_KEYDOWN(KEY_TYPE::SPACE))
	{
		//CreateProjectile();
		//GetComponent<Rigidbody>()->AddImpulse({ 0, -1500 });
	}
	SetPos(vPos);
	GetComponent<MicJumpObserver>()->Update();
	GetComponent<PlayerMovement>()->HandleJump();

	if (vPos.y > SCREEN_WIDTH + 500.f)
	{
		GoCheckPoint();
	}


	if (buf == 2) { GetComponent<Animator>()->PlayAnimation(L"Idle", true); b_moving = false; }
	else if (b_moving != prev)
	{
		if (b_moving)
			GetComponent<Animator>()->PlayAnimation(L"Move", true);
		else
			GetComponent<Animator>()->PlayAnimation(L"Idle", true);
	}
}

void Player::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	//RECT_RENDER(_hdc, vPos.x, vPos.y
	//	, vSize.x, vSize.y);
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	//::BitBlt(_hdc
	//	, (int)(vPos.x - vSize.x / 2)
	//	, (int)(vPos.y - vSize.y / 2)
	//	, width, height,
	//	m_pTex->GetTexDC()
	//	,0,0,SRCCOPY
	//);
	/*::TransparentBlt(_hdc
		, (int)(vPos.x - width / 2)
		, (int)(vPos.y - height / 2)
		, width, height,
		m_pTex->GetTexDC()
		, 0, 0,width, height, RGB(255,0,255));*/
	ComponentRender(_hdc);
	//::StretchBlt();
	//::AlphaBlend();
	//::PlgBlt();
}

void Player::OnMicJump(const float& power)
{
	//cout << power << endl;
	Rigidbody* rb = GetComponent<Rigidbody>();
	if (rb != nullptr && rb->IsGrounded())
	{
		//rb->AddImpulse(Vec2(0.f, power * -900.0f));
	}
}

void Player::SetCheckPoint(Vec2 pos)
{
	v_checkPoint = pos;
}

void Player::GoCheckPoint()
{
	GET_SINGLE(StatisticManager)->AddFall();
	GET_SINGLE(ResourceManager)->Play(L"Respawn");
	GetOrAddComponent<Rigidbody>()->SetVelocity(Vec2(0,0));
	SetPos(v_checkPoint);
}

void Player::CreateProjectile()
{
	Projectile* pProj = new Projectile;
	Vec2 vPos = GetPos();
	vPos.y -= GetSize().y / 2.f;
	pProj->SetPos(vPos);
	pProj->SetSize({30.f,30.f});
	// �� -> ����: PI / 180
	//pProj->SetAngle(PI / 4 * 7.f); // 1
	//static float angle = 0.f;
	//pProj->SetAngle(angle * PI / 180); // 2
	//angle += 10.f;
	pProj->SetDir({0.f, -1.f});
	pProj->SetName(L"PlayerBullet");
	//Vec2 a = { 10.f, 10.f };
	//Vec2 b = { 0.f, 0.f };
	//Vec2 c = a / b;

	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pProj, LAYER::PROJECTILE);
}
