#pragma once
#include "Singleton.h"
#include <map>
#include <Xinput.h>



namespace HoneyEngine
{
	enum class InputState
	{
		Released,
		Pressed,
		Down
	};

	struct InputAction
	{
		InputAction(InputState triggerState = InputState::Pressed, int keyboardCode = -1)
			: m_TriggerState(triggerState)
			, m_KeyCode(keyboardCode)
			, m_IsTriggered(false)
		{
		}

		InputState m_TriggerState;
		int m_KeyCode;
		bool m_IsTriggered;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();

		void Initialize();
		void Update();
		void AddInputAction(const InputAction& action, const int actionID);
		bool IsActionTriggered(const int actionID);

		void SetCursorVisibility(const bool visible) { ShowCursor(visible); }
		POINT GetMouseMovement() const { return m_MouseMovement; }
		POINT GetMousePosition(const bool previousFrame = false) const { return (previousFrame) ? m_OldMousePos : m_CurrMousePos; }

		bool IsKeyDown(const int key, const bool previousFrame = false) const;

	private:
		void UpdateKeyboardStates();

		std::map<int, InputAction> m_InputActions;

		int m_CurrStateIdx = 0;
		PBYTE m_pKeyboardState[2] = { nullptr, nullptr };

		POINT m_CurrMousePos;
		POINT m_OldMousePos;
		POINT m_MouseMovement;

		bool m_IsInitialized = false;
	};

}
