#pragma once

template <typename T>
void SafeDelete(T& Obj)
{
	if (Obj)
	{
		delete Obj;
		Obj = nullptr;
	}
}

template <typename T>
bool LessY(T& dst, T& src)
{
	return dst->GetInfo().fY < src->GetInfo().fY;
}