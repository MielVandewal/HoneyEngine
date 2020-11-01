#include "HoneyEnginePCH.h"
#include "InputManager.h"
#include "GameContext.h"

HoneyEngine::InputManager::InputManager()
	: m_pKeyboardState{ nullptr, nullptr }
	, m_CurrMousePos{ 0, 0 }
	, m_OldMousePos{ 0, 0 }
	, m_MouseMovement{ 0, 0 }
	, m_IsInitialized{ false }
{
}

HoneyEngine::InputManager::~InputManager()
{
	SafeDeleteArray(m_pKeyboardState[0]);
	SafeDeleteArray(m_pKeyboardState[1]);

	m_IsInitialized = false;
}

void HoneyEngine::InputManager::Initialize()
{
	if (m_IsInitialized)
		return;

	m_pKeyboardState[0] = new BYTE[256];
	m_pKeyboardState[1] = new BYTE[256];

	bool gotKeyboardState = false;
	gotKeyboardState = GetKeyboardState(m_pKeyboardState[0]);
	gotKeyboardState = GetKeyboardState(m_pKeyboardState[1]);

	m_IsInitialized = true;
}

void HoneyEngine::InputManager::AddInputAction(const InputAction& action, const int actionID)
{
	//check if the action is already mapped 
	if (m_InputActions.find(actionID) == m_InputActions.end())
		m_InputActions[actionID] = action;
}

bool HoneyEngine::InputManager::IsActionTriggered(const int actionID)
{
	//check if the action is in the map if so return the isTriggered else return false. 
	if (m_InputActions.find(actionID) != m_InputActions.end())
		return m_InputActions[actionID].m_IsTriggered;
	return false;
}

void HoneyEngine::InputManager::UpdateKeyboardStates()
{
	//swap the index of the current/previous keyboardstate
	m_CurrStateIdx = 1 - m_CurrStateIdx;

	//get keyboard current keyboardstate
	for (int i = 0; i < 256; ++i)
		m_pKeyboardState[m_CurrStateIdx][i] = (char)(GetAsyncKeyState(i) >> 8);
}

void HoneyEngine::InputManager::Update()
{
	UpdateKeyboardStates();
	for (auto it = m_InputActions.begin(); it != m_InputActions.end(); ++it)
	{
		InputAction* currAction = &(it->second);
		currAction->m_IsTriggered = false;

		//the first part of this if statement checks the previous frame and will return false 
		//if the triggerstate is equals to pressed/1.
		//the second part of this if statement checks the current frame and will return false 
		//if the triggerstate is equals to released/0.
		bool test1 = bool((int(currAction->m_TriggerState) % 2)) != IsKeyDown(currAction->m_KeyCode, true);
		bool test2 = (bool(currAction->m_TriggerState) == IsKeyDown(currAction->m_KeyCode));
		if (test1 && test2)
		{
			currAction->m_IsTriggered = true;
		}
	}

	//Set Mouse Position
	m_OldMousePos = m_CurrMousePos;
	if (GetCursorPos(&m_CurrMousePos))
		ScreenToClient(GameContext::GetInstance()->pWindow->GetWindowHandle(), &m_CurrMousePos);

	m_MouseMovement.x = m_CurrMousePos.x - m_OldMousePos.x;
	m_MouseMovement.y = m_CurrMousePos.y - m_OldMousePos.y;
}

bool HoneyEngine::InputManager::IsKeyDown(const int key, const bool previousFrame) const
{
	//check if key is within the 
	if (key <= 0x00 && key > 0xFE)
		return false;
	//then return the state based on if you want the previous state or the current state
	if (previousFrame)
		return (m_pKeyboardState[1 - m_CurrStateIdx][key] & 0xF0) != 0;
	return (m_pKeyboardState[m_CurrStateIdx][key] & 0xF0) != 0;
}