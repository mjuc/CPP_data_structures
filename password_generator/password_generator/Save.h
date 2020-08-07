#pragma once
#include<iostream>
#include<vector>

class Save
{
	Save();
	void save_to_file(std::string input);
	std::vector<std::string> read_from_file();
};

