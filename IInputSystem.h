#pragma once

namespace Engine {
	enum class Command {
		None,
		MoveUp,
		MoveDown,
		MoveLeft,
		MoveRight,
		Confirm,
		Exit
	};

	class IInputSystem {
	public:
		virtual ~IInputSystem() = default;

		virtual Command getCommand() = 0;
	};
}