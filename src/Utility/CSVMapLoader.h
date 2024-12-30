#ifndef _CSVMAPLOADER_H
#define _CSVMAPLOADER_H

#include <istream>
#include <vector>

// Loads a CSV of ints (no header row)
namespace CSV {
	using Row = std::vector<int>;
	std::vector<Row> Parse(std::istream&, int n, int m);
};

#endif
