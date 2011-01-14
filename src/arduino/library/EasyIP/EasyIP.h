

#ifndef EasyIP_h
#define EasyIP_h
#include <inttypes.h>


#define EASYIP_HEADER_SIZE 20
#define EASYIP_DATA_SIZE 25  //max number of uint16_t values data can handle  

#define EASYIP_PORT               995

#define EASYIP_FLAG_INFO          0x01
#define EASYIP_FLAG_BIT_OR        0x02
#define EASYIP_FLAG_BIT_AND       0x04
#define EASYIP_FLAG_NOACK         0x40
#define EASYIP_FLAG_RESP          0x80

#define EASYIP_ERROR_OPERAND      0x01
#define EASYIP_ERROR_OFFSET       0x02
#define EASYIP_ERROR_DATASIZE     0x04
#define EASYIP_ERROR_NOSUPPORT    0x10

#define EASYIP_TYPE_FLAGWORD      1
#define EASYIP_TYPE_INPUTWORD     2
#define EASYIP_TYPE_OUTPUTWORD    3
#define EASYIP_TYPE_REGISTERS     4
#define EASYIP_TYPE_STRINGS       11


typedef struct {
	uint8_t flags;
	uint8_t error;
	uint16_t counter;
	uint16_t index1;
	uint8_t spare1;
	uint8_t senddata_type;
	uint16_t senddata_size;
	uint16_t senddata_offset;
	uint8_t spare2;
	uint8_t reqdata_type;
	uint16_t reqdata_size;
	uint16_t reqdata_offset_server;
	uint16_t reqdata_offset_client;
	uint16_t data[EASYIP_DATA_SIZE];
} easyip_packet_t;

class EasyIP {
private:
	void clear_packet();
	void clear_data();
	uint8_t _MAX_FLAGWORDS;
	bool _is_sending;
	
public:
	int16_t *flagwords;
	easyip_packet_t packet;
	EasyIP(int16_t [], uint8_t); //initialize everyting and set available FlagWords	
	void begin(); //start 
	int available();		// has data been received?	
	int process(); //process any pending requests
	
};



#endif
