#pragma once

#include "base/module.h"

#include "../editing/base/edit-mode.h"

#include "../editing/note-edit-mode.h"
#include "../editing/select-edit-mode.h"

/*
* special edit-mode actions cannot be directly called by the program, but must be interfaced through the edit module.
*/

class EditModule : public Module, public EditMode
{
public: //module overrides

	bool Tick(const float& InDeltaTime) override;

public: //edit-mode overrides

	bool OnMouseLeftButtonClicked(const bool InIsShiftDown) override;
	bool OnMouseLeftButtonReleased() override;

	bool OnMouseRightButtonClicked(const bool InIsShiftDown) override;
	bool OnMouseRightButtonReleased() override;

	bool OnMouseDrag() override;

	bool OnCopy() override;
	bool OnPaste() override;

	void SubmitToRenderGraph(TimefieldRenderGraph& InOutTimefieldRenderGraph) override;

public:

	void SetChart(Chart* const InOutChart);
	void SetCursorData(const Cursor& InCursor);

	template<class T>
	void SetEditMode()
	{
		_EditModes[_SelectedEditMode]->OnReset();
		_SelectedEditMode = _EditModes.GetIndex<T>();
	}

private:

	size_t _SelectedEditMode = 0;

	EditModeCollection<SelectEditMode, NoteEditMode> _EditModes;
};