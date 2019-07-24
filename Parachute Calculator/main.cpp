//
//  main.cpp
//  Parachute Calculator
//
//  Created by Mark McCorkle on 7/21/19.
//  Copyright © 2019 Mark McCorkle. All rights reserved.
//


#include <iostream>
#include <math.h>		// SQRT, POW


enum units { Imperial,
			 Metric,
			 Unknown };


struct ParachuteParameters
{
	float Mass;
	float Speed_of_Impact;
	float Drag_Coefficient;
	units Unit = Unknown;
	float Diameter;
	float ShroudLineLength;
};


void printDetails(float _ROCKET_MASS,
				  float _GRAVITY,
				  float _PI,
				  float _AIR_DENSITY,
				  float _DRAG_COEFFICIENT,
				  float _SPEED_OF_IMPACT,
				  float _Parachute_Diameter,
				   bool _In_Metric)
{
	
	if(_In_Metric)
	{
		std::cout << "Metric Parachute Calculation Results:\n"
				  << '\n' << std::endl
				  << "\tRocket Mass: " << _ROCKET_MASS << " Kilogram(s)" << std::endl
				  << "\tDrag Coefficient: " << _DRAG_COEFFICIENT << std::endl
				  << "\tSpeed of Impact: " << _SPEED_OF_IMPACT << " Meters/Second" << std::endl
				  << "\tGravitational Constant: " << _GRAVITY << " Meters/Second²" << std::endl
				  << "\tPi: " << _PI << std::endl
				  << "\tAir Density: " << _AIR_DENSITY << " Kilograms/Meter³" << std::endl
				  << '\n' << '\n' << std::endl
				  << "\tParachute_Diameter: " << _Parachute_Diameter << " Meter(s)" << std::endl
				  << '\n' << std::endl;
	}
	else
	{
		std::cout << "Imperial Parachute Calculation Results:\n"
				  << '\n' << std::endl
				  << "\tRocket Mass: " << _ROCKET_MASS << " Pound(s)" << std::endl
				  << "\tDrag Coefficient: " << _DRAG_COEFFICIENT << std::endl
				  << "\tSpeed of Impact: " << _SPEED_OF_IMPACT << " Feet/Second" << std::endl
				  << "\tGravitational Constant: " << _GRAVITY << " Feet/Second²" << std::endl
				  << "\tPi: " << _PI << std::endl
				  << "\tAir Density: " << _AIR_DENSITY << " Pounds/Feet³" << std::endl
				  << '\n' << '\n' << std::endl
				  << "\tParachute_Diameter: " << _Parachute_Diameter << " Inche(s)" << std::endl
				  << '\n' << std::endl;
	}
	
}


float CalculateParachuteDiameter_Metric(ParachuteParameters* _input)
{
	
	// Feet in a meter:
	const float METER_TO_FEET_RATIO = 0.3048;
	
	// Gravitational Constant (ft/s):
	const float GRAVITY_FT = 32.1740;
	
	// Convert ft/s to m/s:
	const float GRAVITY_M = GRAVITY_FT * METER_TO_FEET_RATIO;
	
	// Air Density (kg/m3):
	// Source of calculations @ 80°F: https://www.engineeringtoolbox.com/air-density-specific-weight-d_600.html
	const float AIR_DENSITY = 1.177;
	
	// Manual Pi value:
	const float PI = 3.1415927;
	
	// Main Calculation:
	float Parachute_Diameter_M = sqrt((8 * _input->Mass * GRAVITY_M) / (PI * AIR_DENSITY * _input->Drag_Coefficient * pow (_input->Speed_of_Impact,2)));
	
	printDetails(_input->Mass,
				 GRAVITY_FT,
				 PI,
				 AIR_DENSITY,
				 _input->Drag_Coefficient,
				 _input->Speed_of_Impact,
				 Parachute_Diameter_M,
				 true);
	
	return Parachute_Diameter_M;
	
}


float CalculateParachuteDiameter_Imperial(ParachuteParameters* _input)
{
	
	// Pounds in a kilogram:
	const float POUNDS_IN_KILOGRAM = 2.20462262;
	
	// Convert Rocket Mass to kilograms:
	const float ROCKET_MASS_KG = _input->Mass / POUNDS_IN_KILOGRAM;
	
	// Feet in a meter:
	const float METER_TO_FEET_RATIO = 0.3048;
	
	// Convert ft/s to m/s:
	const float SPEED_OF_IMPACT_M = _input->Speed_of_Impact * METER_TO_FEET_RATIO;
	
	// Gravitational Constant (ft/s):
	const float GRAVITY_FT = 32.1740;
	
	// Convert ft/s to m/s:
	const float GRAVITY_M = GRAVITY_FT * METER_TO_FEET_RATIO;
	
	// Air Density (kg/m3):
	// Source of calculations @ 80°F: https://www.engineeringtoolbox.com/air-density-specific-weight-d_600.html
	const float AIR_DENSITY = 1.177;
	
	// Manual Pi value:
	const float PI = 3.1415927;
	
	// Main Calculation:
	float Parachute_Diameter_M = sqrt((8 * ROCKET_MASS_KG * GRAVITY_M) / (PI * AIR_DENSITY * _input->Drag_Coefficient * pow (SPEED_OF_IMPACT_M,2)));
	
	// Convert from meters to inches:
	float Parachute_Diameter_In = Parachute_Diameter_M * 39.3700787;
	
	printDetails(_input->Mass,
				 GRAVITY_FT,
				 PI,
				 AIR_DENSITY,
				 _input->Drag_Coefficient,
				 _input->Speed_of_Impact,
				 Parachute_Diameter_In,
				 false);
	
	return Parachute_Diameter_In;
	
}


void QueryUser(ParachuteParameters* _input)
{
	
	std::string tmp;
	units user_data_units = Unknown;
	float user_data_mass;
	float user_data_impact;
	float user_data_drag;
	
unit_question:
	std::cout << "Imperial (feet, pounds, etc...) or Metric (meters, kilograms, etc...) units?\n";
	std::cout << "[i|m|imperial|metric]> ";
	std::cin >> tmp;
	
	if(tmp == "i" || tmp == "imperial")
	{
		user_data_units = Imperial;
	}
	else if (tmp == "m" || tmp == "metric")
	{
		user_data_units = Metric;
	}
	else
	{
		std::cout << "You have entered an invalid unit... Lets try this again.\n\n" << std::endl;
		goto unit_question;
	}

mass_question:
	std::cout << "What is the mass of the rocket";
	if(user_data_units == Imperial)
		std::cout << " (Pounds)?\n> ";
	else if(user_data_units == Metric)
		std::cout << " (Kilograms)?\n> ";
	std::cin >> user_data_mass;
	if(!std::cin)
	{
		std::cin.clear();
		std::cin.ignore(9999,'\n');
		goto mass_question;
	}
	
impact_question:
	std::cout << "What is the desired speed of impact";
	if(user_data_units == Imperial)
		std::cout << " (Feet/Second)?\n> ";
	else if(user_data_units == Metric)
		std::cout << " (Meters/Second)?\n> ";
	std::cin >> user_data_impact;
	if(!std::cin)
	{
		std::cin.clear();
		std::cin.ignore(9999,'\n');
		goto impact_question;
	}

drag_question:
	std::cout << "What is the drag coefficient?\n> ";
	std::cin >> user_data_drag;
	if(!std::cin)
	{
		std::cin.clear();
		std::cin.ignore(9999,'\n');
		goto drag_question;
	}
	
	_input->Unit = user_data_units;
	_input->Mass = user_data_mass;
	_input->Speed_of_Impact = user_data_impact;
	_input->Drag_Coefficient = user_data_drag;
	
	std::cout << '\n' << '\n';
	
}


void printHelp()
{
	std::cerr << "Usage Example: \n\n"
			  << "\t Parachute Calculator --mass 1.1 --drag 1.5 --impact 20 --units imperial\n"
			  << "\t Parachute Calculator -m 23 -i 21 -d 1.25 -u imperial\n\n"
			  << "Options:\n\n"
			  << "\t-h,  --help\t\t\tShow this help message\n"
			  << "\t-m,  --mass\t\t\tObject Mass\n"
			  << "\t-d,  --drag\t\t\tDrag Coefficient\n"
			  << "\t-i,  --impact\t\tSpeed of Impact\n"
			  << "\t-u,  --units\t\tUnits of measurement\n"
			  << std::endl;
}


void confirmInput(ParachuteParameters* _input)
{
	
	if(_input->Unit != Metric && _input->Unit != Imperial)
	{
		
	unit_question:
		std::string tmp;
		std::cout << "Imperial (feet, pounds, etc...) or Metric (meters, kilograms, etc...) units?\n";
		std::cout << "[i|m|imperial|metric]> ";
		std::cin >> tmp;
		
		if(tmp == "i" || tmp == "imperial")
		{
			_input->Unit = Imperial;
		}
		else if (tmp == "m" || tmp == "metric")
		{
			_input->Unit = Metric;
		}
		else
		{
			std::cout << "You have entered an invalid unit... Lets try this again.\n\n" << std::endl;
			goto unit_question;
		}
		std::cout << '\n';
	}
	
	if(!_input->Drag_Coefficient)
	{

	drag_question:
		std::cout << "What is the drag coefficient?\n> ";
		std::cin >> _input->Drag_Coefficient;
		if(!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(9999,'\n');
			goto drag_question;
		}
		std::cout << '\n';
	}
	
	if(!_input->Mass)
	{

	mass_question:
		std::cout << "What is the mass of the rocket";
		if(_input->Unit == Imperial)
			std::cout << " (Pounds)?\n> ";
		else if(_input->Unit == Metric)
			std::cout << " (Kilograms)?\n> ";
		std::cin >> _input->Mass;
		if(!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(9999,'\n');
			goto mass_question;
		}
		std::cout << '\n';
	}
	
	if(!_input->Speed_of_Impact)
	{

	impact_question:
		std::cout << "What is the desired speed of impact";
		if(_input->Unit == Imperial)
			std::cout << " (Feet/Second)?\n> ";
		else if(_input->Unit == Metric)
			std::cout << " (Meters/Second)?\n> ";
		std::cin >> _input->Speed_of_Impact;
		if(!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(9999,'\n');
			goto impact_question;
		}
		std::cout << '\n';
	}
	
}


void processArguments(int* _argc,
					  const char* _argv[],
					  ParachuteParameters* _tmpParachute)
{
	
	if( std::string(_argv[1]) != "--help" && std::string(_argv[1]) != "-h" )
		std::cout << "Input:" << std::endl;
	
	for (int i = 1; i < *_argc; i++)
	{
		
		int next_i = i + 1;
		
		if( std::string(_argv[i]) == "--help" || std::string(_argv[i]) == "-h" )
		{
			printHelp();
			exit(0);
		}
		
		if( std::string(_argv[i]) == "--mass" || std::string(_argv[i]) == "-m" )
		{
			_tmpParachute->Mass = atof (_argv[next_i]);
			std::cout << "\tMass: " << _argv[next_i] << std::endl;
		}
		
		if( std::string(_argv[i]) == "--drag" || std::string(_argv[i]) == "-d" )
		{
			_tmpParachute->Drag_Coefficient = atof (_argv[next_i]);
			std::cout << "\tDrag Coefficient: " << _argv[next_i] << std::endl;
		}
		
		if( std::string(_argv[i]) == "--impact" || std::string(_argv[i]) == "-i" )
		{
			_tmpParachute->Speed_of_Impact = atof (_argv[next_i]);
			std::cout << "\tSpeed of Impact: " << _argv[next_i] << std::endl;
		}
		
		if( std::string(_argv[i]) == "--units" || std::string(_argv[i]) == "-u" )
		{
			
			if(std::string(_argv[next_i]) == "imperial")
				_tmpParachute->Unit = Imperial;
			else if(std::string(_argv[next_i]) == "metric")
				_tmpParachute->Unit = Metric;
			else
				std::cout << "ERROR: There was an error determining the units..." << '\n';
			
			std::cout << "\tUnit: " << _argv[next_i] << std::endl;
			
		}
		
	}
	
	std::cout << '\n';
	
}


float CalculateShroudLines(ParachuteParameters* _input, bool _In_Metric)
{
	
	std::cout << "\tShroud Line Length:\n\n";
	
	if(_In_Metric)
	{
		std::cout << "\t\tStandard (default): " << (_input->Diameter * 1.5) << " meters" << std::endl;
		std::cout << "\t\t              Loop: " << (_input->Diameter * 2) << " meters" << std::endl;
	}
	else
	{
		std::cout << "\t\tStandard (default): " << (_input->Diameter * 1.5) << " inches" << std::endl;
		std::cout << "\t\t              Loop: " << (_input->Diameter * 2) << " inches" << std::endl;
	}
	
	std::cout << '\n' << '\n';
	
	return _input->Diameter * 1.5;
	
}


int main(int argc,
		 const char* argv[])
{
	
	ParachuteParameters tmpParachute;
	ParachuteParameters* ptr2_tmpParachute = nullptr;
	ptr2_tmpParachute = &tmpParachute;
	
	int* ptr2_argc = nullptr;
	ptr2_argc = &argc;

	if(argc > 1)
	{
		processArguments(ptr2_argc, argv, ptr2_tmpParachute);
		confirmInput(ptr2_tmpParachute);
	}
	else
	{
		QueryUser(ptr2_tmpParachute);
		confirmInput(ptr2_tmpParachute);
	}
	
	if(tmpParachute.Unit == Imperial)
		tmpParachute.Diameter = CalculateParachuteDiameter_Imperial(ptr2_tmpParachute);
	else if(tmpParachute.Unit == Metric)
		tmpParachute.Diameter = CalculateParachuteDiameter_Metric(ptr2_tmpParachute);
	else
		std::cout << "ERROR: An error has occured while calculating the parachute dimensions." << std::endl;
	
	tmpParachute.ShroudLineLength = CalculateShroudLines(ptr2_tmpParachute, tmpParachute.Unit);
	
	return 0;
	
}
