
#include <iostream>
#include <map>
#include "Outlet.hpp"
#include "DevAttr.hpp"
#include "Device.hpp"
#include "XiaomiGateway.hpp"
#include "SupportDevice.hpp"

using namespace XiaoMi;

AttrMap XiaomiGateway::m_attrMap;
DeviceMap XiaomiGateway::m_deviceMap;



XiaomiGateway::XiaomiGateway()
{
	if (m_attrMap.empty())
	{
		initDeviceAttrMap(devInfoTab, sizeof(devInfoTab)/sizeof(devInfoTab[0]));
	}
}


XiaomiGateway::~XiaomiGateway()
{
	std::cout<<"~XiaomiGateway"<<std::endl;
}


void XiaomiGateway::initDeviceAttrMap(const DevInfo devInfo[], int size)
{
	int ii;
	for (ii = 0; ii < size; ii++)
	{
		m_attrMap.emplace(devInfo[ii].zigbeeModel, new DevAttr(devInfo[ii]));
	}
	std::cout<<"support device number:"<<m_attrMap.size()<<std::endl;
	for (const auto & itt : m_attrMap)
	{
		std::cout<<"zigbee model:"<<itt.first<<std::endl;
	}
	return;
}


const DevAttr* XiaomiGateway::findDevAttr(std::string& model)
{
	auto it = m_attrMap.find(model);
	if (it == m_attrMap.end())
	{
		return NULL;
	}
	return it->second;
}


void XiaomiGateway::addDeviceToMap(std::string& mac, std::shared_ptr<Device> ptr)
{
	m_deviceMap.emplace(mac, ptr);
	std::cout<<"add device to map mac:"<<mac<<std::endl;
}

void XiaomiGateway::delDeviceFromMap(std::string& mac)
{
	m_deviceMap.erase(mac);
	std::cout<<"delDeviceFromMap mac:"<<mac<<std::endl;
}


std::shared_ptr<Device> XiaomiGateway::getDevice(std::string& mac)
{
	std::shared_ptr<Device> ptr;
	auto it = m_deviceMap.find(mac);
	if (it == m_deviceMap.end())
	{
		std::cout<<"error: getDevice failed mac:"<<mac<<std::endl;
		return ptr;
	}
	return it->second;
}

std::shared_ptr<Device> XiaomiGateway::getDevice(unsigned int ssid, int type, int subType, int unit)
{
	bool res;
	std::shared_ptr<Device> ptr;
	for (const auto itt : m_deviceMap)
	{
		res = itt.second->match(ssid, type, subType, unit);
		if (true == res)
		{
			ptr = itt.second;
			break;
		}
	}
	if (ptr.get() == nullptr)
	{
		std::cout<<"error: getDevice failed ssid:"<<std::hex<<ssid <<"  type:"<<std::hex<<type;
		std::cout<<" subType: "<<std::hex<<subType<<"  unit:"<<unit<<std::endl;
	}
	return ptr;
}

