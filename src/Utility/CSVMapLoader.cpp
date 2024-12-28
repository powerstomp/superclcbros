#include "CSVMapLoader.h"

#include <ios>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

std::vector<CSV::Row> CSV::Parse(std::istream& stream, int n, int m) {
	std::vector<CSV::Row> result(n, CSV::Row(m, -1));
	for (int i = 0; i < n; i++) {
		std::string line;
		std::getline(stream, line);
		std::istringstream lineStream(line);
		for (int j = 0; j < m; j++) {
			if (!(lineStream >> result[i][j]))
				throw std::invalid_argument("File parse error.");
			lineStream.ignore(std::numeric_limits<std::streamsize>::max(), ',');
		}
	}
	return result;
}
