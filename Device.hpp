#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <boost/tuple/tuple.hpp>
#include <initializer_list>
#include <memory>
#include <list>

#include "XiaoMiType.hpp"
#include "Device.hpp"
#include "DevAttr.hpp"
#include "Outlet.hpp"




class DevID
{

public:
	DevID()
	{

	}
	void initID(std::string mac, std::vector<SsidPair> ssidList) 
	{
		m_mac = mac;
		m_ssidList = ssidList;
	}

	std::string getMac(){return m_mac;}
	const std::vector<SsidPair>& getSsid(){return m_ssidList;}
	bool match(std::string& mac);	
	bool match(unsigned int ssid);

private:
	std::string m_mac;
	std::vector<SsidPair> m_ssidList;
};



class Device
{
	public:
		Device(DevAttr* devAttr, std::string mac);
	public:
		virtual bool recvFrom(std::string& msg, void *miGateway);
	
		virtual bool writeTo(const unsigned char* packet, int len, std::string& gwMac, std::string& key, void  * miGateway);

	public:
		bool match(std::string& mac);
		bool match(unsigned int ssid, int type, int subType, int unit);
	private:
	
		DevAttr* m_devAttr;
		DevID	m_devID;

};




