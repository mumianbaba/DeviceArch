#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <functional>
#include "XiaomiGateway.hpp"

namespace Json
{
	class Value{
		public:
			Value(){}
			bool isArray(){return true;}
			bool isMember(){return true;}
			int size(){return 3;}
			
	};
}
class GetValue {

    public:
        GetValue(const std::string& key): m_key(key)
		{
            std::cout << "hello Action:" << key << std::endl;
        }
		
		
        std::string actionRecvFrom(Json::Value& params){
		
			if (false == params.isArray()){
				std::cout << "input params not a array" <<std::endl;
				return "";
			}
			std::string value = "";
			
			for (int ii = 0; ii < params.size(); ii++)
			{
				//if (params[ii].isMember(m_key))
				{
					//value = params[ii][m_key].asString();
					break;

				}
			}
			return value;
        }

private:
    std::string m_key;
};

#define RSSI_KEY  "link_quality"
#define BATTERY_KEY  "battery_voltage"


class RssiAction : GetValue{

public:
	RssiAction():GetValue(RSSI_KEY)
	{
	}
	std::string rssiRecv(Json::Value& params)
	{
		return actionRecvFrom(params);
	}
};

class BatteryAction : GetValue{

public:
	BatteryAction():GetValue(BATTERY_KEY)
	{
	}
	std::string batteryRecv(Json::Value& params)
	{
		return actionRecvFrom(params);
	}
};