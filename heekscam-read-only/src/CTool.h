
// CTool.h
/*
 * Copyright (c) 2009, Dan Heeks, Perttu Ahola
 * This program is released under the BSD license. See the file COPYING for
 * details.
 */

#pragma once

#include "Op.h"
#include "HeeksCNCTypes.h"

#include <vector>
#include <algorithm>

class CTool;
class CSurface;

class CTool: public HeeksObj {
public:
	typedef enum {
		eDrill = 0,
		eCentreDrill,
		eEndmill,
		eSlotCutter,
		eBallEndMill,
		eChamfer,
		eEngravingTool,
		eUndefinedToolType
	} eToolType;

	typedef enum {
		eHighSpeedSteel = 0,
		eCarbide,
		eUndefinedMaterialType
	} eMaterial_t;


	// The G10 command can be used (within EMC2) to add a tool to the tool
	// table from within a program.
	// G10 L1 P[tool number] R[radius] X[offset] Z[offset] Q[orientation]

	int m_material;	// eMaterial_t - describes the cutting surface type.
	double m_diameter;
	double m_tool_length_offset;
	double m_corner_radius;
	double m_flat_radius;
	double m_cutting_edge_angle;
	double m_cutting_edge_height;	// How far, from the bottom of the cutter, do the flutes extend?
	int	m_type;
	int m_automatically_generate_title;	// Set to true by default but reset to false when the user edits the title.
	std::wstring m_title;
	int m_tool_number;
	HeeksObj *m_pToolSolid;

	//	Constructors.
	CTool(const wxChar *title = NULL, int type = eDrill, const int tool_number = 0) : m_tool_number(tool_number), m_pToolSolid(NULL)
	{
        ReadDefaultValues();
		m_type = type;
		if (title != NULL)m_title = title;
		else m_title = GetMeaningfulName(wxGetApp().m_view_units);
	} // End constructor

    CTool( const CTool & rhs );
    CTool & operator= ( const CTool & rhs );

	~CTool();


	void set_initial_values();
	void write_values_to_config();
	void WriteXMLAttributes(TiXmlNode* pElem);
	void ReadParametersFromXMLElement(TiXmlElement* pElem);

	double ReasonableGradient(const int type) const;

	bool operator== ( const CTool & rhs ) const;
	bool operator!= ( const CTool & rhs ) const { return(! (*this == rhs)); }

	bool IsDifferent( HeeksObj *other ) { return(*this != (*(CTool *)other)); }

	 // HeeksObj's virtual functions
        int GetType()const{return ToolType;}
	const wxChar* GetTypeString(void) const { return _("Tool"); }
        HeeksObj *MakeACopy(void)const;

        void WriteXML(TiXmlNode *root);
        static HeeksObj* ReadFromXMLElement(TiXmlElement* pElem);

	// program whose job is to generate RS-274 GCode.
	Python AppendTextToProgram();
	Python OCLDefinition(CSurface* surface)const;

	void GetProperties(std::list<Property *> *list);
	void CopyFrom(const HeeksObj* object);
	bool CanAddTo(HeeksObj* owner);
	const wxBitmap &GetIcon();
    const wxChar* GetShortString(void)const{return m_title.c_str();}
	void glCommands(bool select, bool marked, bool no_color);
	void KillGLLists(void);
	void GetTools(std::list<Tool*>* t_list, const wxPoint* p);
    bool CanEditString(void)const{return true;}
    void OnEditString(const wxChar* str);
	void WriteDefaultValues();
	void ReadDefaultValues();
	HeeksObj* PreferredPasteTarget();

	static CTool *Find( const int tool_number );
	static int FindTool( const int tool_number );
	static int FindToolType( const int tool_number );
	static bool IsMillingToolType( int type );
	static int FindFirstByType( const int type );
	wxString GetMeaningfulName(double units) const;
	wxString ResetTitle();
	static wxString FractionalRepresentation( const double original_value, const int max_denominator = 64 );
	TopoDS_Shape GetShape() const;
	TopoDS_Face  GetSideProfile() const;
	double CuttingRadius(const bool express_in_program_units = false, const double depth = -1) const;
	static int CutterType( const int tool_number );
	static CTool::eMaterial_t CutterMaterial( const int tool_number );
	void SetDiameter( const double diameter );
	Python OpenCamLibDefinition(const unsigned int indent = 0)const;
	Python VoxelcutDefinition()const;

	void GetOnEdit(bool(**callback)(HeeksObj*));
	void OnChangeViewUnits(const double units);

private:
	void DeleteSolid();

public:
}; // End CTool class definition.

