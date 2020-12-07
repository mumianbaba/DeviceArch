#include <iostream>
#include <map>
#include "Outlet.hpp"
#include "DevAttr.hpp"
#include "Device.hpp"
#include "XiaomiGateway.hpp"


using namespace XiaoMi;

int main(int argc, char** argv)
{
	std::cout<<"Rebuild domoticz xiaomi_gateway.cpp by yp"<<std::endl;

	XiaomiGateway* gw = new XiaomiGateway();

	std::string zigbeeModel = "lumi.ctrl_neutral2";
	std::string mac = "1234567890123456";
	/* add device on device list */
	{
		Device* pdev = new Device(mac, gw->findDevAttr(zigbeeModel));
		std::shared_ptr<Device> dev (pdev);
		gw->addDeviceToMap(mac, dev);
		gw->addDeviceToMap(mac, dev);
		gw->addDeviceToMap(mac, dev);
	}

	/* from/to Device */
	{
		std::shared_ptr<Device> dev1 = gw->getDevice(mac);
		std::shared_ptr<Device> dev2 = gw->getDevice(0x90123456, pTypeGeneralSwitch, sSwitchGeneralSwitch, 1);
		std::shared_ptr<Device> dev3 = gw->getDevice(0x90123456, pTypeGeneralSwitch, sSwitchGeneralSwitch, 2);
		std::shared_ptr<Device> dev4 = gw->getDevice(0x90123456, pTypeGeneralSwitch, sSwitchGeneralSwitch, 3);

		std::string msg = "12345";
		unsigned char packet[] = "1w234243";
		std::string gwMac = "1232334";
		std::string key = "1223234436776";

		dev1->recvFrom(msg, nullptr);
		dev1->writeTo(packet, sizeof(packet), gwMac, key, nullptr);


		std::cout<<dev1.get()<<std::endl;
		std::cout<<dev2.get()<<std::endl;
		std::cout<<dev3.get()<<std::endl;
		std::cout<<dev4.get()<<std::endl;
	}

	/* remove device from device list */
	{
		gw->delDeviceFromMap(mac);
		gw->delDeviceFromMap(mac);
		gw->delDeviceFromMap(mac);
	}

	gw->getDevice(mac);
	delete gw;
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


#if 0
	
	static DevAttr devAttr{{&onoff0, &onoff1}, "Aqara Wall Dual Switch", "lumi.ctrl_neutral2", "QBKG03LM", "lumi"};
	
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
#endif

