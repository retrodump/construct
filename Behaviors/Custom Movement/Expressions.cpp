// Include StdAfx
#include "StdAfx.h"

//////////////////////////////////////////////////////////////////////////////////
// Built-in expressions
//////////////////////////////////////////////////////////////////////////////////

// Return the Default Value.  This is the value to be returned if your object name
// is used without an expression name, eg. in "Counter + 1".
// Parameters can be passed, eg. MyObject(3,7).  You can check ExpReturn::Type() or GetNumParams() to check for overloads.
long ExtObject::ReturnDefaultValue(LPVAL theParams, ExpReturn& ret)
{
	return ret = 0;
}

// Called for undefined expression names, if your extension allows it.
// Eg: MyObject.UndefinedExpression(3,4,5) calls this routine with
// "UndefinedExpression" as the expression name.  OF_UNDEFINEDEXPRESSIONS must be specified in Main.h.
long ExtObject::ReturnUndefinedExpression(CString& expName, LPVAL theParams, ExpReturn& ret)
{
	return ret = 0;
}

//////////////////////////////////////////////////////////////////////////////////
// Expressions
//////////////////////////////////////////////////////////////////////////////////

long ExtObject::eSpeed (LPVAL theParams, ExpReturn& ret)
{
	return ret = m_speed;
}
long ExtObject::eAngle (LPVAL theParams, ExpReturn& ret)
{
	return ret = DEGREES(m_angle);
}
long ExtObject::eXspeed (LPVAL theParams, ExpReturn& ret)
{
	float dx, dy;
	ComponentToVector(m_speed, m_angle, dx, dy);
	return ret = dx;
}
long ExtObject::eYSpeed (LPVAL theParams, ExpReturn& ret)
{
	float dx, dy;
	ComponentToVector(m_speed, m_angle, dx, dy);
	return ret = dy;
}

/*long ExtObject::eMyExpression(LPVAL params, ExpReturn& ret)
{
	// Return 0 using ExpReturn's operator=
	// Use ret.ReturnString() for strings.
	return ret = 0;
}*/