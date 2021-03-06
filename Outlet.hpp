#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <boost/tuple/tuple.hpp>
#include <initializer_list>


#include "XiaoMiType.hpp"



class OutletAttr
{
public:
	OutletAttr(int type, int subType, int swType, int unit, int direction, std::string opts);
	~OutletAttr(){}	

	friend std::ostream & operator << (std::ostream& out, OutletAttr& oa);
	friend std::ostream & operator << (std::ostream& out, OutletAttr* poa);

public:
	virtual bool recvFrom(std::string& root, void * miGateway) = 0;
	virtual bool writeTo(const unsigned char* packet, int len, std::string& mac, std::string& model, std::string& gwMac, std::string& key, void * miGateway) = 0;
	virtual SsidPair idConverter(std::string& mac);

public:
	int getType(){return m_type;}

	int getSubType(){return m_subType;}

	int getswType(){return m_swType;}

	int getUnit(){return m_unit;}

	int getDirection(){return m_direction;}

	std::string getOpts(){return m_opts;}

	unsigned int macToUint(std::string& mac);	

	bool match(int type, int subType, int unit);

protected:


private:
	const int m_type;
	const int m_subType;
	const int m_swType;
	const int m_unit;
	const int m_direction;
	const std::string m_opts;
};



class OnOffOutlet : public OutletAttr
{

public:
	OnOffOutlet(int unit, int dir, std::initializer_list<Rule_OnOff> list);

public:
	bool recvFrom(std::string& root, void * miGateway) override;

	bool writeTo(const unsigned char* packet, int len, std::string& mac, std::string& model, std::string& gwMac, std::string& key, void * miGateway)  override;


private:

	std::vector<boost::tuple<std::string  /* key */, std::string /* value */, bool> > m_rule;

};





