#ifndef _CSVMAPLOADER_H
#define _CSVMAPLOADER_H

#include <istream>
#include <vector>

namespace CSV {
	using Row = std::vector<int>;
	std::vector<Row> Parse(std::istream&, int n, int m);
};

#endif
