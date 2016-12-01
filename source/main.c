#include "includes.h"
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void splash(Experiment *experiment);

//Global UM7 receive packet
extern UM7_packet global_packet;

int main(int argc, char *argv[])
{
	int opt;
	int is_one = 0;
	int is_two = 0;
	
	//decalre structs
	Experiment experiment;	
	Synthesizer synthOne;
	Synthesizer synthTwo;	
	
	//initialize synth number
	synthOne.number = 1;
	synthTwo.number = 2;
	
	// Retrieve the options:
    while ((opt = getopt(argc, argv, "dib:c:1:2:")) != -1 ) 
    {
        switch (opt) 
        {
            case 'd':
                experiment.is_debug_mode = 1;
                break;
            case 'i':
                experiment.is_imu = 1;
                break;
			case 'c':
				experiment.adc_channel = atoi(optarg);
				break;
			case 'b':
				synthOne.parameterFile = optarg;
				synthTwo.parameterFile = optarg;
				is_one = 1;
				is_two = 1;
				break;
			case '1':
				is_one = 1;
				synthOne.parameterFile = optarg;
				break;
			case '2':
				is_two = 1;
				synthTwo.parameterFile = optarg;
				break;
            case '?':
				if (optopt == 'c')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);		
				else
				fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);				
        }
    }
    
    if (is_one + is_two != 2)	
    {
		cprint("[!!] ", BRIGHT, RED);
		printf("A .ini parameter file must be provided for each synthesizer.\n");
		exit(EXIT_FAILURE);
	}
	
	splash(&experiment);
	
	clearParameters(&synthOne);
	clearParameters(&synthTwo);

	//get parameters for ini files
	getParameters(&synthOne);
	getParameters(&synthTwo);
	
	//calculate additional ramp paramters
	calculateRampParameters(&synthOne, &experiment);
	calculateRampParameters(&synthTwo, &experiment);
	
	//convert neccessary values to binary
	generateBinValues(&synthOne);
	generateBinValues(&synthTwo);

	//import register values from template file
	readTemplateFile("register_template/ramp_template.txt", &synthOne);	
	readTemplateFile("register_template/ramp_template.txt", &synthTwo);
	
	//insert calculated ramp paramters into register array	
	insertRampParameters(&synthOne);
	insertRampParameters(&synthTwo);
	
	//initilize the red pitaya and configure pins 
	initRP();
	initPins(&synthOne);
	initPins(&synthTwo);
	
	//red pitaya provides 50 MHz reference signal for synth's 
	generateClock();

	//software reset all synth register values
	setRegister(&synthOne, 2, 0b00000100); 
	setRegister(&synthTwo, 2, 0b00000100); 
	
	//initilize IMU and configure update rates
	if (experiment.is_imu) initIMU();
	
	//send register array values to synths
	updateRegisters(&synthOne);
	updateRegisters(&synthTwo);		

	//get user input for final experiment settings
	getExperimentParameters(&experiment);
	configureVerbose(&experiment, &synthOne, &synthTwo);		


	//trigger synth's to begin generating ramps at the same time
	parallelTrigger(&synthOne, &synthTwo);
	//triggerSynthesizers(&synthOne, &synthTwo);		
	
	//begin recording adc data
	if (continuousAcquire(experiment.adc_channel, experiment.recSize, experiment.decFactor, experiment.ch1_filename, experiment.ch2_filename, experiment.imu_filename, experiment.is_imu) != 0)
	{
		cprint("[!!] ", BRIGHT, RED);
		printf("Error occured during recording.\n");
	}
	
	releaseRP();	

	return EXIT_SUCCESS;
}


void splash(Experiment *experiment)
{
	system("clear\n");
	printf("UCT RPC Version: %s\n", VERSION);
	printf("----------------------\n");	
	
	if (experiment->is_debug_mode)
	{
		cprint("[OK] ", BRIGHT, GREEN);	
		printf("Debug mode active.\n");
	}
	else
	{
		cprint("[!!] ", BRIGHT, RED);	
		printf("Debug mode disabled.\n");
	}		
	
	if (experiment->is_imu)
	{
		cprint("[OK] ", BRIGHT, GREEN);
		printf("IMU mode active.\n");
	}
	else
	{	
		cprint("[!!] ", BRIGHT, RED);
		printf("IMU mode disabled.\n");
	}
}

