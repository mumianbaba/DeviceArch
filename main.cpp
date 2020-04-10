#include <iostream>
#include "Outlet.hpp"
#include "DevAttr.hpp"
#include "Device.hpp"

static OnOffOutlet onoff0{ 1, 3, {{"channel_0", "on", true}, {"channel_0", "off", false}}};
static OnOffOutlet onoff1{ 2, 3, {{"channel_1", "on", true}, {"channel_1", "off", false}}};
static OnOffOutlet onoff2{ 3, 3, {{"channel_2", "on", true}, {"channel_2", "off", false}}};
static OnOffOutlet onoff3{ 4, 3, {{"channel_3", "on", true}, {"channel_4", "off", false}}};

static DevAttr devAttr{{&onoff0, &onoff1}, "Aqara Wall Dual Switch", "lumi.ctrl_neutral2", "QBKG03LM", "lumi"};


const DevInfo  devInfoTab[] {
	{	
		name : "Aqara Wall Dual Switch",
		zigbeeModel : "lumi.ctrl_neutral2",
		model : "QBKG03LM",
		vendor : "lumi",
		outlet : {&onoff0, &onoff1}
	},
	{	
		name : "Aqara Wall Dual Switch",
		zigbeeModel : "lumi.ctrl_neutral2",
		model : "QBKG03LM",
		vendor : "lumi",
		outlet : {&onoff0, &onoff1}
	}
};


int main(int argc, char** argv)
{
	std::cout<<"Rebuild domoticz xiaomi_gateway.cpp by yp"<<std::endl;

	std::cout<<devAttr<<std::endl;
	OutletAttr* outlet0 = dynamic_cast<OutletAttr*>(devAttr.getOutlet(0));
	OutletAttr* outlet1 = dynamic_cast<OutletAttr*>(devAttr.getOutlet(1));

	std::shared_ptr<Device> dev (new Device(&devAttr, "1234567890123456"));
	std::string msg = "12345";
	unsigned char packet[] = "1w234243";
	std::string gwMac = "1232334";
	std::string key = "1223234436776";


	dev->recvFrom(msg, nullptr);


	
	dev->writeTo(packet, sizeof(packet), gwMac, key, nullptr);
	
	return 0;
}




#if 0


{
	int ab;
	unsigned char msg[] = "123";
	std::string str = "123";
	
	std::string mac= "1234567890123456";
	std::string model= "1234567890123456";
	std::string gwModel= "1234567890123456";
	std::string key= "1234567890123456";

	/* read need multi outlet {model mac} -->device--> [outlet] */
	outlet0->recvFrom(str, &ab);
	outlet1->recvFrom(str, &ab);


	/* write allways one outlet {type, subType, swType, unit, ssid} --> outlet*/
	outlet0->writeTo(msg, 0, mac, model, key, gwModel, &ab);
	outlet1->writeTo(msg, 0, mac, model, key, gwModel, &ab);
}


#endif

