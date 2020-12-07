#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <tuple>

typedef std::map<std::string, std::string> ActionParam;

class ReadAction {

    public:
        ReadAction(const std::string& key): m_key(key)
		{
            std::cout << "hello ReadAction:" << key << std::endl;
        }

        std::string actionRecvFrom(const ActionParam& params){
            std::string value = "";
            try{
                auto it = param.find(key);
                if (it != param.end()){
                    value = param.at(key);
                }
            }
            catch(const std::exception& ex){
                Log(LOG_ERROR, "%s stoi error: %s", key.c_str(), ex.what());
            }
            if (!value.empty()){
                m_value = value;
            }
            return value;
        }

        const std::string& getActionValue()
        {
            return m_value;
        }
private:
    std::string m_key;
    std::string m_value;
};

#define RSSI_VALUE_KEY  "link_quality"
#define RSSI_RANK_KEY  "link_rank"
#define BATTERY_VALUE_KEY  "battery_voltage"
#define BATTERY_RANK_KEY  "battery_rank"


class RssiAction{

public:
	RssiAction(){
        auto  value= std:make_shared<ReadAction>(RSSI_VALUE_KEY);
        auto  rank= std:make_shared<ReadAction>(RSSI_LEVEL_KEY);
        m_rssiAction.emplace_back(value);
        m_rssiAction.emplace_back(rank);
    }
	void rssiUpadte(const ActionParam& params)
	{
        for (auto & itt : m_rssiAction){
            itt->actionRecvFrom(params)
        }
        std::string value = m_rssiAction[0]->getActionValue();
        std::string rank = m_rssiAction[1]->getActionValue();
        return {value, rank};
	}
    const std::tuple<std::string, std::string> rssiGet()
    {
        std::string value = m_rssiAction[0]->getActionValue();
        std::string rank = m_rssiAction[1]->getActionValue();
        return {value, rank};
    }
private:
    std::vector<std::shared_ptr<ReadAction>> m_rssiAction;
};


class BatteryAction {

public:
	BatteryAction(){
        auto  value= std:make_shared<ReadAction>(BATTERY_VALUE_KEY);
        auto  rank= std:make_shared<ReadAction>(BATTERY_RANK_KEY);
        m_batAction.emplace_back(value);
        m_batAction.emplace_back(rank);
    }
	 const std::tuple<std::string, std::string>  batteryUpadte(const ActionParam& params)
	{
        for (auto & itt : m_batAction){
            itt->actionRecvFrom(params)
        }
        std::string value = m_batAction[0]->getActionValue();
        std::string rank = m_batAction[1]->getActionValue();
        return {value, rank};
	}
    const std::tuple<std::string, std::string>  batteryGet()
    {
        std::string value = m_batAction[0]->getActionValue();
        std::string rank = m_batAction[1]->getActionValue();
        return {value, rank};
    }
private:
    std::vector<std::shared_ptr<ReadAction>> m_batAction;
};