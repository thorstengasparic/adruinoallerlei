#include <..\OneWire\OneWire.h>
#include <inttypes.h>


/* DS18S20 Temperature chip i/o */

#define MAX_SENSORCOUNT 1
class DS1820
{
	public:
	uint8_t SensorCount;
	bool debug;
	DS1820(uint8_t IoPin);
	float Measure(uint8_t sensor);
	void Search();
private:
	OneWire  ds;
	void Reset();
	uint8_t addr[MAX_SENSORCOUNT][8];
	uint8_t data[12];
};
