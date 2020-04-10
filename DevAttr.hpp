#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <boost/tuple/tuple.hpp>
#include <initializer_list>
#include <list>

#include "Outlet.hpp"


struct DevInfo{

public:
	std::string name;
	std::string zigbeeModel;
	std::string model;
	std::string vendor;
	std::list<OutletAttr*> outlet;
};




class DevAttr
{
public:
	DevAttr()
	{

	}

	DevAttr(DevAttr* dattr);
	DevAttr(DevInfo& devInfo);
	
	
	DevAttr(std::initializer_list<OutletAttr*> list, std::string name, std::string zigbeeModel, std::string model, std::string vendor);

	friend  std::ostream & operator << (std::ostream& out, DevAttr& da);


public:
	std::string getName(){return m_name;}
	std::string getZigbeeModel(){return m_zigbeeModel;}
	std::string getModel(){return m_model;}
	std::string getVendor(){return m_model;}
	OutletAttr* getOutlet(int Outlet)
	{
		if (Outlet >= m_Outlet.size())
		{
			return nullptr;
		}
		return m_Outlet.at(Outlet);
	}
	std::vector<OutletAttr*>& getOutlet()
	{
		return m_Outlet;
	}

	bool match(int type, int subType, int unit);

private:
	std::string m_name;
	std::string m_zigbeeModel;
	std::string m_model;
	std::string m_vendor;
	std::vector<OutletAttr*> m_Outlet; 
};





