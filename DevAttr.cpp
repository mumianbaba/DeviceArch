#include <iostream>
#include <string>
#include "DevAttr.hpp"

std::ostream & operator << (std::ostream& out, DevAttr& da)
{
	out<<std::endl;
	out<<"---------devattr----------------"<<std::endl;
	out<<"name:"<<da.m_name<<std::endl;
	out<<"zigbeeModel:"<<da.m_zigbeeModel<<std::endl;
	out<<"model:"<<da.m_model<<std::endl;
	out<<"vendor:"<<da.m_vendor<<std::endl;
	out<<"outlet number:"<<da.m_Outlet.size()<<std::endl;
	out<<std::endl;
	int ii = 0;
	for (const auto &itt : da.m_Outlet)
	{
		out<<"---------outlet:"<<ii++<<"--------"<<std::endl;
		out<<itt;
		out<<std::endl;
	}
	out<<std::endl;
	return out;
}


DevAttr::DevAttr(DevAttr* dattr)
{
	if (dattr != nullptr)
	{
		m_name = dattr->m_name;
		m_zigbeeModel = dattr->m_zigbeeModel;
		m_model = dattr->m_model;
		m_vendor = dattr->m_vendor;
	}
}

DevAttr::DevAttr(DevInfo& devInfo)
{
	m_name =devInfo.name;
	m_zigbeeModel = devInfo.zigbeeModel;
	m_model = devInfo.model;
	m_vendor = devInfo.vendor;
	std::cout<<"DevAttr devInfo list size:"<<devInfo.outlet.size()<<std::endl;

	for (const auto &itt : devInfo.outlet)
	{
		m_Outlet.push_back(itt);
	}
	
	std::cout<<"DevAttr Outlet number:"<<m_Outlet.size()<<std::endl;
}


DevAttr::DevAttr(std::initializer_list<OutletAttr*> list, std::string name, std::string zigbeeModel, std::string model, std::string vendor)
{
	m_name = name;
	m_zigbeeModel = zigbeeModel;
	m_model = model;
	m_vendor = vendor;
	std::cout<<"DevAttr list size:"<<list.size()<<std::endl;

	for (const auto &itt : list)
	{
		m_Outlet.push_back(itt);
	}
	
	std::cout<<"DevAttr Outlet number:"<<m_Outlet.size()<<std::endl;
}


bool DevAttr::match(int type, int subType, int unit)
{
	for(const auto &itt : m_Outlet)
	{
		if (itt->match(type, subType, unit) == true)
		{
			return true;
		}
	}
	return false;
}









