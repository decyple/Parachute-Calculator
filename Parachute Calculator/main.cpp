//
//  main.cpp
//  Parachute Calculator
//
//  Created by Mark McCorkle on 7/21/19.
//  Copyright © 2019 Mark McCorkle. All rights reserved.
//


#include <iostream>
#include <math.h>		// SQRT, POW


enum units { Imperial, Metric, Unknown };


struct ParachuteParameters
{
	float Mass;
	float Speed_of_Impact;
	float Drag_Coefficient;
	units Unit;
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
		std::cout << "Metric Parachute Calculation Results:\n";
		std::cout << '\n' << std::endl;
		std::cout << "\tRocket Mass: " << _ROCKET_MASS << " Kilogram(s)" << std::endl;
		std::cout << "\tDrag Coefficient: " << _DRAG_COEFFICIENT << std::endl;
		std::cout << "\tSpeed of Impact: " << _SPEED_OF_IMPACT << " Meters/Second" << std::endl;
		std::cout << "\tGravitational Constant: " << _GRAVITY << " Meters/Second²" << std::endl;
		std::cout << "\tPi: " << _PI << std::endl;
		std::cout << "\tAir Density: " << _AIR_DENSITY << " Kilograms/Meter³" << std::endl;
		std::cout << '\n' << '\n' << std::endl;
		std::cout << "\tParachute_Diameter: " << _Parachute_Diameter << " Meter(s)" << std::endl;
		std::cout << '\n' << std::endl;
	}
	else
	{
		std::cout << "Imperial Parachute Calculation Results:\n";
		std::cout << '\n' << std::endl;
		std::cout << "\tRocket Mass: " << _ROCKET_MASS << " Pound(s)" << std::endl;
		std::cout << "\tDrag Coefficient: " << _DRAG_COEFFICIENT << std::endl;
		std::cout << "\tSpeed of Impact: " << _SPEED_OF_IMPACT << " Feet/Second" << std::endl;
		std::cout << "\tGravitational Constant: " << _GRAVITY << " Feet/Second²" << std::endl;
		std::cout << "\tPi: " << _PI << std::endl;
		std::cout << "\tAir Density: " << _AIR_DENSITY << " Pounds/Feet³" << std::endl;
		std::cout << '\n' << '\n' << std::endl;
		std::cout << "\tParachute_Diameter: " << _Parachute_Diameter << " Inche(s)" << std::endl;
		std::cout << '\n' << std::endl;
	}
	
}


float CalculateParachuteDiameter_Metric(ParachuteParameters _input)
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
	float Parachute_Diameter_M = sqrt((8 * _input.Mass * GRAVITY_M) / (PI * AIR_DENSITY * _input.Drag_Coefficient * pow (_input.Speed_of_Impact,2)));
	
	printDetails(_input.Mass,
				 GRAVITY_FT,
				 PI,
				 AIR_DENSITY,
				 _input.Drag_Coefficient,
				 _input.Speed_of_Impact,
				 Parachute_Diameter_M,
				 true);
	
	return Parachute_Diameter_M;
	
}


float CalculateParachuteDiameter_Imperial(ParachuteParameters _input)
{
	
	// Pounds in a kilogram:
	const float POUNDS_IN_KILOGRAM = 2.20462262;
	
	// Convert Rocket Mass to kilograms:
	const float ROCKET_MASS_KG = _input.Mass / POUNDS_IN_KILOGRAM;
	
	// Feet in a meter:
	const float METER_TO_FEET_RATIO = 0.3048;
	
	// Convert ft/s to m/s:
	const float SPEED_OF_IMPACT_M = _input.Speed_of_Impact * METER_TO_FEET_RATIO;
	
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
	float Parachute_Diameter_M = sqrt((8 * ROCKET_MASS_KG * GRAVITY_M) / (PI * AIR_DENSITY * _input.Drag_Coefficient * pow (SPEED_OF_IMPACT_M,2)));
	
	// Convert from meters to inches:
	float Parachute_Diameter_In = Parachute_Diameter_M * 39.3700787;
	
	printDetails(_input.Mass,
				 GRAVITY_FT,
				 PI,
				 AIR_DENSITY,
				 _input.Drag_Coefficient,
				 _input.Speed_of_Impact,
				 Parachute_Diameter_In,
				 false);
	
	return Parachute_Diameter_In;
	
}


ParachuteParameters QueryUser()
{
	
	ParachuteParameters return_data_;
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
		//std::cout << "Imperial has been selected..." << std::endl;
	}
	else if (tmp == "m" || tmp == "metric")
	{
		user_data_units = Metric;
		//std::cout << "Metric has been selected..." << std::endl;
	}
	else
	{
		std::cout << "You have entered an invalid unit... Lets try this again.\n\n" << std::endl;
		goto unit_question;
	}

mass_question:
	std::cout << "What is the mass of the rocket?\n> ";
	std::cin >> user_data_mass;
	if(!std::cin)
	{
		std::cin.clear();
		std::cin.ignore(9999,'\n');
		goto mass_question;
	}
	
impact_question:
	std::cout << "What is the desired speed of impact?\n> ";
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
	
	return_data_.Unit = user_data_units;
	return_data_.Mass = user_data_mass;
	return_data_.Speed_of_Impact = user_data_impact;
	return_data_.Drag_Coefficient = user_data_drag;
	
	std::cout << '\n' << '\n';
	
	return return_data_;
	
}


int main(int argc, const char * argv[])
{
	
	ParachuteParameters Rocket1;
	Rocket1 = QueryUser();
	
	ParachuteParameters Rocket2;
	Rocket2.Mass = 0.453592;
	Rocket2.Speed_of_Impact = 6.096;
	Rocket2.Drag_Coefficient = 1.5;
	
	CalculateParachuteDiameter_Imperial(Rocket1);
	CalculateParachuteDiameter_Metric(Rocket2);
	
	return 0;
	
}
