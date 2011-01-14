


#include "Ethernet.h"
#include "Udp.h"
#include "EasyIP.h"

EasyIP::EasyIP(int16_t flagwords[], uint8_t max_flagwords){
	this->_MAX_FLAGWORDS = max_flagwords;
	this->flagwords=flagwords;
	this->_is_sending=false;
}



void EasyIP::begin(){
	Udp.begin(EASYIP_PORT);
}

int EasyIP::available(){
	return Udp.available();
}

int EasyIP::process(){
	if (!available()) return 0;
	int rv=1;
	clear_packet();
	unsigned int remotePort;
	uint8_t remoteIp[4];
	
	int packetSize =  Udp.readPacket((uint8_t *)&packet,sizeof(packet),remoteIp,(uint16_t *)&remotePort);
	//if return value <0 = the packet was trunctated to fit the buffer
	clear_data();
	//process header
	packetSize = EASYIP_HEADER_SIZE;
	if(packet.reqdata_type==EASYIP_TYPE_FLAGWORD && (packet.reqdata_offset_server+packet.reqdata_size) < _MAX_FLAGWORDS){
		packet.flags = EASYIP_FLAG_RESP; //send a response since flagword data was requested
		//copy from flagwords to packet.data
		memcpy(packet.data, flagwords+packet.reqdata_offset_server, sizeof(uint16_t)*packet.reqdata_size);
		packetSize+=sizeof(uint16_t) * packet.reqdata_size;
	}
	else {
		//did not understand, out of bounds or not implemented, respond with NO ACK
		packet.flags=EASYIP_FLAG_NOACK;
		rv=-1;
	}
	Udp.sendPacket((uint8_t *)&packet, packetSize, remoteIp, remotePort);
	return rv;
}


void EasyIP::clear_data(){
	memset(packet.data, 0, sizeof(packet.data));
}

void EasyIP::clear_packet(){
	memset(&packet, 0, sizeof(packet));
}