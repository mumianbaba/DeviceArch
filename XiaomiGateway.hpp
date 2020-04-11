#pragma once

#include <iostream>
#include <map>
#include <list>
#include <string>

#include "Outlet.hpp"
#include "DevAttr.hpp"
#include "Device.hpp"


typedef std::map <std::string, DevAttr*> AttrMap;
typedef std::map <std::string, std::shared_ptr<Device>> DeviceMap;


class XiaomiGateway
{

public:
	XiaomiGateway();
	~XiaomiGateway();
	
	static void initDeviceAttrMap(const DevInfo devInfo[], int size);
	static void addDeviceToMap(std::string& mac, std::shared_ptr<Device> ptr);
	static const DevAttr* findDevAttr(std::string& model);

	std::shared_ptr<Device> getDevice(std::string& mac);
	std::shared_ptr<Device> getDevice(unsigned int ssid, int type, int subType, int unit);
		
protected:


private:
	static AttrMap m_attrMap;
	static DeviceMap m_deviceMap;
};




