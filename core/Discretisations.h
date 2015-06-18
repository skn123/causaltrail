#ifndef DISCRETISATIONS_H
#define DISCRETISATIONS_H

#include "Matrix.h"

#include <map>
#include <unordered_map>

#include <boost/optional/optional.hpp>

class Discretisations
{
	public:
	using Observations = Matrix<std::string>;
	using DiscObservations = Matrix<int>;
	using ObservationMap = std::unordered_map<std::string, int>;
	using RevObservationMap = std::map<std::pair<int, int>, std::string>;

	static const int NA;

	struct Data
	{
		Data(const Observations& input_, DiscObservations& output_,
		     ObservationMap& map_, RevObservationMap& revMap_)
		    : input(input_), output(output_), map(map_), revMap(revMap_)
		{
		}

		const Observations& input;
		DiscObservations& output;
		ObservationMap& map;
		RevObservationMap& revMap;
	};

	virtual ~Discretisations() = default;
	virtual void apply(unsigned int row, Data& data) = 0;

	protected:
	boost::optional<float> getNumber(const Observations& obs, unsigned int col,
	                                 unsigned int row);

	void createNameEntry(ObservationMap& obs, RevObservationMap& obsR,
	                     int value, unsigned int row);

	std::vector<float> createSortedVector(const Observations&,
	                                      unsigned int row);

	void
	convertToDenseNumbers(const std::vector<boost::optional<int>>& discretized,
	                      Data& data, unsigned int row);
};

#endif
