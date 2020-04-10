#include "Outlet.hpp"
#include <iostream>
#include <string>

inline std::ostream & operator << (std::ostream& out, OutletAttr& oa)
{
	out<<"type:"<<oa.m_type<<std::endl;
	out<<"subType:"<<oa.m_subType<<std::endl;
	out<<"swType:"<<oa.m_swType<<std::endl;
	out<<"unit:"<<oa.m_unit<<std::endl;
	out<<"direction:"<<oa.m_direction<<std::endl;
	out<<"opts:"<<oa.m_opts<<std::endl;
	return out;
}



std::ostream & operator << (std::ostream& out, OutletAttr* poa)
{
	if (poa == nullptr)
	{
		out<<"ptr null"<<std::endl;
		return out;
	}
	out<<"type:"<<poa->m_type<<std::endl;
	out<<"subType:"<<poa->m_subType<<std::endl;
	out<<"swType:"<<poa->m_swType<<std::endl;
	out<<"unit:"<<poa->m_unit<<std::endl;
	out<<"direction:"<<poa->m_direction<<std::endl;
	out<<"opts:"<<poa->m_opts<<std::endl;
	return out;
}




OutletAttr::OutletAttr(int type, int subType, int swType, int unit, int direction, std::string opts)
:m_type(type), m_subType(subType),m_swType(swType),m_unit(unit),m_direction(direction),m_opts(opts)
{

}


inline unsigned int OutletAttr::macToUint(std::string& mac)
{
	unsigned long long sID = std::stoull(mac, NULL, 16);
	return (sID & 0xffffffff);
}


SsidPair OutletAttr::idConverter(std::string& mac)
{
	
	unsigned int rowId;
	char szTmp[64];

	rowId = macToUint(mac);
	sprintf(szTmp, "%08X", rowId);
	std::string  strSsid = szTmp;
	return std::make_pair(rowId, strSsid);
}

bool OutletAttr::match(int type, int subType, int unit)
{
	if (type == m_type && subType == m_subType && unit == m_unit)
	{
		return true;
	}
	return false;
}




OnOffOutlet::OnOffOutlet(int unit, int dir, std::initializer_list<Rule_OnOff> list)
	:OutletAttr(pTypeGeneralSwitch, sSwitchGeneralSwitch, STYPE_OnOff, static_cast<int>(unit), static_cast<int>(dir), "")
{
	std::cout<<"OnOffOutlet init list size:"<<list.size()<<std::endl;
	for (const auto &itt : list)
	{
		m_rule.emplace_back(itt);
	}
	std::cout<<"OnOffOutlet rule number:"<<list.size()<<std::endl;
}


bool OnOffOutlet::recvFrom(std::string& root, void * miGateway)
{
	std::cout<<"OnOffOutlet recvFrom"<<std::endl;
}

bool OnOffOutlet::writeTo(const unsigned char* packet, int len, std::string& mac, std::string& model,std::string& gwMac,  std::string& key, void * miGateway)
{
	std::cout<<"OnOffOutlet writeTo"<<std::endl;
}








