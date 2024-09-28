/******************************************************************************
/*!
\file       main.cpp
\author     Chan Guo Geng Gordon
\par        email: g.chan/@digipen.edu
\date       September 27, 2024
\brief      Defines

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <fstream>
#include <ostream>

int main(int argc, char** argv)
{
	std::ofstream registry("lol.txt");
		
	registry << "AAAAAAAAAAHHHHHHHHHHHH";

	registry.close();

	return 1;
}
namespace BorealisAssetCompiler
{
}

