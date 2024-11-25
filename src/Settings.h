/// <summary>
/// A place with some bools and an enum to track which buttons are toggled.
/// </summary>
class Settings
{
public:

	enum Mode 
	{
		view,
		move,
		edit
	};

	inline static bool appRunning = true;
	static inline Mode currentMode = Mode::edit;
	static inline bool snapping = false;
	static inline bool showNewLine = true;
	static inline bool showShortcuts = false;
};