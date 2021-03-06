#include <iostream>
#include <string>
#include <map>
#include "Device.hpp"
#include "DevAttr.hpp"
#include "Outlet.hpp"


bool DevID::match(std::string& mac)
{
	return (m_mac == mac);
}

bool DevID::match(unsigned int ssid)
{
	for (const auto &itt : m_ssidList)
	{
		if (itt.first == ssid)
		{
			return true;
		}
	}
	return false;
}





/*
 *  class  Device
 *
 *
*/
Device::Device(DevAttr* devAttr, std::string mac):m_devAttr(devAttr)
{
	std::vector<SsidPair> result;
	for(int ii = 0; ;ii++)
	{
		OutletAttr* outlet = m_devAttr->getOutlet(ii);
		if (outlet == nullptr)
		{
			break;
		}
		SsidPair ssid = outlet->idConverter(mac);
		result.emplace_back(ssid);
	}

	m_devID.initID(mac, result);
}


bool Device::writeTo(const unsigned char* packet, int len, std::string& gwMac, std::string& key, void  * miGateway)
{
		
	int type = pTypeGeneralSwitch;
	int subtype= sSwitchGeneralSwitch;
	int uint = 1;


	auto Outlet = m_devAttr->getOutlet();
	for (const auto & itt : Outlet)
	{
		if (itt->match(type, subtype, uint) == true)
		{
			std::string mac = m_devID.getMac();
			std::string model = m_devAttr->getModel();

			itt->writeTo(packet, len, mac, model, key, gwMac, miGateway);
			break;
		}
	}
	return true;
}




bool Device::recvFrom(std::string& msg, void *miGateway)
{

	auto Outlet = m_devAttr->getOutlet();
	for (const auto & itt : Outlet)
	{
		itt->recvFrom(msg, miGateway);
	}
	return true;
}



bool Device::match(std::string& mac)
{
	return m_devID.match(mac);
}


bool Device::match(unsigned int ssid, int type, int subType, int unit)
{
	return (m_devID.match(ssid) && m_devAttr->match(type, subType, unit));
}






