#pragma once

class Cell
{
public:
	Cell();
	~Cell();

	inline void setState(CELL_STATE state) { m_state = state; }
	inline CELL_STATE getState() { return m_state; }
private:
	CELL_STATE m_state;
};