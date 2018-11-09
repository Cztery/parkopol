#pragma once


class park_unit
{
public:
	park_unit *m_parent;
	std::vector <park_unit *> m_children;
	int m_depthLevel;
	string m_unitname;
	int m_childId;

	park_unit();
	~park_unit();


};

