#include "stdafx.h"
#include "AISetting.h"

const std::string& AISetting::getName() const
{
	return name;
}

const bool& AISetting::isDeletable()
{
	return deletable;
}
