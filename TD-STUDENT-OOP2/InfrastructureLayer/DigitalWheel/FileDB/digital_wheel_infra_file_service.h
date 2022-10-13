#ifndef DW_INFRA_FILE_SERVICE_H
#define DW_INFRA_FILE_SERVICE_H

int DigitalWheelInfraFileService_open(char *name);
void DigitalWheelInfraFileService_append(digital_wheel record);
void DigitalWheelInfraFileService_close(void);
digital_wheel DigitalWheelInfraFileService_get_nth(int rank);
#endif