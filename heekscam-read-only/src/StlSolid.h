// StlSolid.h
// Copyright (c) 2009, Dan Heeks
// This program is released under the BSD license. See the file COPYING for details.

#include "HeeksObj.h"

class CStlTri{
public:
	float x[3][3];
	CStlTri(){}
	CStlTri(const float* t);
	CStlTri(const double* t);
};

class CStlSolid:public HeeksObj{
private:
	HeeksColor m_color;
	int m_gl_list;
	int m_edge_gl_list;
	CBox m_box;
	wxString m_title;

	void read_from_file(const wxChar* filepath);

public:
	std::list<CStlTri> m_list;
	int m_clicked_triangle;

	CStlSolid();
	CStlSolid(const HeeksColor* col);
	CStlSolid(const wxChar* filepath, const HeeksColor* col);
#ifdef UNICODE
	CStlSolid(const std::wstring& filepath);
#endif
	CStlSolid( const CStlSolid & rhs );
	~CStlSolid();

	virtual const CStlSolid& operator=(const CStlSolid& s);

	int GetType()const{return StlSolidType;}
	long GetMarkingMask()const{return MARKING_FILTER_STL_SOLID;}
	int GetIDGroupType()const{return SolidType;}
	const wxChar* GetTypeString(void)const{return _("STL Solid");}
	const wxBitmap &GetIcon();
	void GetProperties(std::list<Property *> *list);
	void glCommands(bool select, bool marked, bool no_color);
	void GetGripperPositions(std::list<GripData> *list, bool just_for_endof);
	void GetTools(std::list<Tool*>* t_list, const wxPoint* p);
	void SetColor(const HeeksColor &col){ m_color = col; }
	const HeeksColor* GetColor()const{return &m_color;}
	void GetBox(CBox &box);
	void KillGLLists(void);
	void ModifyByMatrix(const double* m);
	const wxChar* GetShortString(void)const{return m_title.c_str();}
	bool CanEditString(void)const{return true;}
	void OnEditString(const wxChar* str);
	void GetTriangles(void(*callbackfunc)(const double* x, const double* n), double cusp, bool just_one_average_normal = true);
	void CopyFrom(const HeeksObj* object);
	HeeksObj *MakeACopy()const;
	void WriteXML(TiXmlNode *root);
	bool IsDifferent(HeeksObj* obj);
	void SetClickMarkPoint(MarkedObject* marked_object, const double* ray_start, const double* ray_direction);
	bool UsesCustomSubNames(){ return true; }

	static HeeksObj* ReadFromXMLElement(TiXmlElement* pElem);

	void AddTriangle(float* t); // 9 floats
};

