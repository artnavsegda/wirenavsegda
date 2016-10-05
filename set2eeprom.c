#include <stdio.h>
#include "settings.h"

int main(void)
{
	struct eeprom e = { .jump_table = startstate };
	scanf("ip = %hhu.%hhu.%hhu.%hhu\n",&e.ip[0],&e.ip[1],&e.ip[2],&e.ip[3]);
	scanf("mac = %hhx:%hhx:%hhx:%hhx:%hhx:%hhx\n",&e.mac[0],&e.mac[1],&e.mac[2],&e.mac[3],&e.mac[4],&e.mac[5]);
	scanf("startlevel = %hu\nprecalibrationdelay = %hu\ncalibration = %hu\npostcalibrationdelay = %hu\ncelldelay = %hu\ncelllevel = %hu\nzerodelay = %hu\nzerotest = %hu\ntotalmercurydelay = %hu\ntotalmercury = %hu\nelementalmercurydelay = %hu\nelementalmercury = %hu\npurge = %hu\n",&e.length_table.startlevel,&e.length_table.precalibrationdelay,&e.length_table.calibration,&e.length_table.postcalibrationdelay,&e.length_table.celldelay,&e.length_table.celllevel,&e.length_table.zerodelay,&e.length_table.zerotest,&e.length_table.totalmercurydelay,&e.length_table.totalmercury,&e.length_table.elementalmercurydelay,&e.length_table.elementalmercury,&e.length_table.purge);
        scanf("ad7705_setup_register = %hhX\n",&e.ad7705_setup_register);
        scanf("ad7705_clock_register = %hhX\n",&e.ad7705_clock_register);
	fwrite((char *)&e,sizeof(e),1,stdout);
	return 0;
}
